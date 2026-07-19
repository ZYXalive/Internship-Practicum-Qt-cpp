#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QTableView>
#include <QSqlDatabase>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showAddDialog();
    void deleteRow();
    void refreshData();
    void importFromFile();
    void exportToFile();
    void updateStatusBar();

private:
    void initDatabase();
    void loadData();
    void createActions();
    void createToolBar();
    void createMenus();
    void createStatusBar();

    // 数据库
    QSqlDatabase db;

    // 数据模型
    QStandardItemModel *model;

    // 视图
    QTableView *tableView;

    // 动作
    QAction *addAct;
    QAction *deleteAct;
    QAction *refreshAct;
    QAction *importAct;
    QAction *exportAct;
};

#endif
