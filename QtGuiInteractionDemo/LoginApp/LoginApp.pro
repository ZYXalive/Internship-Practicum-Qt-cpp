QT       += core gui widgets

TEMPLATE = app
CONFIG  += c++17 release

SOURCES += \
    main.cpp \
    LoginDialog.cpp \
    MainWindow.cpp

HEADERS += \
    LoginDialog.h \
    MainWindow.h

# 使用 Qt 资源系统加载图标（避免 windres 中文路径问题）
RESOURCES += resources.qrc

# 输出目录设置
DESTDIR = bin
