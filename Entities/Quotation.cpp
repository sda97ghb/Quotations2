#include "Quotation.h"

Quotation::Quotation() :
    m_datetime(),
    m_open(0.0),
    m_close(0.0),
    m_low(0.0),
    m_high(0.0)
{
    // Designed as empty
}

bool Quotation::isValid() const
{
    return m_datetime.isValid() &&
           (m_high >= m_low) &&
           (m_low <= m_open && m_open <= m_high) &&
           (m_low <= m_close && m_close <= m_high);
}

QDateTime Quotation::datetime() const
{
    return m_datetime;
}

double Quotation::open() const
{
    return m_open;
}

double Quotation::close() const
{
    return m_close;
}

double Quotation::low() const
{
    return m_low;
}

double Quotation::high() const
{
    return m_high;
}

void Quotation::setDatetime(const QDateTime& datetime)
{
    m_datetime = datetime;
}

void Quotation::setOpen(double open)
{
    m_open = open;
}

void Quotation::setClose(double close)
{
    m_close = close;
}

void Quotation::setLow(double low)
{
    m_low = low;
}

void Quotation::setHigh(double high)
{
    m_high = high;
}

Quotation::operator QString() const
{
    return QString("%1 %2 %3 %4 %5")
            .arg(datetime().toString("yyyy.MM.dd hh:mm"))
            .arg(open())
            .arg(high())
            .arg(low())
            .arg(close());
}
