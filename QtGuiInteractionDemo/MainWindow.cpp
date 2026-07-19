#include "MainWindow.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    // 设置窗口大小为400x400
    setFixedSize(400, 400);
    // 设置窗口标题
    setWindowTitle("我的第一个QT程序");

    // ========================================
    // 第一部分：标签 + 两个按钮（隐藏/显示标签）
    // ========================================

    // 创建标签，内容为"你的专业 你的学号-姓名"，位于(10,10)
    m_label = new QLabel("我的第一个QT程序", this);
    m_label->setGeometry(10, 10, 180, 20);

    // 创建"点击隐藏标签"按钮，位于(10,40)，大小80x20
    m_btnHide = new QPushButton("点击隐藏标签", this);
    m_btnHide->setGeometry(10, 40, 80, 20);

    // 创建"点击显示标签"按钮，位于(10,80)，大小80x20
    m_btnShow = new QPushButton("点击显示标签", this);
    m_btnShow->setGeometry(10, 80, 80, 20);

    // 连接信号与槽：点击隐藏按钮 → 隐藏标签
    connect(m_btnHide, &QPushButton::clicked, m_label, &QLabel::hide);

    // 连接信号与槽：点击显示按钮 → 显示标签
    connect(m_btnShow, &QPushButton::clicked, m_label, &QLabel::show);

    // ========================================
    // 第二部分：两个单行文本框（文字同步）
    // ========================================

    // 上面的单行文本框，位置(10,10)（因同窗口演示，实际位置调为(10,110)）
    m_inputBox = new QLineEdit(this);
    m_inputBox->setGeometry(10, 110, 150, 20);
    m_inputBox->setPlaceholderText("在此输入文字...");

    // 下面的单行文本框，位置(10,50)（实际调为(10,140)）
    m_outputBox = new QLineEdit(this);
    m_outputBox->setGeometry(10, 140, 150, 20);
    m_outputBox->setPlaceholderText("文字同步显示...");
    m_outputBox->setReadOnly(true);

    // 设置字体加粗和红色
    QFont font = m_outputBox->font();
    font.setBold(true);
    m_outputBox->setFont(font);
    m_outputBox->setStyleSheet("color: red;");

    // 连接信号与槽：输入框文字变化 → 输出框同步更新
    connect(m_inputBox, &QLineEdit::textChanged,
            m_outputBox, &QLineEdit::setText);

    //使用ui文件取消注释即可：
    //setupUi(this);
}
