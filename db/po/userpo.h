#ifndef USERPO_H
#define USERPO_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>

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
    QString getSex() const;
    QString getEmail() const;

signals:


private:
    int user_id;
    QString nickname;
    QString password;
    QString sex;
    QString email;
};

#endif // USERPO_H
