#ifndef DBHELPER_H
#define DBHELPER_H

#include <QObject>
#include <QSql>
#include <QSqlDatabase>
#include <QSettings>
#include <tools/hiredis-master/hiredis.h>
#include <QDebug>

class DbHelper : public QObject
{
    Q_OBJECT
public:
    explicit DbHelper(QObject *parent = nullptr);

    static QSqlDatabase DbConnect();

    static bool RedisNoReturn(const QString &cmd);

    static QString RedisReturn(const QString &cmd);

private:
    static redisContext* NoSqlConnect();
signals:

};

#endif // DBHELPER_H
