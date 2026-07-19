#include "Receiver.h"
#include <QDebug>

Receiver::Receiver(QObject *parent) : QObject(parent) {}

void Receiver::onNoArg()
{
    m_receiveCount++;
    qDebug() << "  [接收] Receiver::onNoArg() —— 收到无参数信号，已接收" << m_receiveCount << "次";
}

void Receiver::onWithValue(int value)
{
    m_receiveCount++;
    qDebug() << "  [接收] Receiver::onWithValue(" << value << ") —— 收到带参数信号，已接收" << m_receiveCount << "次";
}

void Receiver::onWithMessage(const QString &message)
{
    m_receiveCount++;
    qDebug() << "  [接收] Receiver::onWithMessage(" << message << ") —— 收到字符串信号，已接收" << m_receiveCount << "次";
}

void Receiver::onOverload()
{
    m_receiveCount++;
    qDebug() << "  [接收] Receiver::onOverload() —— 无参版本，已接收" << m_receiveCount << "次";
}

void Receiver::onOverload(int value)
{
    m_receiveCount++;
    qDebug() << "  [接收] Receiver::onOverload(" << value << ") —— 有参版本，已接收" << m_receiveCount << "次";
}

int Receiver::getReceiveCount() const
{
    return m_receiveCount;
}
