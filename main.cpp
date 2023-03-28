#include <QCoreApplication>
#include <QSqlQuery>
#include <QDebug>
#include <QWebSocket>
#include "tools/dispatcher/dispatcherservice.h"
#include "user/userservice.h"

#include "db/dbserver.h"
#include "db/po/userpo.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    UserService * use = new UserService();
//    QWebSocket * user = new QWebSocket();
//    use->UserLogin(1,user);
//    DispatcherService* dispatcher_server = new DispatcherService();

//    DbServer * db = new DbServer();

//    QString user = "{\"user_id\":4,\"nickname\":\"张三\",\"password\":\"112233\"}";
//    QString privatePo = "{\"msg_content\":\"test msg 3\",\"sender_user_id\":3,\"receiver_user_id\":2}";
    GroupMsgPo poo = GroupMsgPo("{\"msg_content\":\"dispatcher test\",\"receiver_user_id\":1,\"sender_user_id\":2}");
    auto localSendMsg = DbServer::SendMsg(poo);
    qDebug() << Result(localSendMsg);
//    PrivateMsgPo ppo(privatePo);
//    UserPo po(user);
//    po.PrintParam();
//    ppo.PrintParam();
//    auto localSignIn = DbServer::SignIn(po);
//    auto localSendMsg = DbServer::SendMsg(ppo);

    //db->LogIn(po);

//    db->QueryFriend(1);
    //qDebug() << localSignIn;
//    qDebug() << Result(localSendMsg);

    return a.exec();
}
