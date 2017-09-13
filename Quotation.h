#ifndef QUOTATION_H
#define QUOTATION_H

#include <QDateTime>
#include <QString>

struct Quotation
{
    Quotation();

    operator QString() const;

    QDateTime datetime;

    double open;
    double close;

    double low;
    double high;
};

#endif // QUOTATION_H
