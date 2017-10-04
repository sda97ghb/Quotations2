#include "BetterCpp.h"
#include "Global.h"
#include "LongPeriodDealsLoader.h"

LongPeriodDealsLoader::LongPeriodDealsLoader(QString ticker, QDate from, QDate to) :
    m_daysLoaded(0)
{
    unless (from.isValid() && to.isValid() && from <= to)
        throw InvalidInputException();
    for (QDate date = from; date <= to; date = date.addDays(1))
    {
        if (date.dayOfWeek() == 6 || date.dayOfWeek() == 7)
            continue;
        LoadableDeals* loadableDeals = new LoadableDeals;
        loadableDeals->setDate(date);
        loadableDeals->setTicker(ticker);
        connect(loadableDeals, &LoadableDeals::updated,
                this, &LongPeriodDealsLoader::onDealsUpdated);
        m_loadableDealsList.append(loadableDeals);
    }
    for (LoadableDeals* loadableDeals : m_loadableDealsList)
        Global::instance().dataLoader().load(loadableDeals);
}

void LongPeriodDealsLoader::onDealsUpdated()
{
    LoadableDeals* loadableDeals = qobject_cast<LoadableDeals*>(sender());
    if (loadableDeals == nullptr)
        return;
    Deals deals = loadableDeals->toDeals();
    if (deals.isEmpty())
        return_after Global::instance().dataLoader().load(loadableDeals);
    ++ m_daysLoaded;
    if (m_daysLoaded == m_loadableDealsList.size())
        emit allDaysLoaded();
}

QList<LoadableDeals*> LongPeriodDealsLoader::loadableDealsList() const
{
    return m_loadableDealsList;
}

Deals LongPeriodDealsLoader::allDeals() const
{
    Deals deals;
    for (LoadableDeals* loadableDeals : m_loadableDealsList)
        for (Deal deal : loadableDeals->toDeals().toList())
            deals.append(deal);
    return deals;
}
