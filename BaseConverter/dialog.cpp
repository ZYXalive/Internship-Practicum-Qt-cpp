#include "dialog.h"
#include <QApplication>
#include <QMessageBox>
#include <QFont>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    setupUI();
    // 设置窗口标题：学号-姓名-进制转换器
    setWindowTitle("2025112454-朱雅新-进制转换器");
}

Dialog::~Dialog()
{
}

void Dialog::setupUI()
{
    // 主布局采用垂直布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // 标题标签
    QLabel *titleLabel = new QLabel("进制转换器", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont;
    titleFont.setPointSize(16);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    mainLayout->addWidget(titleLabel);

    // 输入文本框 - 初始值为0，右对齐
    m_inputEdit = new QLineEdit(this);
    m_inputEdit->setText("0");
    m_inputEdit->setAlignment(Qt::AlignRight);
    m_inputEdit->setReadOnly(false);
    m_inputEdit->setMinimumHeight(35);
    QFont editFont;
    editFont.setPointSize(14);
    m_inputEdit->setFont(editFont);
    mainLayout->addWidget(m_inputEdit);

    // 结果显示文本框 - 不可编辑
    QLabel *resultLabel = new QLabel("转换结果：", this);
    mainLayout->addWidget(resultLabel);

    m_resultEdit = new QLineEdit(this);
    m_resultEdit->setText("0");
    m_resultEdit->setAlignment(Qt::AlignRight);
    m_resultEdit->setReadOnly(true);
    m_resultEdit->setMinimumHeight(35);
    m_resultEdit->setFont(editFont);
    m_resultEdit->setStyleSheet("background-color:;");
    mainLayout->addWidget(m_resultEdit);

    // 数字按钮网格 (0-9)
    QGridLayout *digitLayout = new QGridLayout();
    for (int i = 0; i < 10; i++) {
        m_digitButtons[i] = new QPushButton(QString::number(i), this);
        m_digitButtons[i]->setMinimumSize(60, 45);
        QFont btnFont;
        btnFont.setPointSize(12);
        m_digitButtons[i]->setFont(btnFont);
        // 连接信号和槽 - 通过信号槽编辑器实现
        connect(m_digitButtons[i], SIGNAL(clicked()), this, SLOT(onDigitClicked()));
    }

    // 布局数字按钮：1-9 排成3x3，0单独
    // 第一行: 1 2 3
    digitLayout->addWidget(m_digitButtons[1], 0, 0);
    digitLayout->addWidget(m_digitButtons[2], 0, 1);
    digitLayout->addWidget(m_digitButtons[3], 0, 2);
    // 第二行: 4 5 6
    digitLayout->addWidget(m_digitButtons[4], 1, 0);
    digitLayout->addWidget(m_digitButtons[5], 1, 1);
    digitLayout->addWidget(m_digitButtons[6], 1, 2);
    // 第三行: 7 8 9
    digitLayout->addWidget(m_digitButtons[7], 2, 0);
    digitLayout->addWidget(m_digitButtons[8], 2, 1);
    digitLayout->addWidget(m_digitButtons[9], 2, 2);
    // 第四行: 0 (占两列宽)
    digitLayout->addWidget(m_digitButtons[0], 3, 0, 1, 3);

    mainLayout->addLayout(digitLayout);

    // 进制选择组 (QGroupBox + QRadioButton)
    m_baseGroup = new QGroupBox("请选择转换进制", this);
    QVBoxLayout *radioLayout = new QVBoxLayout(m_baseGroup);

    m_radioBinary = new QRadioButton("十进制 → 二进制", this);
    m_radioOctal = new QRadioButton("十进制 → 八进制", this);
    m_radioHex = new QRadioButton("十进制 → 十六进制", this);

    // 默认选中二进制
    m_radioBinary->setChecked(true);

    radioLayout->addWidget(m_radioBinary);
    radioLayout->addWidget(m_radioOctal);
    radioLayout->addWidget(m_radioHex);

    mainLayout->addWidget(m_baseGroup);

    // 操作按钮布局
    QHBoxLayout *buttonLayout = new QHBoxLayout();

    m_calcButton = new QPushButton("计算", this);
    m_calcButton->setMinimumHeight(35);
    m_calcButton->setStyleSheet("background-color: #4CAF50; color: white; font-size: 14px;");

    m_clearButton = new QPushButton("清空", this);
    m_clearButton->setMinimumHeight(35);
    m_clearButton->setStyleSheet("background-color: #f44336; color: white; font-size: 14px;");

    m_exitButton = new QPushButton("退出", this);
    m_exitButton->setMinimumHeight(35);
    m_exitButton->setStyleSheet("background-color: #607D8B; color: white; font-size: 14px;");

    buttonLayout->addWidget(m_calcButton);
    buttonLayout->addWidget(m_clearButton);
    buttonLayout->addWidget(m_exitButton);

    mainLayout->addLayout(buttonLayout);

    // 使用信号槽编辑器建立关联（代码方式实现信号槽连接）
    connect(m_calcButton, SIGNAL(clicked()), this, SLOT(onCalculateClicked()));
    connect(m_clearButton, SIGNAL(clicked()), this, SLOT(onClearClicked()));
    connect(m_exitButton, SIGNAL(clicked()), this, SLOT(onExitClicked()));

    // 设置整体布局
    setLayout(mainLayout);
    setFixedSize(350, 500);
}

void Dialog::onDigitClicked()
{
    // 获取发送信号的按钮
    QPushButton *btn = qobject_cast<QPushButton *>(sender());
    if (!btn) return;

    QString digit = btn->text();
    QString currentText = m_inputEdit->text();

    // 如果当前为0，替换为输入的数字
    if (currentText == "0") {
        m_inputEdit->setText(digit);
    } else {
        m_inputEdit->setText(currentText + digit);
    }
}

void Dialog::onCalculateClicked()
{
    QString input = m_inputEdit->text();
    bool ok;
    input.toInt(&ok);  // 验证输入是否为有效整数

    if (!ok) {
        QMessageBox::warning(this, "错误", "请输入有效的十进制整数！");
        return;
    }

    QString result;
    if (m_radioBinary->isChecked()) {
        result = convertNumber(input, 2);
    } else if (m_radioOctal->isChecked()) {
        result = convertNumber(input, 8);
    } else if (m_radioHex->isChecked()) {
        result = convertNumber(input, 16);
    }

    m_resultEdit->setText(result);
}

void Dialog::onClearClicked()
{
    m_inputEdit->setText("0");
    m_resultEdit->setText("0");
    m_radioBinary->setChecked(true);
}

void Dialog::onExitClicked()
{
    QApplication::quit();
}

QString Dialog::convertNumber(const QString &input, int base)
{
    bool ok;
    int decimalValue = input.toInt(&ok);
    if (!ok) {
        return "输入错误";
    }

    return QString::number(decimalValue, base).toUpper();
}
