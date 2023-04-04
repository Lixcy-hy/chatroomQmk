#ifndef GROUPMSGPO_H
#define GROUPMSGPO_H

#include <QDate>
#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>

#include <QDebug>

class GroupMsgPo : public QObject
{
    Q_OBJECT
public:
    explicit GroupMsgPo(QObject *parent = nullptr);
    GroupMsgPo(const QString &json);

    int getMsg_id() const;
    int getSender_user_id() const;
    int getReceiver_user_id() const;
    QString getMsg_content() const;
    QDateTime getMsg_date() const;

signals:
private:
    int msg_id;
    int sender_user_id;
    int receiver_user_id;
    QString msg_content;
    QDateTime msg_date = QDateTime::currentDateTime();
};

#endif // GROUPMSGPO_H
