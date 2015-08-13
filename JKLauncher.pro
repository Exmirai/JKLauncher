#-------------------------------------------------
#
# Project created by QtCreator 2015-08-12T23:57:36
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = JKLauncher
TEMPLATE = app


SOURCES += source/main.cpp\
            json/cJSON.c \
            source/mainwindow.cpp \
    source/settings.cpp \
    source/profiles.cpp \
    source/network.cpp \
    source/starter.cpp \
    source/smartconnect.cpp \
    source/AESWrapper.cpp \
    source/RSAWrapper.cpp

HEADERS  += json/cJSON.h \
            source/mainwindow.h \
    source/launcher.h \
    source/profiles.h \
    source/network.h \
    source/settings.h \
    source/starter.h \
    source/smartconnect.h \
    source/AESWrapper.h \
    source/RSAWrapper.h

FORMS    += forms/mainwindow.ui \
            forms/settings.ui

RESOURCES += resources/resources.qrc
