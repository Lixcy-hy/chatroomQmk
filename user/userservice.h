#ifndef USERSERVICE_H
#define USERSERVICE_H

#include <QObject>
#include "usersession.h"
#include "tools/db/dbhelper.h"

class UserService : public QObject
{
    Q_OBJECT
public:
    explicit UserService(QObject *parent = nullptr);

    bool UserLogin(const int user_id,QWebSocket *&socket);
    bool UserLogout(const int user_id);

    bool GetUserStatus(const int user_id);
    bool SendMessage(const int user_id,const QString &msg);
    bool SendMessage(QList<int> user_ids,const QString &msg);
signals:
private:
    QList<UserSession> user_list;
};

#endif // USERSERVICE_H

