#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>
#include <QVector>
#include "salesrecord.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAddRecord();

private:
    QComboBox *comboSalesperson;
    QDoubleSpinBox *spinAmount;
    QPushButton *btnAdd;
    QTextEdit *textRecords;
    QLabel *labelTotal;

    QVector<SalesRecord> records;
};

#endif // MAINWINDOW_H
