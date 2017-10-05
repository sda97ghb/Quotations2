#ifndef QUOTATION_H
#define QUOTATION_H

#include <QDateTime>
#include <QString>

/// Represents one single quotation.
///
/// Can be printed with qDebug().
class Quotation
{
public:
    Quotation();

    operator QString() const;

    /// @return true if quotation can be interpreted as a valid quotation
    /// (valid datetime, high not less than low, open and close is in interval
    /// from low to high).
    /// false otherwise.
    bool isValid() const;

    QDateTime datetime() const;
    double open() const;
    double close() const;
    double low() const;
    double high() const;

    void setDatetime(const QDateTime& datetime);
    void setOpen(double open);
    void setClose(double close);
    void setLow(double low);
    void setHigh(double high);

private:
    QDateTime m_datetime;

    double m_open;
    double m_close;

    double m_low;
    double m_high;
};

#endif // QUOTATION_H
