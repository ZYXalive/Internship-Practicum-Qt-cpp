#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QDockWidget>
#include <QDoubleSpinBox>
#include <QPixmap>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void toggleImage();
    void zoomIn();
    void zoomOut();
    void zoomReset();
    void updateStatusBar();

private:
    void createActions();
    void createMenus();
    void createToolBar();
    void createDockWidget();
    void createStatusBar();
    void updateImage();

    // 中心部件
    QLabel *imageLabel;
    QPixmap originalPixmap;
    bool imageVisible;

    // 缩放相关
    double currentZoom;
    QDoubleSpinBox *zoomSpinBox;

    // 菜单动作
    QAction *toggleAct;
    QAction *zoomInAct;
    QAction *zoomOutAct;
    QAction *zoomResetAct;

    // 停靠窗口
    QDockWidget *dockWidget;
};

#endif
