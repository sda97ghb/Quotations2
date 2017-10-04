#include "Deal.h"

Deal::Type::operator QString() const
{
    switch (value())
    {
    case Buy:  return "bought";
    case Sell: return "sold";
    default:   return "unknown";
    }
}

Deal::Deal() :
    m_type(Type::Unknown),
    m_datetime(),
    m_id(0ull),
    m_last(0.0),
    m_volume(0ull)
{
    // Designed as empty
}

bool Deal::isValid() const
{
    return m_datetime.isValid() &&
            (m_volume > 0ull) &&
            (m_type != Type::Unknown);
}

Deal::Type Deal::type() const
{
    return m_type;
}

QDateTime Deal::datetime() const
{
    return m_datetime;
}

quint64 Deal::id() const
{
    return m_id;
}

double Deal::last() const
{
    return m_last;
}

quint64 Deal::volume() const
{
    return m_volume;
}

void Deal::setType(Type type)
{
    m_type = type;
}

void Deal::setDatetime(const QDateTime& datetime)
{
    m_datetime = datetime;
}

void Deal::setId(quint64 id)
{
    m_id = id;
}

void Deal::setLast(double last)
{
    m_last = last;
}

void Deal::setVolume(quint64 volume)
{
    m_volume = volume;
}

Deal::operator QString() const
{
    if (!isValid())
        return "Invalid";

    return QString("%1 %2 %3 %4 for the price of %5")
            .arg(datetime().toString("yyyy.MM.dd hh:mm:ss"))
            .arg(QString::number(id()))
            .arg(type().toString())
            .arg(QString::number(volume()))
            .arg(QString::number(last()));
}
