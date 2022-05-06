TEMPLATE = app

QT += qml quick widgets

QT_CONFIG -= no-pkg-config
CONFIG += link_pkgconfig debug
PKGCONFIG = \
    gstreamer-1.0 \
    gstreamer-video-1.0

DEFINES += GST_USE_UNSTABLE_API

INCLUDEPATH +=  include

SOURCES += src/main.cpp \
           src/MyTimer.cpp \
           src/SetPlaying.cpp

RESOURCES += qmlsink.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =


target.path = /opt/data/$${TARGET}/bin
INSTALLS += target

HEADERS += \
    include/MyTimer.h \
    include/SetPlaying.h
