#include "display_content_background.h"
#include <QPainter>
#include <QPainterPath>
#include <QRectF>
#include <QDebug>
#include<Qt>
display_content_background::display_content_background()
{

}
void display_content_background::paint(QPainter *painter){
    m_painter=painter;
    update_painter();
}
void display_content_background::update_painter(){

    QBrush brush; //笔刷
    QPen pen;//画笔
    pen.setColor(qRgba(0,0,0,2));
    pen.setWidth(0);
    int x_center=(width()-height())/2;
    int y_center=0;
    int yuan_width=height()-5;
    int yuan_height=height()-5;
    int yuan_banjing=height()/2;
    m_painter->setPen(pen);
    m_painter->setRenderHints(QPainter::Antialiasing);
    QRectF yuan(x_center,y_center,yuan_width,yuan_height);
    //辉光渐变
    QRadialGradient gradient(x_center+yuan_banjing,y_center+yuan_banjing,yuan_banjing);//圆点xy,半径,
    gradient.setColorAt(0,qRgba(170,170,170,255));
    gradient.setColorAt(1,qRgba(255,255,255,255));
    brush=QBrush(gradient);
    brush.setStyle(Qt::RadialGradientPattern);
    m_painter->setBrush(brush);
//    m_painter->drawEllipse(yuan);
    m_painter->drawChord(yuan,0,180*16);
    m_painter->drawArc(yuan,0,180*16);//起始角度,结束角度;
    brush=QBrush();
    brush.setColor(qRgba(30,30,30,255));
    brush.setStyle(Qt::SolidPattern);
    m_painter->setBrush(brush);
    m_painter->drawChord(yuan,180*16,180*16);
    //

    pen.setColor(qRgba(150,150,150,255));
    pen.setWidth(3);
    QPainterPath path;
    path.moveTo(x_center+yuan_height/2,yuan_height/2+10);
    path.lineTo(x_center+yuan_height/2,yuan_height-10);
    m_painter->setPen(pen);
    m_painter->drawPath(path);


}
