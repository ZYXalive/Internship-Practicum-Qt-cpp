QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TARGET = MDI_Notepad
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    mdichild.cpp

HEADERS += \
    mainwindow.h \
    mdichild.h
