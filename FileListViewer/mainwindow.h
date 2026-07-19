#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListView>
#include <QStringList>
#include <QStringListModel>
#include <QPushButton>
#include <QFont>
#include <QColor>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onOpenFile();
    void onSetFont();
    void onSetTextColor();
    void onSetBackgroundColor();
    void onExit();

private:
    void updateStyleSheet();

    QListView *listView;
    QStringListModel *model;
    QStringList fileList;

    QPushButton *btnOpenFile;
    QPushButton *btnSetFont;
    QPushButton *btnSetTextColor;
    QPushButton *btnSetBackgroundColor;
    QPushButton *btnExit;

    QFont currentFont;
    QColor textColor;
    QColor backgroundColor;
};

#endif // MAINWINDOW_H
