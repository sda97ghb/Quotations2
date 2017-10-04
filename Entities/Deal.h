#ifndef OPERATION_H
#define OPERATION_H

#include "BetterCpp.h"

#include <QDateTime>
#include <QString>

class Deal
{
public:
    class Type
    {
        BETTER_ENUM
    public:
        enum
        {
            Unknown,
            Buy,
            Sell
        };

        BETTER_ENUM_SHORT_INIT(Type)

        operator QString() const;
        QString toString() const { return QString(*this); }
    };

    Deal();

    operator QString() const;

    bool isValid() const;

    Type type() const;
    QDateTime datetime() const;
    quint64 id() const;
    double last() const;
    quint64 volume() const;

    void setType(Type type);
    void setDatetime(const QDateTime& datetime);
    void setId(quint64 id);
    void setLast(double last);
    void setVolume(quint64 volume);

private:
    Type m_type;

    QDateTime m_datetime;

    quint64 m_id;

    double m_last;
    quint64 m_volume;

};

#endif // OPERATION_H
