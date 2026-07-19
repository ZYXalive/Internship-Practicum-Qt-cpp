#include "salesrecord.h"

double SalesRecord::s_totalTurnover = 0.0;

SalesRecord::SalesRecord()
    : m_salespersonId(""), m_amount(0.0)
{
}

SalesRecord::SalesRecord(const QString &salespersonId, double amount)
    : m_salespersonId(salespersonId), m_amount(amount)
{
    s_totalTurnover += amount;
}

QString SalesRecord::salespersonId() const
{
    return m_salespersonId;
}

double SalesRecord::amount() const
{
    return m_amount;
}

QString SalesRecord::toString() const
{
    return QString("售货员: %1, 销售金额: %2 元")
        .arg(m_salespersonId)
        .arg(m_amount, 0, 'f', 2);
}

double SalesRecord::totalTurnover()
{
    return s_totalTurnover;
}

void SalesRecord::resetTotalTurnover()
{
    s_totalTurnover = 0.0;
}
