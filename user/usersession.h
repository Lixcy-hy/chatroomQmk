#ifndef USERSESSION_H
#define USERSESSION_H

#include <QObject>
#include <QWebSocket>

class UserSession : public QObject
{
    Q_OBJECT
public:
    explicit UserSession(QObject *parent = nullptr);
    UserSession(const int id,QWebSocket *&socket);
    UserSession(const int id);
    UserSession(const UserSession& user);
    UserSession operator=(const UserSession& user);
    //~UserSession();
    bool operator==(const UserSession& user);

    bool SendMsg(const QByteArray &msg);
    bool SendMsg(const QString &msg);

    bool LogOut();


signals:
private:
    int user_id;
    QWebSocket * socket;
};

#endif // USERSESSION_H
