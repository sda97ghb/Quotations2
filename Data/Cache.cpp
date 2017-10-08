#include "Cache.h"

#include "BetterCpp.h"

bool Cache::check(QString address) const
{
    return m_loadedData.contains(address);
}

void Cache::save(QString address, QByteArray data)
{
    m_loadedData[address] = data;
}

QByteArray Cache::get(QString address) const
{
    unless (check(address))
        return QByteArray();
    return m_loadedData[address];
}
