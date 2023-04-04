#include "dispatcherservice.h"
#include <QWebSocket>

DispatcherService::DispatcherService(QObject *parent)
    : QObject{parent}
{
    // websocket server init
    websocket_server = new QWebSocketServer("server",QWebSocketServer::NonSecureMode,this);

    connect(websocket_server,&QWebSocketServer::newConnection,this,&DispatcherService::NewConnect);

    websocket_server->listen(QHostAddress::AnyIPv4,8888);
    qDebug() << "DispatcherServer on!" << websocket_server->serverAddress().toString() << websocket_server->serverPort();

    //user server init
    this->user_server = new UserService();

    //dbserver init
    //this->db_server = new DbServer();

    // timer init
    timer = new QTimer();

    connect(timer,&QTimer::timeout,this,&DispatcherService::PopMessageFromQuene);

    timer->start(1000);

}

bool DispatcherService::NewConnect()
{
    QWebSocket* localNextPendingConnection = websocket_server->nextPendingConnection();

    int type = localNextPendingConnection->resourceName().split('?')[1].split('&')[2].split('=')[1].toInt();
    QString name = localNextPendingConnection->resourceName().split('?')[1].split('&')[0].split('=')[1];
    QString password = localNextPendingConnection->resourceName().split('?')[1].split('&')[1].split('=')[1];

    UserPo user = UserPo(name.toInt(),password);
    qDebug() <<  name.toInt() <<  "：" << password << ":" << type;
    if(type == 1)
    {
        int login_result = DbServer::LogIn(user);
        if(login_result == Result::LOGIN_SUCCESS)
        {
            bool result = this->user_server->UserLogin(name.toInt(),localNextPendingConnection);
            qDebug() <<  "login success" << result;
            if(result)
            {
                connect(localNextPendingConnection,&QWebSocket::textMessageReceived,this,&DispatcherService::PushMessageToQuene);
                //  TODO:replay login success
                qDebug() <<  "insert success";
                localNextPendingConnection->sendTextMessage(JsonHelper::LoginRespond(login_result));
                return true;
            }

        }
    }
    else if(type == 2)
    {
        int login_result = DbServer::SignIn(user);
        if(login_result == Result::REGIST_SUCCESS)
        {
            localNextPendingConnection->sendTextMessage(JsonHelper::LoginRespond(login_result));
            return true;
        }
    }
    return false;
}

void DispatcherService::PushMessageToQuene(const QString &msg)
{
    QString msgFormat = QString(msg);
    msgFormat.replace(" ","0X00");
    QString cmd = "LPUSH message_list /" + msgFormat + "/";
    //qDebug() << msg;
    DbHelper::RedisNoReturn(cmd);
}

void DispatcherService::PopMessageFromQuene()
{

    QString cmd = "RPOP message_list ";
    QString str = DbHelper::RedisReturn(cmd);
    str.replace("0X00"," ");
    str.remove(0,1);
    str.remove(-1,1);
    QString result = NULL;
    int resultInt = 0;
    if(str != "")
    {
        qDebug() << str;
        int cmd_type = JsonHelper::GetCommandType(str);
        if(cmd_type != 0){
            QString data = JsonHelper::GetMessageData(str);
            QJsonValue user_id;
            QJsonValue rece_id;
            //qDebug() << po.getMsg_content();
            switch(cmd_type)
            {
            case MessageType::GROUP_MSG:
                //QJsonValue user_id = JsonHelper::GetDataByKey(data,"user_id");
                //resultInt = DbServer::SendMsg(GroupMsgPo(data));
                user_id = JsonHelper::GetDataByKey(data,"user_id");
                result = DbServer::QueryGroupMsg(user_id.toInt());
                break;
            case MessageType::GROUP_QUERY:
                user_id = JsonHelper::GetDataByKey(data,"user_id");
                result = DbServer::QueryGourp(user_id.toInt());
                break;
            case MessageType::USER_QUERY:
                user_id = JsonHelper::GetDataByKey(data,"user_id");
                result = DbServer::QueryFriend(user_id.toInt());
                break;
            case MessageType::PRIVATE_MSG:
                user_id = JsonHelper::GetDataByKey(data,"user_id");
                result = DbServer::QueryUserMsg(user_id.toInt());
                break;
            case MessageType::USER_STATUS:
                break;
            case MessageType::USER_INFO_UPDATE:
                user_id = JsonHelper::GetDataByKey(data,"user_id");
                resultInt = DbServer::AlterUserInfo(UserPo(data));
                break;
            case MessageType::SEMD_MSG_GROUP:
                user_id = JsonHelper::GetDataByKey(data,"user_id");
                rece_id = JsonHelper::GetDataByKey(data,"frind_id");
                resultInt = DbServer::SendMsg(GroupMsgPo(data));
                user_server->SendMessage(DbServer::QueryGroupFriendId(rece_id.toInt()),str);
                break;
            case MessageType::SEND_MSG_PRIVATE:
                user_id = JsonHelper::GetDataByKey(data,"user_id");
                rece_id = JsonHelper::GetDataByKey(data,"frind_id");
                resultInt = DbServer::SendMsg(PrivateMsgPo(data));
                user_server->SendMessage(user_id.toInt(),str);
                break;
            case MessageType::ADD_FRIEND:
                user_id = JsonHelper::GetDataByKey(data,"user_id");
                rece_id = JsonHelper::GetDataByKey(data,"frind_id");
                resultInt = DbServer::AddFriend(user_id.toInt(),rece_id.toInt());
            case MessageType::ADD_GROUP:
                user_id = JsonHelper::GetDataByKey(data,"user_id");
                rece_id = JsonHelper::GetDataByKey(data,"frind_id");
                resultInt = DbServer::AddGroup(user_id.toInt(),rece_id.toInt());
            default:
                break;
            };
            if(result != NULL)
            {
                qDebug() << "result:" << user_id.toInt();
                user_server->SendMessage(user_id.toInt(),JsonHelper::PackMessage(user_id.toInt(),result));
            }
            else if(resultInt != 0)
            {
                qDebug() << "resultInt:" << user_id.toInt();
                user_server->SendMessage(user_id.toInt(),JsonHelper::PackMessage(user_id.toInt(),resultInt));
            }
            else
            {
                user_server->SendMessage(user_id.toInt(),"error");
            }
        }

    }
}
