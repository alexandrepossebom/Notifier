# #####################################################################
# Automatically generated by qmake (2.01a) ter ago 25 09:37:03 2009
# #####################################################################
TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .

# Input
HEADERS += window.h \
    ../mailcheck.h \
    mailchecker.h \
    updatemailcount.h
SOURCES += main.cpp \
    window.cpp \
    mailchecker.cpp \
    updatemailcount.cpp
RESOURCES += systray.qrc
QT += dbus xml
PKGCONFIG += dbus-1
CONFIG += qdbus
