#include "LongPeriodDealsStatisticsModel.h"

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

LongPeriodDealsStatisticsModel::LongPeriodDealsStatisticsModel() :
    m_longPeriodDealsLoader(nullptr)
{
}

int LongPeriodDealsStatisticsModel::rowCount(const QModelIndex& parent) const
{
    return m_dayStatisticsList.size();
}

QVariant LongPeriodDealsStatisticsModel::data(const QModelIndex& index, int role) const
{
    unless (index.isValid())
        return QVariant();

    if (index.row() < 0 || index.row() >= m_dayStatisticsList.size())
        return QVariant();

    switch (role)
    {
    case StatisticsRole: return QVariant::fromValue(m_dayStatisticsList.at(index.row()));
    default: return QVariant();
    }
}

QString LongPeriodDealsStatisticsModel::ticker() const
{
    return m_ticker;
}

QDate LongPeriodDealsStatisticsModel::dateFrom() const
{
    return m_dateFrom;
}

QDate LongPeriodDealsStatisticsModel::dateTo() const
{
    return m_dateTo;
}

void LongPeriodDealsStatisticsModel::updateData()
{
    unless (m_longPeriodDealsLoader == nullptr)
        delete m_longPeriodDealsLoader;
    m_longPeriodDealsLoader = new LongPeriodDealsLoader(ticker(), dateFrom(), dateTo());
    connect(m_longPeriodDealsLoader, &LongPeriodDealsLoader::allDaysLoaded,
            this, &LongPeriodDealsStatisticsModel::calculateStatistics);
}

void LongPeriodDealsStatisticsModel::setTicker(QString ticker)
{
    if (m_ticker == ticker)
        return;

    m_ticker = ticker;
    emit tickerChanged(m_ticker);
}

void LongPeriodDealsStatisticsModel::setDateFrom(QDate dateFrom)
{
    if (m_dateFrom == dateFrom)
        return;

    m_dateFrom = dateFrom;
    emit dateFromChanged(m_dateFrom);
}

void LongPeriodDealsStatisticsModel::setDateTo(QDate dateTo)
{
    if (m_dateTo == dateTo)
        return;

    m_dateTo = dateTo;
    emit dateToChanged(m_dateTo);
}

void LongPeriodDealsStatisticsModel::calculateStatistics()
{
    beginResetModel();
    m_dayStatisticsList.clear();

    Deals allDealsInInterval = m_longPeriodDealsLoader->allDeals();
    QHash<int, Deals> splittedByDayOfWeek = allDealsInInterval.splitByDayOfWeek();
    for (QHash<int, Deals>::iterator iter = splittedByDayOfWeek.begin();
         iter != splittedByDayOfWeek.end(); ++ iter)
    {
        int dayOfWeek = iter.key();
        Deals deals = iter.value();
        Deals buyDeals = deals.filterBuy();
        Deals sellDeals = deals.filterSell();

        auto f = [](Deals deals) -> int
        {
            QHash<QDate, Deals> splittedByDate = deals.splitByDate();
            int totalNumberOfDeals = 0;
            for (Deals dealsInSomeDay : splittedByDate)
                totalNumberOfDeals += dealsInSomeDay.size();
            int averageNumberOfDeals = 0;
            unless (splittedByDate.isEmpty())
                averageNumberOfDeals = totalNumberOfDeals / splittedByDate.size();
            return averageNumberOfDeals;
        };

        int averageNumberOfDeals = f(deals);
        int averageNumberOfBuyDeals = f(buyDeals);
        int averageNumberOfSellDeals = f(sellDeals);

        qInfo() << "Day of week" << dayOfWeek;

        qInfo() << "Average volume" << deals.averageVolume();
        qInfo() << "Average buy volume" << deals.filterBuy().averageVolume();
        qInfo() << "Average sell volume" << deals.filterSell().averageVolume();

        qInfo() << "Min volume" << deals.minVolume();
        qInfo() << "Min buy volume" << deals.filterBuy().minVolume();
        qInfo() << "Min sell volume" << deals.filterSell().minVolume();

        qInfo() << "Max volume" << deals.maxVolume();
        qInfo() << "Max buy volume" << deals.filterBuy().maxVolume();
        qInfo() << "Max sell volume" << deals.filterSell().maxVolume();

        qInfo() << "Average number of deals" << averageNumberOfDeals;
        qInfo() << "Average number of buy deals" << averageNumberOfBuyDeals;
        qInfo() << "Average number of sell deals" << averageNumberOfSellDeals;

        StatisticsDTO statsics;
        statsics.title = QString::number(dayOfWeek);
        statsics.numberOfDeals = averageNumberOfDeals;
        statsics.averageVolume = deals.averageVolume();
        statsics.minVolume = deals.minVolume();
        statsics.maxVolume = deals.maxVolume();
        statsics.numberOfBuyDeals = averageNumberOfBuyDeals;
        statsics.averageBuyVolume = buyDeals.averageVolume();
        statsics.minBuyVolume = buyDeals.minVolume();
        statsics.maxBuyVolume = buyDeals.maxVolume();
        statsics.numberOfSellDeals = averageNumberOfSellDeals;
        statsics.averageSellVolume = sellDeals.averageVolume();
        statsics.minSellVolume = sellDeals.minVolume();
        statsics.maxSellVolume = sellDeals.maxVolume();
        m_dayStatisticsList.append(statsics);
    }

    std::sort(m_dayStatisticsList.begin(), m_dayStatisticsList.end(), [](StatisticsDTO left, StatisticsDTO right)
    {
        return left.title < right.title;
    });
    for (StatisticsDTO& item : m_dayStatisticsList)
        item.title = dayNumberToDayName(item.title.toInt());
    endResetModel();
}
