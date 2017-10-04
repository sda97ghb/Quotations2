#ifndef QUOTATION_H
#define QUOTATION_H

#include <QDateTime>
#include <QString>

class Quotation
{
public:
    Quotation();

    operator QString() const;

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
