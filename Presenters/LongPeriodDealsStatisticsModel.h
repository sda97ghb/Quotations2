#ifndef LONGPERIODDEALSSTATISTICSMODEL_H
#define LONGPERIODDEALSSTATISTICSMODEL_H

#include <LongPeriodDealsLoader.h>
#include <QAbstractListModel>

#include "StatisticsDTO.h"

class LongPeriodDealsStatisticsModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(QString ticker READ ticker WRITE setTicker NOTIFY tickerChanged)

    Q_PROPERTY(QDate dateFrom READ dateFrom WRITE setDateFrom NOTIFY dateFromChanged)
    Q_PROPERTY(QDate dateTo READ dateTo WRITE setDateTo NOTIFY dateToChanged)
public:
    LongPeriodDealsStatisticsModel();

    enum Roles
    {
        StatisticsRole = Qt::UserRole + 1
    };

    QHash<int, QByteArray> roleNames() const override
    {
        static const QHash<int, QByteArray> roles = {
            { StatisticsRole, "statistics" }
        };
        return roles;
    }

    int rowCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role) const override;

    QString ticker() const;
    QDate dateFrom() const;
    QDate dateTo() const;

signals:
    void tickerChanged(QString ticker);
    void dateFromChanged(QDate dateFrom);
    void dateToChanged(QDate dateTo);

public slots:
    void updateData();

    void setTicker(QString ticker);
    void setDateFrom(QDate dateFrom);
    void setDateTo(QDate dateTo);

private slots:
    void calculateStatistics();

private:
    LongPeriodDealsLoader* m_longPeriodDealsLoader;
    QString m_ticker;
    QDate m_dateFrom;
    QDate m_dateTo;
    QList<StatisticsDTO> m_dayStatisticsList;
};

#endif // LONGPERIODDEALSSTATISTICSMODEL_H
