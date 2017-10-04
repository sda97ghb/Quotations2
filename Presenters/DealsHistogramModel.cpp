#include "DealsHistogramModel.h"
#include "Global.h"
#include "Histogram.h"

#include <QDebug>

DealsHistogramModel::DealsHistogramModel() :
    m_buyMinVolume(0),
    m_sellMinVolume(0),
    m_buyMaxVolume(0),
    m_sellMaxVolume(0),
    m_buyAverageVolume(0),
    m_sellAverageVolume(0)
{
    QList<quint64> fakeBuyHistogramData;
    QList<quint64> fakeSellHistogramData;
    for (int i = 0; i < m_numberOfIntervals; ++ i)
    {
        fakeBuyHistogramData.append(1);
        fakeSellHistogramData.append(1);
    }
    m_buyHistogramSeriesData = fakeBuyHistogramData;
    m_sellHistogramSeriesData = fakeSellHistogramData;

    m_loadableDeals.setTicker("SBER");
    m_loadableDeals.setDate(QDate(2017, 9, 28));//::currentDate());

    connect(&m_loadableDeals, &LoadableDeals::updated,
            this, &DealsHistogramModel::updateData);
    connect(this, &DealsHistogramModel::numberOfIntervalsChanged,
            this, &DealsHistogramModel::updateData);
    connect(this, &DealsHistogramModel::volumeFromChanged,
            this, &DealsHistogramModel::updateData);
    connect(this, &DealsHistogramModel::volumeToChanged,
            this, &DealsHistogramModel::updateData);
}

QVariant DealsHistogramModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(orientation)
    Q_UNUSED(role)
    switch (section)
    {
    case 0: return "Buy";
    case 1: return "Sell";
    default: return QVariant();
    }
}

int DealsHistogramModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return 1;//2; // Two sets (buy and sell)
}
// 8000
int DealsHistogramModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return m_numberOfIntervals;
}

QVariant DealsHistogramModel::data(const QModelIndex& index, int role) const
{
    Q_UNUSED(role)

    unless (index.isValid())
        return QVariant();

    if (index.row() < 0 || index.row() > 1)
        return QVariant();

    if (index.column() < 0 || index.column() > m_numberOfIntervals)
        return QVariant();

    switch (index.row())
    {
    case 0: return m_histogramSeriesData.at(index.column());
//    case 0: return m_buyHistogramSeriesData.at(index.column());
//    case 1: return m_sellHistogramSeriesData.at(index.column());
    default: return 0;
    };
}

int DealsHistogramModel::numberOfIntervals() const
{
    return m_numberOfIntervals;
}

quint64 DealsHistogramModel::volumeFrom() const
{
    return m_volumeFrom;
}

quint64 DealsHistogramModel::volumeTo() const
{
    return m_volumeTo;
}

quint64 DealsHistogramModel::maxValue() const
{
    auto maxBuyHistogramValueIter = std::max_element(m_buyHistogramSeriesData.begin(),
                                                     m_buyHistogramSeriesData.end());
    quint64 maxBuyHistogramValue = maxBuyHistogramValueIter == m_buyHistogramSeriesData.end() ? 0 : *maxBuyHistogramValueIter;
    auto maxSellHistogramValueIter = std::max_element(m_sellHistogramSeriesData.begin(),
                                                      m_sellHistogramSeriesData.end());
    quint64 maxSellHistogramValue = maxSellHistogramValueIter == m_sellHistogramSeriesData.end() ? 0 : *maxSellHistogramValueIter;
    return maxBuyHistogramValue > maxSellHistogramValue ? maxBuyHistogramValue :
                                                          maxSellHistogramValue;
}

quint64 DealsHistogramModel::buyMinVolume() const
{
    return m_buyMinVolume;
}

quint64 DealsHistogramModel::sellMinVolume() const
{
    return m_sellMinVolume;
}

quint64 DealsHistogramModel::buyMaxVolume() const
{
    return m_buyMaxVolume;
}

quint64 DealsHistogramModel::sellMaxVolume() const
{
    return m_sellMaxVolume;
}

quint64 DealsHistogramModel::buyAverageVolume() const
{
    return m_buyAverageVolume;
}

quint64 DealsHistogramModel::sellAverageVolume() const
{
    return m_sellAverageVolume;
}

quint64 DealsHistogramModel::minVolume() const
{
    return m_minVolume;
}

quint64 DealsHistogramModel::maxVolume() const
{
    return m_maxVolume;
}

void DealsHistogramModel::reload()
{
    Global::instance().dataLoader().load(m_loadableDeals);
}

