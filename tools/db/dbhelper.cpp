#include "dbhelper.h"

DbHelper::DbHelper(QObject *parent)
    : QObject{parent}
{
}

QSqlDatabase DbHelper::DbConnect()
{
    QSettings * config = new QSettings(":/config/config.ini",QSettings::IniFormat);

    QSqlDatabase localAddDatabase = QSqlDatabase::addDatabase("QMYSQL");

    localAddDatabase.setHostName(config->value("/MySql/host").toString());
    localAddDatabase.setDatabaseName(config->value("/MySql/db").toString());
    localAddDatabase.setPassword(config->value("/MySql/password").toString());
    localAddDatabase.setPort(config->value("/MySql/port").toInt());
    localAddDatabase.setUserName(config->value("/MySql/username").toString());

    localAddDatabase.open();

    return localAddDatabase;
}

bool DbHelper::RedisNoReturn(const QString &cmd)
{
    redisContext *redisContext = DbHelper::NoSqlConnect();

    redisReply * reply = (redisReply *)redisCommand(redisContext,cmd.toUtf8());

    qDebug() << reply->str;

    if(NULL == reply->str)
    {
        return false;
    }
    else
    {
        return true;
    }
}

QString DbHelper::RedisReturn(const QString &cmd)
{
    redisContext *redisContext = DbHelper::NoSqlConnect();

    redisReply * reply = (redisReply *)redisCommand(redisContext,cmd.toUtf8());

    return reply->str;
}

redisContext *DbHelper::NoSqlConnect()
{
    QSettings * config = new QSettings(":/config/config.ini",QSettings::IniFormat);
    //建立连接
    redisContext* pRedisContext= (redisContext*) redisConnect(config->value("/Redis/host").toString().toUtf8(),6379);
    QString auth = "AUTH " + config->value("/Redis/password").toString();
    //密码访问
    redisReply* reply = (redisReply *)redisCommand(pRedisContext, auth.toUtf8().data());

    //qDebug() << reply->str << config->value("/Redis/password").toString();

    return pRedisContext;
}
