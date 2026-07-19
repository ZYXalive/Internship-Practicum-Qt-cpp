#include <QApplication>
#include <QIcon>
#include "LoginDialog.h"
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // 设置应用程序图标
    app.setWindowIcon(QIcon(":/app.ico"));

    // 显示登录对话框
    LoginDialog loginDialog;
    if (loginDialog.exec() != QDialog::Accepted) {
        // 用户取消登录，退出程序
        return 0;
    }

    // 登录成功，显示主窗口
    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
