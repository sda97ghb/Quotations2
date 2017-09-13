#include "Quotation.h"

Quotation::Quotation() :
    open(0.0),
    close(0.0),
    low(0.0),
    high(0.0)
{
    // Designed as empty
}

Quotation::operator QString() const
{
    return QString("%1 %2 %3 %4 %5")
            .arg(datetime.toString("yyyy.MM.dd hh:mm"))
            .arg(open).arg(close).arg(low).arg(high);
}
