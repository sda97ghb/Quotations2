#include "Deals.h"

#include <QDebug>

#include <limits>

Deals Deals::from(QString data)
{
    Deals deals;

    for (QString line : data.split("\n"))
    {
        line.replace("\r", "");
        QStringList tokens = line.split(",");
        if (tokens.size() != 6) // line format is not supported
            continue;

        Deal deal;
        deal.setDatetime(QDateTime(QDate(QStringRef(&tokens.at(0), 0, 4).toInt(),
                                         QStringRef(&tokens.at(0), 4, 2).toInt(),
                                         QStringRef(&tokens.at(0), 6, 2).toInt()),
                                   QTime(QStringRef(&tokens.at(1), 0, 2).toInt(),
                                         QStringRef(&tokens.at(1), 2, 2).toInt(),
                                         QStringRef(&tokens.at(1), 4, 2).toInt())));
        deal.setLast(tokens.at(2).toDouble());
        deal.setVolume(tokens.at(3).toULongLong());
        deal.setId(tokens.at(4).toULongLong());

        Deal::Type type = Deal::Type::Unknown;
        if (tokens.at(5) == "S")
            type = Deal::Type::Sell;
        else if (tokens.at(5) == "B")
            type = Deal::Type::Buy;

        deal.setType(type);

        deals.append(deal);
    }

    return deals;
}

Deals::Deals(QString ticker) :
    m_ticker(ticker)
{
    // Designed as empty
}

Deals::Deals(const Deals& other) :
    m_ticker(other.ticker()),
    m_list(other.toList())
{
    // Designed as empty
}

void Deals::append(Deal deal)
{
    m_list.append(deal);
}

Deals Deals::inInterval(QDateTime from, QDateTime to)
{
    Deals deals;
    for (Deal deal : m_list)
        if (deal.datetime() >= from && deal.datetime() <= to)
            deals.append(deal);
    return deals;
}

Deals Deals::inInterval(int length)
{
    if (isEmpty())
        return Deals();

    QDateTime from = first().datetime();
    QDateTime to = from.addSecs(length * 60);

    return inInterval(from, to);
}

Deals Deals::laterThan(QDateTime from)
{
    if (isEmpty())
        return Deals();
    return inInterval(from, last().datetime());
}

quint64 Deals::maxVolume() const
{
    return reduce<quint64>(0ull, [](quint64 accumulator, Deal deal) -> quint64
    {
        return accumulator < deal.volume() ? deal.volume() : accumulator;
    });
}

quint64 Deals::minVolume() const
{
    if (isEmpty())
        return 0ull;

    return reduce<quint64>(std::numeric_limits<quint64>::max(), [](quint64 accumulator, Deal deal) -> quint64
    {
        return accumulator > deal.volume() ? deal.volume() : accumulator;
    });
}

quint64 Deals::averageVolume() const
{
    if (size() == 0)
        return 0;
    return totalVolume() / size();
}

quint64 Deals::totalVolume() const
{
    return reduce<quint64>(0ull, [](quint64 accumulator, Deal deal) -> quint64
    {
        return accumulator + deal.volume();
    });
}

Deal Deals::find(std::function<bool (Deal)> condition) const
{
    for (Deal deal : m_list)
        if (condition(deal))
            return deal;
    return Deal();
}

Deals Deals::filter(std::function<bool (Deal)> condition) const
{
    Deals filtered;
    for (Deal deal : m_list)
        if (condition(deal))
            filtered.append(deal);
    return filtered;
}

Deals Deals::filterBuy() const
{
    return filter([](Deal deal) -> bool
    {
        return deal.type() == Deal::Type::Buy;
    });
}

Deals Deals::filterSell() const
{
    return filter([](Deal deal) -> bool
    {
        return deal.type() == Deal::Type::Sell;
    });
}

Deals Deals::sort(std::function<bool (Deal, Deal)> comparator) const
{
    Deals sorted(*this);
    std::sort(sorted.m_list.begin(), sorted.m_list.end(), comparator);
    return sorted;
}

Deals Deals::sortByVolume() const
{
    return sort([](Deal left, Deal right) -> bool
    {
        return left.volume() < right.volume();
    });
}

QList<quint64> Deals::toListOfVolumes() const
{
    return map<quint64>([](Deal deal) -> quint64
    {
        return deal.volume();
    });
}

QHash<int, Deals> Deals::splitByDayOfWeek() const
{
    return split<int>([](Deal deal) -> int
    {
        return deal.datetime().date().dayOfWeek();
    });
}

QHash<QDate, Deals> Deals::splitByDate() const
{
    return split<QDate>([](Deal deal) -> QDate
    {
        return deal.datetime().date();
    });
}

Deal Deals::first() const
{
    return m_list.first();
}

Deal Deals::last() const
{
    return m_list.last();
}

bool Deals::isEmpty() const
{
    return m_list.isEmpty();
}

int Deals::size() const
{
    return m_list.size();
}

QList<Deal> Deals::toList() const
{
    return m_list;
}

QString Deals::ticker() const
{
    return m_ticker;
}

void Deals::setTicker(QString ticker)
{
    m_ticker = ticker;
}
