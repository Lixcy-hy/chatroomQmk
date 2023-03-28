#include "usersession.h"

UserSession::UserSession(QObject *parent)
    : QObject{parent}
{

}

UserSession::UserSession(const int id, QWebSocket *&socket)
{
    this->user_id = id;
    this->socket = socket;
}

UserSession::UserSession(const int id)
{
    this->user_id = id;
}

UserSession::UserSession(const UserSession &user)
{
    this->user_id = user.user_id;
    this->socket = user.socket;
}

UserSession UserSession::operator=(const UserSession &user)
{
    return user;
}

//UserSession::~UserSession()
//{
//    this->socket->close(QWebSocketProtocol::CloseCodeNormal,"user offline");
//}

bool UserSession::operator==(const UserSession &user)
{
    if(this->user_id == user.user_id)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool UserSession::SendMsg(const QByteArray &msg)
{
    this->socket->sendBinaryMessage(msg);
}

bool UserSession::SendMsg(const QString &msg)
{
    int result = this->socket->sendTextMessage(msg);
    if(result != 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool UserSession::LogOut()
{
    this->socket->close(QWebSocketProtocol::CloseCodeNormal,"user offline");
}
