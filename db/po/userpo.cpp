#include "userpo.h"

UserPo::UserPo(QObject *parent)
    : QObject{parent}
{

}

UserPo::UserPo(const QString &json)
{
    QJsonParseError jsonError;
    qDebug() << json;
    QJsonDocument document = QJsonDocument::fromJson(json.toUtf8(),&jsonError);
    if(!document.isNull() && (jsonError.error == QJsonParseError::NoError))
    {
    // 解析未发生错误
        if (document.isObject())
        {
            // JSON 文档为对象
            QJsonObject object_id = document.object();  // 转化为对象
            if (object_id.contains("user_id"))
            {
                QJsonValue value = object_id.value("user_id");
                int strName = value.toInt();
                this->user_id = strName;
                //qDebug() << "id : " << strName;

            }            // JSON 文档为对象
            QJsonObject object_nickname = document.object();  // 转化为对象
            if (object_nickname.contains("nickname"))
            {
                QJsonValue value = object_nickname.value("nickname");
                if (value.isString()) {
                    QString strName = value.toString();
                    this->nickname = strName;
                    //qDebug() << "Name : " << strName;
                }
            }            // JSON 文档为对象
            QJsonObject object_pwd = document.object();  // 转化为对象
            if (object_pwd.contains("password"))
            {
                QJsonValue value = object_pwd.value("password");
                if (value.isString()) {
                    QString strName = value.toString();
                    this->password = strName;
                    //qDebug() << "Name : " << strName;
                }
            }
            QJsonObject object_sex = document.object();  // 转化为对象
            if (object_sex.contains("sex"))
            {
                QJsonValue value = object_pwd.value("sex");
                this->password = value.toInt();
                //qDebug() << "Name : " << strName;

            }
            QJsonObject object_email = document.object();  // 转化为对象
            if (object_email.contains("email"))
            {
                QJsonValue value = object_pwd.value("email");
                if (value.isString()) {
                    QString strName = value.toString();
                    this->email = strName;
                    //qDebug() << "Name : " << strName;
                }
            }
            QJsonObject object_avatar = document.object();  // 转化为对象
            if (object_avatar.contains("avatar"))
            {
                QJsonValue value = object_pwd.value("avatar");
                if (value.isString()) {
                    QString strName = value.toString();
                    this->avatar = strName;
                    //qDebug() << "Name : " << strName;
                }
            }
        }
        else
        {
            qDebug() << "UserPo Json analy fail";
        }
    }
    else
    {
        qDebug() << "UserPo Json analy fail";
    }
}

UserPo::UserPo(const int user_id, const QString &password)
{
    this->user_id = user_id;
    this->password = password;
}

void UserPo::PrintParam()
{
    qDebug() << user_id << nickname << password;
}

int UserPo::getUser_id() const
{
    return user_id;
}

QString UserPo::getNickname() const
{
    return nickname;
}

QString UserPo::getPassword() const
{
    return password;
}

int UserPo::getSex() const
{
    return sex;
}

QString UserPo::getEmail() const
{
    return email;
}

const QString &UserPo::getAvatar() const
{
    return avatar;
}

