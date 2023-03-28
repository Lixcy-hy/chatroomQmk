#ifndef DBSERVER_H
#define DBSERVER_H

#include <QObject>
#include <QThread>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "po/userpo.h"
#include "po./groupmsgpo.h"
#include "po/privatemsgpo.h"
#include "../tools/db/dbhelper.h"
#include "../tools/enum/ResultEnum.h"

#include <QSqlError>

class DbServer : public QThread
{
    Q_OBJECT
public:
    explicit DbServer(QObject *parent = nullptr);
    // 创建用户
    static int SignIn(const UserPo & user);
    // 用户登录认证
    static int LogIn(const UserPo & user);
    // 修改用户信息
    static int AlterUserInfo(const UserPo & user);
    // 发送信息(入库)
    static int SendMsg(const GroupMsgPo &po);

    static int SendMsg(const PrivateMsgPo &po);
    // 用户群组操作
    static int CreateGroup(const QString &group_name,const int &owner_id);
    static int AddGroup(const int &group_id,const int &user_id);
    // 用户好友操作
    static int AddFriend(const int &user_id,const int &friend_id);
    static int DeleteFriend(const int &user_id,const int &friend_id);

    // 用户关系查询
    static QString QueryFriend(const int &user_id);
    static QString QueryGourp(const int &user_id);
    // 查询消息信息(用户)
    static QString QueryUserMsg(const int &user_id);
    // 查询消息信息(群组)
    static QString QueryGroupMsg(const int &user_id);

signals:


    // QThread interface
protected:
    void run();
private:

};

#endif // DBSERVER_H
