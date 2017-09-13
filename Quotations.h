#ifndef QUOTATIONS_H
#define QUOTATIONS_H

#include "Quotation.h"

class Quotations
{
public:
    static Quotations from(QString data);

    void append(Quotation quotation);

    Quotations inInterval(QDateTime from, QDateTime to);

    /// @arg length Length of the interval in minutes.
    Quotations inInterval(int length = 10);

    Quotations laterThan(QDateTime from);

    Quotation first();
    Quotation last();

    bool isEmpty() const;

    int size() const;

    double max() const;
    double min() const;

    QList<Quotation> toList() const;

private:
    QList<Quotation> m_list;
};

#endif // QUOTATIONS_H
