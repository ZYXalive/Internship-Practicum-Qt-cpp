#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // ============ 1. QWidget ============
    // QWidget 是最基础的窗口类，没有菜单栏、工具栏、状态栏等
    QWidget widget;
    widget.setWindowTitle("QWidget 窗口 - 基础窗口类");
    widget.resize(400, 300);

    QLabel *label1 = new QLabel("QWidget：最基础的窗口，无菜单栏/工具栏/状态栏\n可以嵌入其他窗口，也可以作为独立窗口", &widget);
    label1->setGeometry(20, 20, 360, 100);
    label1->setWordWrap(true);

    widget.show();

    // ============ 2. QMainWindow ============
    // QMainWindow 有菜单栏、工具栏、状态栏、中央部件区域
    QMainWindow mainWindow;
    // QMainWindow 窗口标题
    mainWindow.setWindowTitle("欢迎使用QMainWindow窗口");
    // 设置窗口大小：宽600，高450
    mainWindow.resize(600, 450);

    QLabel *label2 = new QLabel("QMainWindow：有菜单栏、工具栏、状态栏的顶层窗口\n"
                                "标题已设置为：\"欢迎使用QMainWindow窗口\"\n"
                                "大小已设置为：600 x 450");
    mainWindow.setCentralWidget(label2);
    label2->setAlignment(Qt::AlignCenter);

    mainWindow.show();

    // ============ 3. QDialog ============
    // QDialog 是对话框基类，通常用于模态交互
    QDialog dialog;
    dialog.setWindowTitle("QDialog 对话框窗口");
    dialog.resize(400, 300);

    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    QLabel *label3 = new QLabel("QDialog：对话框窗口\n"
                                "通常用做模态对话框（弹窗）\n"
                                "有 exec() 方法用于模态运行\n"
                                "没有菜单栏/工具栏/状态栏");
    label3->setWordWrap(true);
    layout->addWidget(label3);

    dialog.show();

    // 输出三种窗口类型的特点到控制台
    qDebug() << "===== 三种窗口类型对比 =====";
    qDebug() << "QWidget:     基础窗口类，可独立显示或内嵌，无菜单栏/工具栏/状态栏";
    qDebug() << "QMainWindow: 顶层主窗口，含菜单栏、工具栏、状态栏、dock部件区域";
    qDebug() << "QDialog:     对话框类，用于模态/非模态交互，有 exec() 方法";

    return app.exec();
}
