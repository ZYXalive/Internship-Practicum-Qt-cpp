#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>
#include <QRadioButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void onDigitClicked();          // 数字按钮点击
    void onCalculateClicked();      // 计算按钮点击
    void onClearClicked();          // 清空按钮点击
    void onExitClicked();           // 退出按钮点击

private:
    void setupUI();                 // 设置界面
    QString convertNumber(const QString &input, int base);  // 进制转换函数

    QLineEdit *m_inputEdit;         // 输入文本框
    QLineEdit *m_resultEdit;        // 结果显示文本框
    QGroupBox *m_baseGroup;         // 进制选择组
    QRadioButton *m_radioBinary;    // 二进制
    QRadioButton *m_radioOctal;     // 八进制
    QRadioButton *m_radioHex;       // 十六进制
    QPushButton *m_digitButtons[10]; // 0-9数字按钮
    QPushButton *m_calcButton;      // 计算按钮
    QPushButton *m_clearButton;     // 清空按钮
    QPushButton *m_exitButton;      // 退出按钮
};

#endif // DIALOG_H
