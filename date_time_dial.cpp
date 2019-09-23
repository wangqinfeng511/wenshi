#include "date_time_dial.h"
#include <QQuickPaintedItem>
#include <QPainterPath>
#include <QPen>
#include <QPainter>
#include <QDateTime>
#include <math.h>
date_time_dial::date_time_dial()
{

}
void date_time_dial::paint(QPainter *painter){
    m_painter=painter;
    update_dial();
}
void date_time_dial::update_dial(){
    box_width=width();
    box_heigth=height();
    box_width_center=box_heigth/2;
    box_heigth_center=box_heigth/2;
    kedu=(360/24);
//    比如9点
//    QDateTime day=QDateTime::currentDateTime();
//    if(hh==0){
//           hh=day.toString("hh").toInt();
//    }
    int pianyikedu=kedu*(24-xiao_shi);
    for(int i=0;i<24;i++){
          if(i==xiao_shi){
              wai_ce.setX(sin((i*kedu+180+pianyikedu)*3.1415/180)*(box_heigth/2*0.8)+box_width_center-15);
              wai_ce.setY(cos((i*kedu+180+pianyikedu)*3.1415/180)*(box_heigth/2*0.8)+box_heigth_center+15);
              pen.setColor(qRgba(255,0,0,255));
              m_painter->setPen(pen);
              font.setPixelSize(30);
              m_painter->setFont(font);
              m_painter->drawText(wai_ce,QString("%1").arg(i));
          }else {
              wai_ce.setX(sin((i*kedu+180+pianyikedu)*3.1415/180)*(box_heigth/2*0.8)+box_width_center-10);
              wai_ce.setY(cos((i*kedu+180+pianyikedu)*3.1415/180)*(box_heigth/2*0.8)+box_heigth_center+10);
              pen.setColor(qRgba(230,230,230,255));
              m_painter->setPen(pen);
//              m_painter->save();
//              m_painter->translate(wai_ce);
//              m_painter->rotate(30);
              font.setPixelSize(20);
              m_painter->setFont(font);
              m_painter->drawText(wai_ce,QString("%1").arg(i));
//              m_painter->restore();
//              m_painter->translate(0,0);
            }
    }
//    kedu=360/12;
    for (int i=0;i<24;i++){
            wai_ce.setX(sin(i*kedu*3.1415/180)*(box_width/2*0.65)+box_width_center);
            wai_ce.setY(cos(i*kedu*3.1415/180)*(box_heigth/2*0.65)+box_heigth_center);
            nei_ce.setX(sin(i*kedu*3.1415/180)*(box_width/2*0.6)+box_width_center);
            nei_ce.setY(cos(i*kedu*3.1415/180)*(box_heigth/2*0.6)+box_heigth_center);
            if(i%6==0){
                pen.setWidth(3);
                path.moveTo(nei_ce);
                path.lineTo(wai_ce);
                pen.setColor(qRgba(230,230,230,255));
                m_painter->setPen(pen);
                m_painter->drawPath(path);
            }else {
                int x=sin(i*kedu*3.1415/180)*(box_width/2*0.63)+box_width_center;
                int y=cos(i*kedu*3.1415/180)*(box_heigth/2*0.63)+box_heigth_center;
                m_painter->drawEllipse(x,y,3,3);
                }
    }
}

