#ifndef SOCKETMANAGER_H
#define SOCKETMANAGER_H

#include <QObject>

class SocketManager : public QObject
{
    Q_OBJECT
public:
    explicit SocketManager(QObject *parent = nullptr);

    // 新连接入内存管理
signals:

};

#endif // SOCKETMANAGER_H
