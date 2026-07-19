QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    adddialog.cpp

HEADERS += \
    mainwindow.h \
    adddialog.h

TARGET = DatabaseApp
