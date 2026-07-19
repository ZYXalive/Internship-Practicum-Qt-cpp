#ifndef RECEIVER_H
#define RECEIVER_H

#include <QObject>

class Receiver : public QObject
{
    Q_OBJECT

public:
    explicit Receiver(QObject *parent = nullptr);

public slots:
    // 对应无参数信号的槽函数
    void onNoArg();

    // 对应带整数参数信号的槽函数
    void onWithValue(int value);

    // 对应带字符串参数信号的槽函数
    void onWithMessage(const QString &message);

    // 重载版本
    void onOverload();
    void onOverload(int value);

    // 统计接收次数
    int getReceiveCount() const;

private:
    int m_receiveCount = 0;
};

#endif // RECEIVER_H
