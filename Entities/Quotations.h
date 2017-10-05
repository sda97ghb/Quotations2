#ifndef QUOTATIONS_H
#define QUOTATIONS_H

#include "Quotation.h"

#include <QDateTime>
#include <QList>
#include <QString>

/// Collection of quotations with interface similar to QList and
/// special domain-based methods.
class Quotations
{
public:
    /// @brief Parse quotations from raw data.
    /// @details One line for one quotaion, field separator is comma,
    /// line contains following fields in following order:
    ///     date(yyyyMMdd),time(hhmm or hhmmss),open,high,low,close
    static Quotations from(QString data);

    /// Crease new collection with given ticker.
    Quotations(QString ticker = QString());
    Quotations(const Quotations& other);

    // List interface methods

    Quotation first();
    Quotation last();

    bool isEmpty() const;

    int size() const;

    void append(Quotation quotation);

    /// Transform this collection to QList. Creates deep copy.
    QList<Quotation> toList() const;

    // Domain-based methods

    /// Collection of deals in given interval.
    Quotations inInterval(QDateTime from, QDateTime to);

    /// Collection of deals in interval of given length from earliest deal.
    /// @arg length Length of the interval in minutes.
    Quotations inInterval(int length = 10);

    /// Filter deals made later than given datetime.
    Quotations laterThan(QDateTime from);

    /// Maximum value, no matter open, close, or high.
    double max() const;

    /// Minimum value, no matter open, close, or low.
    double min() const;

    // Getters and setters

    QString ticker() const;
    void setTicker(const QString& ticker);

private:
    QString m_ticker;
    QList<Quotation> m_list;
};

#endif // QUOTATIONS_H
