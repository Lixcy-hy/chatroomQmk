#include "privatemsgpo.h"

PrivateMsgPo::PrivateMsgPo(QObject *parent)
    : QObject{parent}
{

}

int PrivateMsgPo::getMsg_id() const
{
    return msg_id;
}

int PrivateMsgPo::getSender_user_id() const
{
    return sender_user_id;
}

int PrivateMsgPo::getReceiver_user_id() const
{
    return receiver_user_id;
}

QString PrivateMsgPo::getMsg_content() const
{
    return msg_content;
}

QDateTime PrivateMsgPo::getMsg_date() const
{
    return msg_date;
}

void PrivateMsgPo::PrintParam()
{
    qDebug() << msg_id << sender_user_id << receiver_user_id << msg_content << msg_date;
}

PrivateMsgPo::PrivateMsgPo(const QString &json)
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
            if (object_id.contains("msg_id"))
            {
                QJsonValue value = object_id.value("msg_id");
                int strName = value.toInt();
                this->msg_id = strName;
                //qDebug() << "id : " << strName;

            }
            // JSON 文档为对象
            QJsonObject object_nickname = document.object();  // 转化为对象
            if (object_nickname.contains("sender_user_id"))
            {
                QJsonValue value = object_id.value("sender_user_id");
                int strName = value.toInt();
                this->sender_user_id = strName;
                //qDebug() << "id : " << strName;
            }
            // JSON 文档为对象
            QJsonObject object_pwd = document.object();  // 转化为对象
            if (object_pwd.contains("receiver_user_id"))
            {
                QJsonValue value = object_id.value("receiver_user_id");
                int strName = value.toInt();
                this->receiver_user_id = strName;
                //qDebug() << "id : " << strName;
            }
            QJsonObject object_sex = document.object();  // 转化为对象
            if (object_sex.contains("msg_content"))
            {
                QJsonValue value = object_pwd.value("msg_content");
                if (value.isString()) {
                    QString strName = value.toString();
                    this->msg_content = strName;
                    //qDebug() << "Name : " << strName;
                }
            }
            QJsonObject object_email = document.object();  // 转化为对象
            if (object_email.contains("msg_date"))
            {
                QJsonValue value = object_pwd.value("msg_date");
                if (value.isString()) {
                    QString strName = value.toString();
                    this->msg_date.fromString(strName,"yyyy-MM-dd hh:mm:ss");
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
