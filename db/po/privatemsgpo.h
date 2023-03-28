#ifndef PRIVATEMSGPO_H
#define PRIVATEMSGPO_H

#include <QDate>
#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>

class PrivateMsgPo : public QObject
{
    Q_OBJECT
public:
    explicit PrivateMsgPo(QObject *parent = nullptr);

    int getMsg_id() const;
    int getSender_user_id() const;
    int getReceiver_user_id() const;
    QString getMsg_content() const;
    QDateTime getMsg_date() const;

    void PrintParam();

    PrivateMsgPo(const QString &json);
signals:
private:
    int msg_id;
    int sender_user_id;
    int receiver_user_id;
    QString msg_content;
    QDateTime msg_date = QDateTime::currentDateTime();

};

#endif // PRIVATEMSGPO_H
