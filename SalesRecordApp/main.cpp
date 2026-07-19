#include "mainwindow.h"
#include "salesrecord.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 题目要求：在主函数中定义两条销售记录，并显示总营业额
    SalesRecord record1("售货员001", 1500.50);
    SalesRecord record2("售货员002", 2300.75);

    qDebug() << record1.toString();
    qDebug() << record2.toString();
    qDebug() << "总营业额:" << SalesRecord::totalTurnover() << "元";

    // 重置营业总额，进入GUI模式
    SalesRecord::resetTotalTurnover();

    MainWindow w;
    w.show();
    return a.exec();
}
