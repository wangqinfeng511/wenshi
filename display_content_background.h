#ifndef DISPLAY_CONTENT_BACKGROUND_H
#define DISPLAY_CONTENT_BACKGROUND_H
#include <QQuickPaintedItem>
#include<QPainter>
#include <QObject>
class display_content_background:public QQuickPaintedItem
{
    Q_OBJECT
public:
    display_content_background();
    void paint(QPainter *painter);
    void update_painter();
private:
    QPainter *m_painter;
};

#endif // DISPLAY_CONTENT_BACKGROUND_H
