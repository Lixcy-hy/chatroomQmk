#include "messageanaly.h"

MessageAnaly::MessageAnaly(QObject *parent)
    : QObject{parent}
{

}

int MessageAnaly::AnalyType(const QString &json)
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
                return value.toInt();
            }
        }
        else
        {
            qDebug() << "Messagetype analy fail";
            return 0;
        }
    }
    else
    {
        qDebug() <<  "Messagetype analy fail";
        return 0;
    }
}

QString MessageAnaly::GetData(const QString &json)
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
            if (object_id.contains("data"))
            {
                QJsonValue value = object_id.value("data");
                if (value.isString()) {
                    return value.toString();
                }
            }
        }
        else
        {
            qDebug() <<  "Messagedata analy fail";
            return 0;
        }
    }
    else
    {
        qDebug() <<  "Messagedata analy fail";
        return 0;
    }
}
