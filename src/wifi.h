#ifndef WIFI_H
#define WIFI_H
#include <QObject>
#include <QJsonObject>
#include <QProcess>
class wifi : public QObject
{
    Q_OBJECT
public:
    explicit wifi(QObject *parent = nullptr);
    Q_INVOKABLE  QJsonObject get_ssid();
signals:
    void update_status(QJsonObject status);
public slots:
    void get_status();

private:
//        QProcess  get;
};

#endif // WIFI_H
