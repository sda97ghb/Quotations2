#ifndef DEALS_H
#define DEALS_H

#include "Deal.h"

#include <QDateTime>
#include <QList>
#include <QString>

class Deals
{
public:
    static Deals from(QString data);

    Deals(QString ticker = QString());
    Deals(const Deals& other);

    // List interface methods

    Deal first() const;
    Deal last() const;

    bool isEmpty() const;

    int size() const;

    void append(Deal deal);

    QList<Deal> toList() const;

    // Domain-based methods

    Deals inInterval(QDateTime from, QDateTime to);

    /// @arg length Length of the interval in minutes.
    Deals inInterval(int length = 10);

    Deals laterThan(QDateTime from);

    template <typename T>
    T reduce(T initialValue, std::function<T(T, Deal)> operation) const
    {
        T accumulator = initialValue;
        for (Deal deal : m_list)
            accumulator = operation(accumulator, deal);
        return accumulator;
    }

    quint64 maxVolume() const;
    quint64 minVolume() const;

    quint64 averageVolume() const;

    quint64 totalVolume() const;

    Deal find(std::function<bool(Deal)> condition) const;

    Deals filter(std::function<bool(Deal)> condition) const;
    Deals filterBuy() const;
    Deals filterSell() const;

    Deals sort(std::function<bool(Deal, Deal)> comparator) const;
    Deals sortByVolume() const;

    template <typename T>
    QList<T> map(std::function<T(Deal)> mapper) const
    {
        QList<T> list;
        for (Deal deal : m_list)
            list.append(mapper(deal));
        return list;
    }
    QList<quint64> toListOfVolumes() const;

    template <typename T>
    QHash<T, Deals> split(std::function<T(Deal)> property) const
    {
        QHash<T, Deals> splitted;
        for (Deal deal : m_list)
        {
            T propertyValue = property(deal);
            unless (splitted.contains(propertyValue))
                splitted[propertyValue] = Deals();
            splitted[propertyValue].append(deal);
        }
        return splitted;
    }

    QHash<int, Deals> splitByDayOfWeek() const;
    QHash<QDate, Deals> splitByDate() const;

    // Getters and setters

    QString ticker() const;
    void setTicker(QString ticker);

private:
    QString m_ticker;
    QList<Deal> m_list;
};

#endif // DEALS_H