void DealsHistogramModel::updateData()
{
    beginResetModel();
    auto deals = m_loadableDeals.toDeals();
    auto buyDeals = deals.filterBuy();
    auto sellDeals = deals.filterSell();
    m_histogramSeriesData = histogram::calculate(deals.toListOfVolumes(), numberOfIntervals());
    m_buyHistogramSeriesData = histogram::calculate(buyDeals.toListOfVolumes(), numberOfIntervals());
    m_sellHistogramSeriesData = histogram::calculate(sellDeals.toListOfVolumes(), numberOfIntervals());
    setMinVolume(deals.minVolume());
    setMaxVolume(deals.maxVolume());
    setBuyMinVolume(buyDeals.minVolume());
    setSellMinVolume(sellDeals.minVolume());
    setBuyMaxVolume(buyDeals.maxVolume());
    setSellMaxVolume(sellDeals.maxVolume());
    setBuyAverageVolume(buyDeals.averageVolume());
    setSellAverageVolume(sellDeals.averageVolume());
//    QList<quint64> fakeBuyHistogramData;
//    QList<quint64> fakeSellHistogramData;
//    for (int i = 0; i < m_numberOfIntervals; ++ i)
//    {
//        fakeBuyHistogramData.append(i * 1000);//rand() % 100);
//        fakeSellHistogramData.append(m_numberOfIntervals - i);//rand() % 100);
//    }
//    m_buyHistogramSeriesData = fakeBuyHistogramData;
//    m_sellHistogramSeriesData = fakeSellHistogramData;
    qInfo() << m_buyHistogramSeriesData;
    qInfo() << m_sellHistogramSeriesData;
    endResetModel();
    emit maxValueChanged(maxValue());
}

void DealsHistogramModel::setNumberOfIntervals(int numberOfIntervals)
{
    if (m_numberOfIntervals == numberOfIntervals)
        return;

    m_numberOfIntervals = numberOfIntervals;
    emit numberOfIntervalsChanged(m_numberOfIntervals);
}

void DealsHistogramModel::setVolumeFrom(quint64 volumeFrom)
{
    if (m_volumeFrom == volumeFrom)
        return;

    m_volumeFrom = volumeFrom;
    emit volumeFromChanged(m_volumeFrom);
}

void DealsHistogramModel::setVolumeTo(quint64 volumeTo)
{
    if (m_volumeTo == volumeTo)
        return;

    m_volumeTo = volumeTo;
    emit volumeToChanged(m_volumeTo);
}

void DealsHistogramModel::setMinVolume(quint64 minVolume)
{
    if (m_minVolume == minVolume)
        return;

    m_minVolume = minVolume;
    emit minVolumeChanged(m_minVolume);
}

void DealsHistogramModel::setMaxVolume(quint64 maxVolume)
{
    if (m_maxVolume == maxVolume)
        return;

    m_maxVolume = maxVolume;
    emit maxVolumeChanged(m_maxVolume);
}

void DealsHistogramModel::setBuyMinVolume(quint64 buyMinVolume)
{
    if (m_buyMinVolume == buyMinVolume)
        return;

    m_buyMinVolume = buyMinVolume;
    emit buyMinVolumeChanged(m_buyMinVolume);
}

void DealsHistogramModel::setSellMinVolume(quint64 sellMinVolume)
{
    if (m_sellMinVolume == sellMinVolume)
        return;

    m_sellMinVolume = sellMinVolume;
    emit sellMinVolumeChanged(m_sellMinVolume);
}

void DealsHistogramModel::setBuyMaxVolume(quint64 buyMaxVolume)
{
    if (m_buyMaxVolume == buyMaxVolume)
        return;

    m_buyMaxVolume = buyMaxVolume;
    emit buyMaxVolumeChanged(m_buyMaxVolume);
}

void DealsHistogramModel::setSellMaxVolume(quint64 sellMaxVolume)
{
    if (m_sellMaxVolume == sellMaxVolume)
        return;

    m_sellMaxVolume = sellMaxVolume;
    emit sellMaxVolumeChanged(m_sellMaxVolume);
}

void DealsHistogramModel::setBuyAverageVolume(quint64 buyAverageVolume)
{
    if (m_buyAverageVolume == buyAverageVolume)
        return;

    m_buyAverageVolume = buyAverageVolume;
    emit buyAverageVolumeChanged(m_buyAverageVolume);
}

void DealsHistogramModel::setSellAverageVolume(quint64 sellAverageVolume)
{
    if (m_sellAverageVolume == sellAverageVolume)
        return;

    m_sellAverageVolume = sellAverageVolume;
    emit sellAverageVolumeChanged(m_sellAverageVolume);
}
