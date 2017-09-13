#include "Quotations.h"

Quotations Quotations::from(QString data)
{
    Quotations quotations;

    for (QString line : data.split("\n"))
    {
        line.replace("\r", "");
        QStringList tokens = line.split(",");
        if (tokens.size() != 8) // line format is not supported
            continue;

        Quotation quotation;
        quotation.datetime = QDateTime(
                    QDate(QStringRef(&(tokens.at(2)), 0, 4).toInt(),
                          QStringRef(&(tokens.at(2)), 4, 2).toInt(),
                          QStringRef(&(tokens.at(2)), 6, 2).toInt()),
                    QTime(QStringRef(&(tokens.at(3)), 0, 2).toInt(),
                          QStringRef(&(tokens.at(3)), 2, 2).toInt()));
        quotation.open  = tokens.at(4).toDouble();
        quotation.close = tokens.at(7).toDouble();
        quotation.low   = tokens.at(6).toDouble();
        quotation.high  = tokens.at(5).toDouble();

        quotations.append(quotation);
    }

    return quotations;
}

void Quotations::append(Quotation quotation)
{
    m_list.append(quotation);
}

Quotations Quotations::inInterval(QDateTime from, QDateTime to)
{
    Quotations quotations;
    for (Quotation quotation : m_list)
        if (quotation.datetime >= from && quotation.datetime <= to)
            quotations.append(quotation);
    return quotations;
}

/// @arg length Length of the interval in minutes.
Quotations Quotations::inInterval(int length)
{
    if (isEmpty())
        return Quotations();

    QDateTime from = m_list.first().datetime;
    QDateTime to = from.addSecs(length * 60);
    return inInterval(from, to);
}

Quotations Quotations::laterThan(QDateTime from)
{
    if (isEmpty())
        return Quotations();

    return inInterval(from, m_list.last().datetime);
}

Quotation Quotations::first()
{
    return m_list.first();
}

Quotation Quotations::last()
{
    return m_list.last();
}

bool Quotations::isEmpty() const
{
    return m_list.isEmpty();
}

int Quotations::size() const
{
    return m_list.size();
}

double Quotations::max() const
{
    double value = -1e10;

    for (Quotation quotation : m_list)
        if (value < quotation.high)
            value = quotation.high;

    return value;
}

double Quotations::min() const
{
    double value = 1e10;

    for (Quotation quotation : m_list)
        if (value > quotation.low)
            value = quotation.low;

    return value;
}

QList<Quotation> Quotations::toList() const
{
    return m_list;
}

QString Quotations::ticker() const
{
    return m_ticker;
}

void Quotations::setTicker(const QString& ticker)
{
    m_ticker = ticker;
}
