#ifndef TODAYDEALSSTATISTICSMODEL_H
#define TODAYDEALSSTATISTICSMODEL_H

#include "Data/LoadableDeals.h"
#include "StatisticsDTO.h"

class TodayDealsStatisticsModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString ticker READ ticker WRITE setTicker NOTIFY tickerChanged)
    Q_PROPERTY(QDate date READ date WRITE setDate NOTIFY dateChanged)
    Q_PROPERTY(StatisticsDTO statistics READ statistics WRITE setStatistics NOTIFY statisticsChanged)
public:
    TodayDealsStatisticsModel();

    QString ticker() const;
    QDate date() const;
    StatisticsDTO statistics() const;

signals:
    void tickerChanged(QString ticker);
    void dateChanged(QDate date);
    void statisticsChanged(StatisticsDTO statistics);

public slots:
    void updateData();

    void setTicker(QString ticker);
    void setDate(QDate date);

private slots:
    void setStatistics(StatisticsDTO statistics);

    void onLoadableDealsUpdated();

private:
    StatisticsDTO m_statistics;

    LoadableDeals m_loadableDeals;
};

#endif // TODAYDEALSSTATISTICSMODEL_H
