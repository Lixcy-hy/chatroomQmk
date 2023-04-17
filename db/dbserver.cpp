#include "dbserver.h"
#include "qdebug.h"

DbServer::DbServer(QObject *parent)
    : QThread{parent}
{


    //QString localRedisReturn = DbHelper::RedisReturn("GET test2");

    qDebug() << "db server on!";
}



int DbServer::SignIn(const UserPo &user)
{

    QSqlDatabase db = DbHelper::DbConnect();
    if(db.isOpen()){
        QSqlQuery sq(db);
        //QString sql = "insert into im_user(user_id,password,nickname,sex,email) value(:user_id,:password);";
        QString sql = "insert into im_user(user_id,password,nickname) value(:user_id,:password,:nickname);";
        sq.prepare(sql);
        sq.bindValue(":user_id",user.getUser_id());
        sq.bindValue(":password",user.getPassword());
        sq.bindValue(":nickname",user.getUser_id());
        if(sq.exec())
        {
            db.close();
            return Result::REGIST_SUCCESS;
        }
        else
        {
            db.close();
            return Result::REGIST_FAIL;
        }

    }
}

int DbServer::LogIn(const UserPo &user)
{
    QSqlDatabase db = DbHelper::DbConnect();

    if(db.isOpen())
    {
        QSqlQuery sq(db);
        QString sql = "select * from im_user where user_id = " + QString::number(user.getUser_id()) + " and password = " + user.getPassword() + ";";
        if(sq.exec(sql))
        {
            if(sq.size() != 0)
            {
                if(sq.size() != 0)
                {
                    db.close();
                    return Result::LOGIN_SUCCESS;
                }
                else
                {
                    db.close();
                    return Result::PASSWORD_ERROR;
                }
            }
            else
            {
                db.close();
                return Result::ACCOUNT_NOT_FOUND;
            }
        }
        else
        {
            qDebug() << "exec fails";
        }
    }
    else
    {
        qDebug() << "open fails";
        return Result::CONNECT_ERROR;
    }


}

QString DbServer::QuerySelfData(const int user_id)
{
    QSqlDatabase db = DbHelper::DbConnect();

    if(db.isOpen())
    {
        QSqlQuery sq(db);
        QString sql = "SELECT JSON_OBJECT('user_id',user_id, 'nickname',nickname, 'sex',sex, 'email',email,'avatar',avatar) FROM im_user WHERE user_id = :user_id;";
        sq.prepare(sql);
        sq.bindValue(":user_id",user_id);
        sq.exec();
        sq.next();
        if(!sq.value(0).isNull())
        {
            qDebug() << sq.value(0);
            return sq.value(0).toString();
        }
        else
        {
            return nullptr;
        }
    }
    else
    {
        qDebug() << "open fails";
        return nullptr;
    }
}

int DbServer::AlterUserInfo(const UserPo &user)
{
    QSqlDatabase db = DbHelper::DbConnect();

    if(db.isOpen()){
        QSqlQuery sq(db);
        QString sql = "update im_user set nickname=:nickname,sex=:sex,email=:email,avatar=:avatar where user_id=:user_id;";
        sq.prepare(sql);
        sq.bindValue(":user_id",user.getUser_id());
        sq.bindValue(":nickname",user.getNickname());
        sq.bindValue(":sex",user.getSex());
        sq.bindValue(":email",user.getEmail());
        sq.bindValue(":avatar",user.getAvatar());
        if(sq.exec())
        {
            db.close();
            return Result::UPDATE_SUCCESS;
        }
        else
        {
            db.close();
            return Result::UPDATE_FAIL;
        }

    }
    else
    {
        db.close();
        return Result::CONNECT_ERROR;
    }
    db.close();
}


int DbServer::SendMsg(const GroupMsgPo &po)
{
    QSqlDatabase db = DbHelper::DbConnect();

    if(db.isOpen()){
        QSqlQuery sq(db);
        QString sql = "insert into im_msg_group(sender_user_id,receiver_user_id,msg_date,msg_content) value(:sender_user_id,:receiver_user_id,:msg_date,:msg_content);";
        sq.prepare(sql);
        //sq.bindValue(":msg_id",po.getMsg_id());
        sq.bindValue(":sender_user_id",po.getSender_user_id());
        sq.bindValue(":receiver_user_id",po.getReceiver_user_id());
        sq.bindValue(":msg_date",po.getMsg_date().toString("yyyy-MM-dd hh:mm:ss"));
        sq.bindValue(":msg_content",po.getMsg_content());

        if(!sq.exec())
        {
            qDebug() << "error:" << sq.lastError();
        }
        if(sq.size() != 0)
        {
            db.close();
            return Result::UPDATE_SUCCESS;
        }
        else
        {
            db.close();
            return Result::UPDATE_FAIL;
        }

    }
    else
    {
        db.close();
        return Result::CONNECT_ERROR;
    }
    db.close();
}

