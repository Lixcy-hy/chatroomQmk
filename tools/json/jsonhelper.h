#ifndef JSONHELPER_H
#define JSONHELPER_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include "tools/enum/MessageTypeEnum.h"

class JsonHelper : public QObject
{
    Q_OBJECT
public:
    explicit JsonHelper(QObject *parent = nullptr);

    static QString LoginRespond(const int result);

    static int GetCommandType(const QString &msg);

    static QString GetMessageData(const QString &msg);

    static QJsonValue GetDataByKey(const QString &msg,const QString &key);

    //static
signals:

};

#endif // JSONHELPER_H
