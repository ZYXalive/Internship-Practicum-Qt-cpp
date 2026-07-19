QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TARGET = BaseConverter
TEMPLATE = app

SOURCES += \
    main.cpp \
    dialog.cpp

HEADERS += \
    dialog.h
