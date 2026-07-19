#ifndef SALESRECORD_H
#define SALESRECORD_H

#include <QString>

class SalesRecord
{
public:
    SalesRecord();
    SalesRecord(const QString &salespersonId, double amount);

    QString salespersonId() const;
    double amount() const;

    QString toString() const;

    static double totalTurnover();
    static void resetTotalTurnover();

private:
    QString m_salespersonId;
    double m_amount;

    static double s_totalTurnover;
};

#endif // SALESRECORD_H
