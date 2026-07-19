QT       += core gui widgets

TEMPLATE = app
CONFIG  += c++17 release

SOURCES += \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    MainWindow.h

RESOURCES += resources.qrc

DESTDIR = bin

FORMS += \
    form.ui
