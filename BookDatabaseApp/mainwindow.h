#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QPushButton>
#include <QComboBox>
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QDataWidgetMapper>
#include <QItemSelectionModel>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAdd();
    void onDelete();
    void onSort(int index);
    void onTableSelectionChanged();
    void onPrevRecord();
    void onNextRecord();
    void onSubmitMapping();

private:
    void initDatabase();
    void setupModel();
    void setupMapper();

    QTableView *tableView;
    QSqlTableModel *model;
    QPushButton *btnAdd;
    QPushButton *btnDelete;
    QComboBox *comboSort;
    QSqlDatabase db;

    // QDataWidgetMapper 映射数据集相关
    QDataWidgetMapper *mapper;
    QLineEdit *editMapTitle;
    QLineEdit *editMapAuthor;
    QDoubleSpinBox *spinMapPrice;
    QLineEdit *editMapPublisher;
    QPushButton *btnPrev;
    QPushButton *btnNext;
    QPushButton *btnSubmitMap;
    QLabel *labelNav;
};

#endif // MAINWINDOW_H
