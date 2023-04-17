#ifndef USERPO_H
#define USERPO_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>

#include <QDebug>

class UserPo : public QObject
{
    Q_OBJECT
public:
    explicit UserPo(QObject *parent = nullptr);

    UserPo(const QString &json);
    UserPo(const int user_id,const QString& password);


    void PrintParam();
    int getUser_id() const;
    QString getNickname() const;
    QString getPassword() const;
    int getSex() const;
    QString getEmail() const;


    const QString &getAvatar() const;

signals:


private:
    int user_id;
    QString nickname;
    QString password;
    int sex;
    QString email;
    QString avatar;
};

#endif // USERPO_H
