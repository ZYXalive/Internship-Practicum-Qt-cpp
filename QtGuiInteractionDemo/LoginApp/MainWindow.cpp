#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // 设置窗口标题
    setWindowTitle("我的第一个QT程序");
    // 设置窗口大小
    resize(400, 300);

    // 中央标签——显示欢迎信息和帮助说明
    QLabel *centralLabel = new QLabel(
        "欢迎进入主界面！\n\n"
        "登录成功！\n"
        "学号：2025112454\n"
        "姓名：朱雅新\n\n"
        "提示：密码已使用 SHA-256 哈希加密存储。\n"
        "输入时密码以密文显示，保证了保密性。",
        this
    );
    centralLabel->setAlignment(Qt::AlignCenter);
    centralLabel->setWordWrap(true);
    setCentralWidget(centralLabel);
}
