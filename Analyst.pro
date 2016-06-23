#-------------------------------------------------
#
# Project created by QtCreator 2016-06-20T16:25:22
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Analyst
TEMPLATE = app


SOURCES += main.cpp\
        analyst.cpp \
    tools.cpp \
    point.cpp \
    markedpoint.cpp \
    couchdb.cpp \
    ore.cpp \
    minor.cpp

HEADERS  += analyst.h \
    tools.h \
    point.h \
    markedpoint.h \
    couchdb.h \
    ore.h \
    minor.h

FORMS    += analyst.ui

DISTFILES += \
    conf.ini
