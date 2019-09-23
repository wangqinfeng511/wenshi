QT += quick
CONFIG += c++11
#LIBS += -lts
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
    display_content_background.cpp \
    date_time_dial.cpp \
    api.cpp \
    src/wifi.cpp

RESOURCES += qml.qrc\
            static.qrc
#LIBS += -L /opt/qt5pi/sysroot_2/usr/local/tslib/lib -lts
# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =
LIBS +=  -lwiringPi
#LIBS += -lbcm2835
# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =
#LIBS += -L /opt/pilibs
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    display_content_background.h \
    date_time_dial.h \
    api.h \
    src/wifi.h
