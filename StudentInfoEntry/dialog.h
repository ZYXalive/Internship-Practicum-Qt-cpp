#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QGroupBox>
#include <QRadioButton>
#include <QSpinBox>
#include <QComboBox>
#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QFormLayout>

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

signals:
    void listFull();        // 自定义信号：列表已满(>=10条)

private slots:
    void onAddClicked();            // 添加按钮点击
    void onAboutClicked();          // 关于按钮点击
    void onListDoubleClicked(QListWidgetItem *item);  // 双击列表项
    void onListFull();              // 处理列表满的槽函数

private:
    void setupUI();

    QLineEdit *m_nameEdit;          // 姓名编辑框
    QGroupBox *m_genderGroup;       // 性别组合框
    QRadioButton *m_radioMale;      // 男
    QRadioButton *m_radioFemale;    // 女
    QSpinBox *m_ageSpinBox;         // 年龄选择
    QComboBox *m_collegeCombo;      // 学院选择

    QListWidget *m_listWidget;      // 信息显示列表

    QPushButton *m_addButton;       // 添加按钮
    QPushButton *m_aboutButton;     // 关于按钮
};

#endif // DIALOG_H
