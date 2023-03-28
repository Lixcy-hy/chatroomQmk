#ifndef YAMLANALYSE_H
#define YAMLANALYSE_H

#include <QObject>
#include <QMap>
class YamlAnalyse : public QObject
{
    Q_OBJECT
public:
    explicit YamlAnalyse(QObject *parent = nullptr);


    // 根据文件获取变量

    // sql服务器参数读取
    static QMap<QString,QString> GetMySqlParam();
    // nosql服务器参数读取
signals:

};

#endif // YAMLANALYSE_H
