#include "jsonhelper.h"

JsonHelper::JsonHelper(QObject *parent)
    : QObject{parent}
{

}

QString JsonHelper::LoginRespond(const int result)
{
    QJsonObject root;
    QJsonObject data;
    data.insert("login_result",result);
    root.insert("message_type",MessageType::LOGIN);
    root.insert("data",data);
    QJsonDocument json = QJsonDocument(root);
    return json.toJson();
}

int JsonHelper::GetCommandType(const QString &msg)
{
    QJsonParseError jsonError;
    QJsonDocument document = QJsonDocument::fromJson(msg.toUtf8(),&jsonError);
    if(!document.isNull() && (jsonError.error == QJsonParseError::NoError))
    {
    // 解析未发生错误
        if (document.isObject())
        {
            // JSON 文档为对象
            QJsonObject object_id = document.object();  // 转化为对象
            if (object_id.contains("message_type"))
            {
                QJsonValue value = object_id.value("message_type");
                return value.toInt();

            }
        }
    }
}

QString JsonHelper::GetMessageData(const QString &msg)
{
    QJsonParseError jsonError;
    QJsonDocument document = QJsonDocument::fromJson(msg.toUtf8(),&jsonError);
    if(!document.isNull() && (jsonError.error == QJsonParseError::NoError))
    {
    // 解析未发生错误
        if (document.isObject())
        {
            // JSON 文档为对象
            QJsonObject object_id = document.object();  // 转化为对象
            if (object_id.contains("data"))
            {
                QJsonDocument json = QJsonDocument(object_id.value("data").toObject());
                return QString(json.toJson(QJsonDocument::Compact));
            }
        }
    }
}

QJsonValue JsonHelper::GetDataByKey(const QString &msg, const QString &key)
{
    QJsonParseError jsonError;
    QJsonDocument document = QJsonDocument::fromJson(msg.toUtf8(),&jsonError);
    if(!document.isNull() && (jsonError.error == QJsonParseError::NoError))
    {
    // 解析未发生错误
        if (document.isObject())
        {
            // JSON 文档为对象
            QJsonObject object_id = document.object();  // 转化为对象
            if (object_id.contains(key))
            {
                return object_id.value(key);
            }
        }
    }
}
