#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
//use ui
//#include "ui_form.h"

class MainWindow : public QWidget
                  // ,public Ui::Form
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    // 第(1)部分：标签和按钮交互
    QLabel *m_label;
    QPushButton *m_btnHide;
    QPushButton *m_btnShow;

    // 第(1)部分：文本框同步
    QLineEdit *m_inputBox;
    QLineEdit *m_outputBox;
};

#endif // MAINWINDOW_H