int DbServer::SendMsg(const PrivateMsgPo &po)
{
    QSqlDatabase db = DbHelper::DbConnect();

    if(db.isOpen()){
        QSqlQuery sq(db);
        QString sql = "insert into im_msg_private(sender_user_id,receiver_user_id,msg_date,msg_content) value(:sender_user_id,:receiver_user_id,:msg_date,:msg_content);";
        sq.prepare(sql);
        //sq.bindValue(":msg_id",po.getMsg_id());
        sq.bindValue(":sender_user_id",po.getSender_user_id());
        sq.bindValue(":receiver_user_id",po.getReceiver_user_id());
        sq.bindValue(":msg_date",po.getMsg_date().toString("yyyy-MM-dd hh:mm:ss"));
        sq.bindValue(":msg_content",po.getMsg_content());
        sq.exec();
        if(sq.size() != 0)
        {
            db.close();
            return Result::UPDATE_SUCCESS;
        }
        else
        {
            db.close();
            return Result::UPDATE_FAIL;
        }

    }
    else
    {
        db.close();
        return Result::CONNECT_ERROR;
    }
    db.close();
}

int DbServer::CreateGroup(const QString &group_name, const int &owner_id)
{
    QSqlDatabase db = DbHelper::DbConnect();

    if(db.isOpen()){
        QSqlQuery sq(db);
        QString sql = "insert into im_group(group_name,group_create_time,group_owner) value(:group_name,:group_create_time,:group_owner);";
        sq.prepare(sql);
        sq.bindValue(":group_name",group_name);
        sq.bindValue(":group_create_time",QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        sq.bindValue(":group_owner",owner_id);
        if(sq.exec())
        {
            // return Result::UPDATE_SUCCESS;
            qDebug() << "创建群组成功";
            QSqlQuery ug(db);
            QString us_sql = "insert into im_user_group(group_id,user_id) value((select group_id from im_group order by group_id desc limit 1),:user_id);";
            ug.prepare(us_sql);
            ug.bindValue(":user_id",owner_id);            
            if(ug.exec())
            {
                db.close();
                return Result::UPDATE_SUCCESS;
            }
            else
            {
                db.close();
                return Result::UPDATE_FAIL;
            }
        }
        else
        {
            db.close();
            return Result::UPDATE_FAIL;
        }

    }
    else
    {
        db.close();
        return Result::CONNECT_ERROR;
    }
    db.close();
}

int DbServer::AddGroup(const int &group_id, const int &user_id)
{
    QSqlDatabase db = DbHelper::DbConnect();

    if(db.isOpen()){
        QSqlQuery sq(db);
        QString sql = "insert into im_user_group(group_id,user_id) value(:group_id,:user_id);";
        sq.prepare(sql);
        sq.bindValue(":group_id",group_id);
        sq.bindValue(":user_id",user_id);
        if(sq.exec())
        {
            db.close();
            return Result::UPDATE_SUCCESS;
        }
        else
        {
            db.close();
            return Result::UPDATE_FAIL;
        }

    }
    else
    {
        db.close();
        return Result::CONNECT_ERROR;
    }
    db.close();
}

int DbServer::AddFriend(const int &user_id, const int &friend_id)
{
    QSqlDatabase db = DbHelper::DbConnect();

    if(db.isOpen()){
        QSqlQuery sq(db);
        QString sql = "insert into im_friend(user_id,friend_id) value(:user_id,:friend_id);";
        sq.prepare(sql);
        sq.bindValue(":user_id",user_id);
        sq.bindValue(":friend_id",friend_id);
        if(sq.exec())
        {
            db.close();
            return Result::UPDATE_SUCCESS;
        }
        else
        {
            db.close();
            return Result::UPDATE_FAIL;
        }

    }
    else
    {
        db.close();
        return Result::CONNECT_ERROR;
    }
    db.close();
}

QString DbServer::QueryFriend(const int &user_id)
{
    QSqlDatabase db = DbHelper::DbConnect();

    if(db.isOpen()){
        QSqlQuery sq(db);
        QString sql = "SELECT CONCAT('[', GROUP_CONCAT(JSON_OBJECT('user_id',user_id, 'nickname',nickname, 'sex',sex, 'email',email,'avatar',avatar)), ']')FROM im_user WHERE user_id IN (	SELECT 	friend_id FROM im_friend WHERE user_id = :user_id) ";
        sq.prepare(sql);
        sq.bindValue(":user_id",user_id);
        //sq.bindValue(":receiver_user_id",user_id);
        sq.exec();
        sq.next();
        qDebug() << sq.value(0);

        db.close();
        return sq.value(0).toString();
    }
    else
    {
        db.close();
        return QString(Result::CONNECT_ERROR);
    }

    db.close();
}

QString DbServer::QueryGourp(const int &user_id)
{
    QSqlDatabase db = DbHelper::DbConnect();

    if(db.isOpen()){
        QSqlQuery sq(db);
        //QString sql = "SELECT CONCAT('[', GROUP_CONCAT(JSON_OBJECT('group_id', group_id)), ']')FROM im_user_group WHERE user_id = :user_id;";
        QString sql = "SELECT CONCAT('[', GROUP_CONCAT(JSON_OBJECT('group_id', group_id,'nickname',group_name)), ']') FROM im_group ig WHERE group_id IN (SELECT group_id FROM im_user_group iug WHERE user_id = :user_id);";
        sq.prepare(sql);
        sq.bindValue(":user_id",user_id);
        sq.exec();
        sq.next();
        qDebug() << sq.value(0);

        db.close();
        return sq.value(0).toString();
    }
    else
    {
        db.close();
        return QString(Result::CONNECT_ERROR);
    }

    db.close();
}


QString DbServer::QueryUserMsg(const int &user_id)
{
    QSqlDatabase db = DbHelper::DbConnect();

    if(db.isOpen()){
        QSqlQuery sq(db);
        //QString sql = "SELECT CONCAT('[', GROUP_CONCAT(JSON_OBJECT('msg_id', msg_id, 'sender_user_id', sender_user_id, 'receiver_user_id', receiver_user_id, 'msg_date', msg_date, 'msg_content', msg_content)), ']') FROM	im_msg_private WHERE sender_user_id = :sender_user_id OR receiver_user_id = :receiver_user_id;  ";
        QString sql = "SELECT  CONCAT('[', GROUP_CONCAT(JSON_OBJECT('user_data',JSON_OBJECT('avatar',avatar,'nickname',nickname),'msg_id', msg_id, 'sender_user_id', sender_user_id, 'receiver_user_id', receiver_user_id, 'msg_date', msg_date, 'msg_content', msg_content)), ']') FROM im_msg_private imp join im_user iu2 on imp.sender_user_id = iu2.user_id WHERE sender_user_id =:sender_user_id OR receiver_user_id = :receiver_user_id;";
        sq.prepare(sql);
        sq.bindValue(":sender_user_id",user_id);
        sq.bindValue(":receiver_user_id",user_id);
        sq.exec();
        sq.next();
        //qDebug() << sq.value(0);

        db.close();
        return sq.value(0).toString();
    }
    else
    {
        db.close();
        return QString(Result::CONNECT_ERROR);
    }

    db.close();
}

QString DbServer::QueryGroupMsg(const int &user_id)
{
    QSqlDatabase db = DbHelper::DbConnect();

    if(db.isOpen()){
        QSqlQuery sq(db);
        //QString sql = "SELECT CONCAT('[',GROUP_CONCAT( JSON_OBJECT('msg_id', msg_id,'sender_user_id', sender_user_id, 'receiver_user_id', receiver_user_id, 'msg_date', msg_date, 'msg_content', msg_content)), ']') FROM im_msg_group WHERE receiver_user_id in(SELECT group_id FROM im_user_group	WHERE user_id = :user_id); ";
        QString sql = "SELECT CONCAT('[',GROUP_CONCAT( JSON_OBJECT('user_data',JSON_OBJECT('avatar',avatar,'nickname',nickname),'msg_id', msg_id,'sender_user_id', sender_user_id, 'receiver_user_id', receiver_user_id, 'msg_date', msg_date, 'msg_content', msg_content)), ']') FROM im_msg_group imp  join im_user iu2 on imp.sender_user_id = iu2.user_id WHERE receiver_user_id in(SELECT group_id FROM im_user_group WHERE user_id = :user_id);";
        sq.prepare(sql);
        sq.bindValue(":user_id",user_id);
        sq.exec();
        if(sq.first())
        {
            db.close();
            return sq.value(0).toString();
        }
        db.close();
        return 0;
    }
    else
    {
        db.close();
        return QString(Result::CONNECT_ERROR);
    }

}

QList<int> DbServer::QueryUserFriendId(const int &user_id)
{
    QSqlDatabase db = DbHelper::DbConnect();

    if(db.isOpen()){
        QSqlQuery sq(db);
        QString sql = "SELECT user_id FROM im_user";
        sq.prepare(sql);
        sq.bindValue(":user_id",user_id);
        sq.exec();
        if(sq.first())
        {
            db.close();
        }
        db.close();
    }
    else
    {
        db.close();
    }

}

QList<int> DbServer::QueryGroupFriendId(const int &group_id)
{
    QSqlDatabase db = DbHelper::DbConnect();

    QList<int> list;
    if(db.isOpen()){
        QSqlQuery sq(db);
        QString sql = "SELECT user_id FROM im_user_group iug  WHERE group_id = :group_id;";
        sq.prepare(sql);
        sq.bindValue(":group_id",group_id);
        if(sq.exec())
        {
            while(sq.next())
            {
                list.append(sq.value(0).toInt());
                qDebug() << sq.value(0).toInt();
            }
            return list;
        }
        return list;
}
}

void DbServer::run()
{

}
