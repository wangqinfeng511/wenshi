#ifndef DATE_TIME_DIAL_H
#define DATE_TIME_DIAL_H
#include <QQuickPaintedItem>
#include <QPainter>
#include <QObject>

class date_time_dial:public QQuickPaintedItem
{
    Q_OBJECT
public:
    date_time_dial();
    void paint(QPainter *painter);
    Q_INVOKABLE void update_dial();
    Q_PROPERTY(int shi READ Read_Shi WRITE Set_Shi)
    int Read_Shi(){
        return xiao_shi;
    }
    void Set_Shi(int shi){
        xiao_shi=shi;
    };
private:
    QPainter *m_painter;
    QPainterPath path;
    int box_width;
    int box_heigth;
    int box_width_center;
    int box_heigth_center;
    int kedu;
    int xiao_shi=0;
    QPointF wai_ce;
    QPointF nei_ce;
    QPen pen;
    QFont font;
//signals:
//    void update();
};

#endif // DATE_TIME_DIAL_H
