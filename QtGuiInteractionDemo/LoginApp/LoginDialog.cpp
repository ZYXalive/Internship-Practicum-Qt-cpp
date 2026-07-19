#include "LoginDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QCryptographicHash>

// 使用 SHA-256 哈希进行密码验证，避免明文存储和比较
// 密码 "123456" 的 SHA-256 哈希值（十六进制）
static const QString PASSWORD_HASH =
    QString("8d969eef6ecad3c29a3a629280e686cf0c3f5d5a86aff3ca12020c923adc6c92");

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("登录");
    setFixedSize(320, 220);

    // 标题标签
    QLabel *titleLabel = new QLabel("欢迎登录系统");
    QFont titleFont;
    titleFont.setPointSize(14);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);

    // 用户名
    QLabel *userLabel = new QLabel("用户名：");
    m_usernameEdit = new QLineEdit;
    m_usernameEdit->setPlaceholderText("请输入用户名");

    // 密码——使用 Password 模式保证输入保密
    QLabel *passLabel = new QLabel("密  码：");
    m_passwordEdit = new QLineEdit;
    m_passwordEdit->setPlaceholderText("请输入密码");
    m_passwordEdit->setEchoMode(QLineEdit::Password);

    // 登录 / 取消按钮
    m_btnLogin = new QPushButton("登录");
    m_btnCancel = new QPushButton("取消");

    // 连接信号与槽
    connect(m_btnLogin, &QPushButton::clicked, this, &LoginDialog::onLoginClicked);
    connect(m_btnCancel, &QPushButton::clicked, this, &QDialog::reject);
    // 按回车键触发登录
    connect(m_passwordEdit, &QLineEdit::returnPressed, this, &LoginDialog::onLoginClicked);

    // 布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QHBoxLayout *userLayout = new QHBoxLayout;
    userLayout->addWidget(userLabel);
    userLayout->addWidget(m_usernameEdit);

    QHBoxLayout *passLayout = new QHBoxLayout;
    passLayout->addWidget(passLabel);
    passLayout->addWidget(m_passwordEdit);

    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addStretch();
    btnLayout->addWidget(m_btnLogin);
    btnLayout->addWidget(m_btnCancel);
    btnLayout->addStretch();

    mainLayout->addWidget(titleLabel);
    mainLayout->addSpacing(10);
    mainLayout->addLayout(userLayout);
    mainLayout->addLayout(passLayout);
    mainLayout->addSpacing(10);
    mainLayout->addLayout(btnLayout);

    // 默认焦点在用户名输入框
    m_usernameEdit->setFocus();
}

void LoginDialog::onLoginClicked()
{
    QString username = m_usernameEdit->text().trimmed();
    QString password = m_passwordEdit->text();

    // 空值检查
    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "提示", "用户名和密码不能为空！");
        return;
    }

    // 使用 SHA-256 哈希比对密码（密码保密处理）
    QByteArray passwordHash = QCryptographicHash::hash(
        password.toUtf8(), QCryptographicHash::Sha256).toHex();

    if (username == "admin" && QString(passwordHash) == PASSWORD_HASH) {
        accept();   // 登录成功，关闭对话框返回 Accepted
    } else {
        QMessageBox::critical(this, "错误", "用户名或密码错误！");
        m_passwordEdit->clear();
        m_passwordEdit->setFocus();
    }
}
