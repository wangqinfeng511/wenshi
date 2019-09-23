#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QThread>
#include <QString>
#include <QQmlContext>
#include "display_content_background.h"
#include "date_time_dial.h"
#include "api.h"
#include "src/wifi.h"
//#include "touch_event.h"
int main(int argc, char *argv[])
{
//    qputenv("QT_QPA_PLATFORM","eglfs");
    qputenv("QT_IM_MODULE", "qtvirtualkeyboard");
    qputenv("QT_QPA_PLATFORM","linuxfb:fb=/dev/fb1:size=480x320:tty=/dev/tty1:nographicsmodeswitch");
    qputenv("QT_QPA_FB_DISABLE_INPUT","1");
    qputenv("QT_QPA_GENERIC_PLUGINS","tslib:/dev/input/event0");
    qputenv("TSLIB_CONFFILE", "/usr/local/tslib/etc/ts.conf");
    qputenv("TSLIB_CALIBFILE","/usr/local/tslib/etc/pointercal");
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
//    app.addLibraryPath("/usr/local/qt5/plugins")
    QQmlApplicationEngine engine;
    Api api;
    wifi w_f;
    qmlRegisterType<display_content_background>("Dcb",1,0,"Dcb");
    qmlRegisterType<date_time_dial>("Date_time_dial",1,0,"Date_time_dial");
    engine.rootContext()->setContextProperty("Api",&api);
    engine.rootContext()->setContextProperty("Wifi",&w_f);
    engine.load(QUrl(QStringLiteral("qrc:qml/main.qml")));
//    engine.load("qml/main.qml");
    if (engine.rootObjects().isEmpty())
        return -1;
    return app.exec();
}
//按结构体返回{温度,湿度,错误码}
