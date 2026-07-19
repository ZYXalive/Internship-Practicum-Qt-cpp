#include "Sender.h"
#include <QDebug>

Sender::Sender(QObject *parent) : QObject(parent) {}

void Sender::emitSignals()
{
    qDebug() << "\n====== 发送者(Sender)发射信号 ======";

    // 发射无参数信号
    qDebug() << "[发射] signalNoArg()";
    emit signalNoArg();

    // 发射带整数参数信号
    int value = 42;
    qDebug() << "[发射] signalWithValue(" << value << ")";
    emit signalWithValue(value);

    // 发射带字符串参数信号
    QString msg = "Hello, 信号与槽!";
    qDebug() << "[发射] signalWithMessage(" << msg << ")";
    emit signalWithMessage(msg);

    qDebug() << "====================================\n";
}
