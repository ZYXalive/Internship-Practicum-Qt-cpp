#ifndef SENDER_H
#define SENDER_H

#include <QObject>

class Sender : public QObject
{
    Q_OBJECT

public:
    explicit Sender(QObject *parent = nullptr);

    // 模拟触发各种信号
    void emitSignals();

signals:
    // 1. 无参数信号
    void signalNoArg();

    // 2. 带参数信号
    void signalWithValue(int value);

    // 3. 带字符串参数信号
    void signalWithMessage(const QString &message);

    // 4. 重载信号
    void signalOverload();
    void signalOverload(int value);
};

#endif // SENDER_H
