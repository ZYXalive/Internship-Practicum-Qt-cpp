#include <QCoreApplication>
#include <QDebug>
#include "Sender.h"
#include "Receiver.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    qDebug() << "===== Qt 信号与槽通信机制 演示 =====";

    // 1. 创建发送者和接收者对象
    Sender sender;
    Receiver receiver;

    // ============================================
    // 2. 连接信号与槽（关键步骤）
    //    语法: connect(发送者, 信号, 接收者, 槽)
    // ============================================
    qDebug() << "[连接] signalNoArg ---> onNoArg";
    QObject::connect(&sender, &Sender::signalNoArg,
                     &receiver, &Receiver::onNoArg);

    qDebug() << "[连接] signalWithValue ---> onWithValue";
    QObject::connect(&sender, &Sender::signalWithValue,
                     &receiver, &Receiver::onWithValue);

    qDebug() << "[连接] signalWithMessage ---> onWithMessage";
    QObject::connect(&sender, &Sender::signalWithMessage,
                     &receiver, &Receiver::onWithMessage);

    // ============================================
    // 演示2：一个信号连接多个槽（一对多）
    // ============================================
    qDebug() << "[连接] signalNoArg ---> onOverload()  (一个信号连接两个槽)";
    QObject::connect(&sender, &Sender::signalNoArg,
                     &receiver, static_cast<void (Receiver::*)()>(&Receiver::onOverload));

    // ============================================
    // 演示3：多个信号连接同一个槽（多对一）
    // ============================================
    qDebug() << "[连接] signalNoArg 和 signalWithValue ---> onNoArg  (两个信号连接同一个槽)";
    QObject::connect(&sender, &Sender::signalWithValue,
                     &receiver, [&]() { receiver.onNoArg(); });

    qDebug() << "";
    qDebug() << "============================================";
    qDebug() << "  启动演示：发送者开始发射信号...";
    qDebug() << "============================================";

    // 3. 触发信号
    sender.emitSignals();

    // 4. 输出总结
    qDebug() << "\n===== 信号与槽机制总结 =====";
    qDebug() << "总接收次数:" << receiver.getReceiveCount() << "次";
    qDebug() << "";
    qDebug() << "信号与槽的核心特点:";
    qDebug() << "1. 松耦合：发送者不知道接收者的存在";
    qDebug() << "2. 类型安全：编译期检查参数类型是否匹配";
    qDebug() << "3. 一对多/多对一：一个信号可连多个槽，多个信号可连同一个槽";
    qDebug() << "4. 线程安全：支持跨线程的对象通信";

    return 0;
}
