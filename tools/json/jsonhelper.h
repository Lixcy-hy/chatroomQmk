#ifndef JSONHELPER_H
#define JSONHELPER_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "tools/enum/MessageTypeEnum.h"

class JsonHelper : public QObject
{
    Q_OBJECT
public:
    explicit JsonHelper(QObject *parent = nullptr);

    static QString LoginRespond(const int result,const int user_id);

    static int GetCommandType(const QString &msg);

    static QString GetMessageData(const QString &msg);

    static QJsonValue GetDataByKey(const QString &msg,const QString &key);

    static QString PackMessage(const int type,const QString &result);
    //static
    static QString PackMessage(const int type, const int &result);
signals:

};

#endif // JSONHELPER_H
