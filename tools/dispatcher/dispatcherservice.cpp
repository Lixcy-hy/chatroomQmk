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
    QString cmd = "LPUSH message_list /" + msg + "/";
    qDebug() << msg;
    DbHelper::RedisNoReturn(cmd);
}

void DispatcherService::PopMessageFromQuene()
{

    QString cmd = "RPOP message_list ";
    QString str = DbHelper::RedisReturn(cmd);
    qDebug() << str;
    if(str != "")
    {
        int cmd_type = JsonHelper::GetCommandType(str);
        QString data = JsonHelper::GetMessageData(str);
        QJsonValue user_id = JsonHelper::GetDataByKey(data,"user_id");
        //qDebug() << po.getMsg_content();
        switch(cmd_type)
        {
        case MessageType::GROUP_MSG:
            //QJsonValue user_id = JsonHelper::GetDataByKey(data,"user_id");
            DbServer::SendMsg(GroupMsgPo(data));
            break;
        case MessageType::GROUP_QUERY:
            DbServer::QueryGroupMsg(user_id.toInt());
            break;
        case MessageType::USER_QUERY:
            DbServer::QueryFriend(user_id.toInt());
            break;
        case MessageType::PRIVATE_MSG:
            DbServer::QueryUserMsg(user_id.toInt());
            break;
        case MessageType::USER_STATUS:
            break;
        default:
            break;
        };

    }
}
