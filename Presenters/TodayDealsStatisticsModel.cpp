#include "Global.h"
#include "TodayDealsStatisticsModel.h"

namespace
{
    QString dayNumberToDayName(int dayNumber)
    {
        switch (dayNumber)
        {
        case 1: return "Monday";
        case 2: return "Tuesday";
        case 3: return "Wednesday";
        case 4: return "Thursday";
        case 5: return "Friday";
        case 6: return "Saturday";
        case 7: return "Sunday";
        default: return "Unknown";
        }
    }
}

TodayDealsStatisticsModel::TodayDealsStatisticsModel()
{
    m_statistics.title = "Today";
    connect(&m_loadableDeals, &LoadableDeals::updated,
            this, &TodayDealsStatisticsModel::onLoadableDealsUpdated);
}

QString TodayDealsStatisticsModel::ticker() const
{
    return m_loadableDeals.ticker();
}

QDate TodayDealsStatisticsModel::date() const
{
    return m_loadableDeals.date();
}

StatisticsDTO TodayDealsStatisticsModel::statistics() const
{
    return m_statistics;
}

void TodayDealsStatisticsModel::updateData()
{
    Global::instance().dataLoader().load(m_loadableDeals);
}

void TodayDealsStatisticsModel::setTicker(QString ticker)
{
    if (m_loadableDeals.ticker() == ticker)
        return;

    m_loadableDeals.setTicker(ticker);
    emit tickerChanged(m_loadableDeals.ticker());
}

void TodayDealsStatisticsModel::setDate(QDate date)
{
    if (m_loadableDeals.date() == date)
        return;

    m_loadableDeals.setDate(date);
    emit dateChanged(m_loadableDeals.date());
}

void TodayDealsStatisticsModel::setStatistics(StatisticsDTO statistics)
{
//    if (m_statistics == statistics)
//        return;

    m_statistics = statistics;
    emit statisticsChanged(m_statistics);
}

void TodayDealsStatisticsModel::onLoadableDealsUpdated()
{
    Deals deals = m_loadableDeals.toDeals();
    Deals buyDeals = deals.filterBuy();
    Deals sellDeals = deals.filterSell();

    StatisticsDTO statsics;

    statsics.title = dayNumberToDayName(date().dayOfWeek());

    statsics.numberOfDeals = deals.size();
    statsics.averageVolume = deals.averageVolume();
    statsics.minVolume = deals.minVolume();
    statsics.maxVolume = deals.maxVolume();

    statsics.numberOfBuyDeals = buyDeals.size();
    statsics.averageBuyVolume = buyDeals.averageVolume();
    statsics.minBuyVolume = buyDeals.minVolume();
    statsics.maxBuyVolume = buyDeals.maxVolume();

    statsics.numberOfSellDeals = sellDeals.size();
    statsics.averageSellVolume = sellDeals.averageVolume();
    statsics.minSellVolume = sellDeals.minVolume();
    statsics.maxSellVolume = sellDeals.maxVolume();

    setStatistics(statsics);
}
