#ifndef MESSAGEANALY_H
#define MESSAGEANALY_H

#include <QObject>
#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include "tools/enum/MessageTypeEnum.h"

class MessageAnaly : public QObject
{
    Q_OBJECT
public:
    explicit MessageAnaly(QObject *parent = nullptr);

    static int AnalyType(const QString &json);
    static QString GetData(const QString &json);
signals:

};

#endif // MESSAGEANALY_H
