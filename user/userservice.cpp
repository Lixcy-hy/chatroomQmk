#include "userservice.h"

UserService::UserService(QObject *parent)
    : QObject{parent}
{
    qDebug() << "user server on!";
}

bool UserService::UserLogin(const int user_id, QWebSocket *&socket)
{
    QString login_str = "SET " + QString::number(user_id) + " 1";
    UserSession user = UserSession(user_id,socket);
    user_list.append(user);
    qDebug()<< "当前在线的用户数量为:" << user_list.size();
    // 用户断开将redis用户列表注销
    connect(socket,&QWebSocket::disconnected,[&user, this, user_id]()->void{
        this->UserLogout(user_id);
       qDebug() << QString::number(user_id) << "用户退出";
    });
    return DbHelper::RedisNoReturn(login_str);
}

bool UserService::UserLogout(const int user_id)
{
    QString login_str = "SET " + QString::number(user_id) + " 0";
    UserSession user = UserSession(user_id);
    int index = user_list.indexOf(user);
    //qDebug() << index;
    user_list[index].LogOut();
    user_list.removeAt(index);
    //user_list.contains(user);
    return DbHelper::RedisNoReturn(login_str);
}

bool UserService::GetUserStatus(const int user_id)
{
    QString login_str = "GET " + QString::number(user_id);
    QString replay = DbHelper::RedisReturn(login_str);
    if(replay == "1")
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool UserService::SendMessage(const int user_id, const QString &msg)
{
    try {
        //qDebug() << "result:" << msg;
        UserSession user = UserSession(user_id);
        int index = user_list.indexOf(user);
        if(index == -1)
        {
            qDebug() << "用户查询失败";
            return false;
        }
        qDebug() << "发送的信息为:" << msg <<"发送的用户下标为:" << index << "发送的用户为:" <<user_id;
        user_list[index].SendMsg(msg);
        return true;
    } catch (...)
    {
        return false;
    }
}

bool UserService::SendMessage(QList<int> user_ids, const QString &msg)
{
    try {
        QList<int>::Iterator it = user_ids.begin();
        for(;it!=user_ids.end();++it)
        {
            this->SendMessage(*it,msg);
        }
        return true;
    } catch (...)
    {
        return false;
    }
}
