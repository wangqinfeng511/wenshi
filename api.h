#ifndef API_H
#define API_H
#include <QObject>
#include <QJsonObject>
struct wen_shi{
    QString wen;
    QString shi;
    QString error;
};
class Api : public QObject
{
    Q_OBJECT
public:
    explicit Api(QObject *parent = nullptr);

signals:
     void date_time_update(QJsonObject data);
public slots:
         void get_time();
         wen_shi get_wen_shi();
private:
         wen_shi w_s;
};

#endif // API_H
