#-------------------------------------------------
#
# Project created by QtCreator 2015-06-26T17:52:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Solaris
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        PolinomM2.cpp \
    func.cpp \
    specedit.cpp \
    spinsegment.cpp \
    knopkasmena.cpp \
    nastrraynd.cpp \
    spinsegmentk.cpp \
    redactirpolinom.cpp \
    combosegment.cpp \
    combosegmentk.cpp \
    spinsegmentn.cpp \
    spinsegmentrk.cpp \
    convertthread.cpp \
    funcdyblicat.cpp \
    test.cpp \
    keys.cpp \
    knopkagenaz.cpp \
    knopkagenak.cpp

HEADERS  += mainwindow.h \
    PolinomM2.h \
    combosegment.h \
    specedit.h \
    spinsegment.h \
    knopkasmena.h \
    combosegmentk.h \
    spinsegmentk.h \
    spinsegmentn.h \
    spinsegmentrk.h \
    convertthread.h \
    knopkagenaz.h \
    knopkagenak.h

FORMS    += mainwindow.ui

RC_FILE += icon.rc

RESOURCES += \
    pic.qrc
