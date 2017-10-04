#ifndef QUOTATIONS_H
#define QUOTATIONS_H

#include "Quotation.h"

#include <QDateTime>
#include <QList>
#include <QString>

class Quotations
{
public:
    static Quotations from(QString data);

    Quotations(QString ticker = QString());
    Quotations(const Quotations& other);

    // List interface methods

    Quotation first();
    Quotation last();

    bool isEmpty() const;

    int size() const;

    void append(Quotation quotation);

    QList<Quotation> toList() const;

    // Domain-based methods

    Quotations inInterval(QDateTime from, QDateTime to);

    /// @arg length Length of the interval in minutes.
    Quotations inInterval(int length = 10);

    Quotations laterThan(QDateTime from);

    double max() const;
    double min() const;

    // Getters and setters

    QString ticker() const;
    void setTicker(const QString& ticker);

private:
    QString m_ticker;
    QList<Quotation> m_list;
};

#endif // QUOTATIONS_H
