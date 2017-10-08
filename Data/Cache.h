#ifndef CACHE_H
#define CACHE_H

#include <QDate>
#include <QHash>

class Cache
{
public:
    bool check(QString address) const;
    void save(QString address, QByteArray data);
    QByteArray get(QString address) const;

private:
    QHash<QString, QByteArray> m_loadedData;
};

#endif // CACHE_H
