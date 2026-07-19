QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TARGET = StandardItemModelDemo
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    combodelegate.cpp

HEADERS += \
    mainwindow.h \
    combodelegate.h
