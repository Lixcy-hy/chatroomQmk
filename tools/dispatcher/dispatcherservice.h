#ifndef DISPATCHERSERVICE_H
#define DISPATCHERSERVICE_H

#include <QObject>
#include <QtWebSockets/QWebSocketServer>
#include <QTimer>
#include "db/dbserver.h"
#include "user/userservice.h"
#include "tools/json/jsonhelper.h"
#include "tools/db/dbhelper.h"
class DispatcherService : public QObject
{
    Q_OBJECT
public:
    explicit DispatcherService(QObject *parent = nullptr);

    // 数据分析函数
    // 接收消息
    bool RecMsg();
public slots:
    // 新连接(包含链接认证、用户认证、UID生成、reids入库等功能）
    bool NewConnect();
private:
    // 消息接收服务器
    QWebSocketServer * websocket_server;
    //DbServer * db_server;
    UserService * user_server;
    QTimer * timer;
signals:
    // 新号发送函数
private slots:
    void PushMessageToQuene(const QString& msg);
    void PopMessageFromQuene();

};

#endif // DISPATCHERSERVICE_H
