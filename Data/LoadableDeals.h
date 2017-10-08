#ifndef LOADABLEDEALS_H
#define LOADABLEDEALS_H

#include "LoadableData.h"

#include "Entities/Deals.h"

#include <QObject>

/// Implementation of LoadableData that load deals.
///
/// Usage example:
///     LoadableDeals loadableDeals;
///     loadableDeals.setTicker("TICKER");
///     loadableDeals.setDate(QDate::currentDate());
///     connect(&loadableDeals, &LoadableDeals::updated, [&loadableDeals](){
///         Deals deals = loadableDeals.toDeals();
///         /* do something with deals */
///     });
///     dataLoader.load(loadableDeals);
class LoadableDeals : public QObject, public LoadableData
{
    Q_OBJECT
    Q_INTERFACES(LoadableData)
public:
    LoadableDeals();

    /// @return Url from where data will be loaded.
    QString url() const override;

    /// Called when all data is loaded.
    /// @arg data Loaded raw data
    void updateFrom(QByteArray data) override;

    /// Called when error happened.
    void onError() override;

    QString ticker() const;
    QDate date() const;

    void setTicker(const QString& ticker);
    void setDate(const QDate& date);

    /// @return Loaded usual deals.
    /// If there are no deals loaded return empty deals object.
    Deals toDeals() const;

signals:
    /// Emitted after updateFrom(data).
    void updated();

    void error();

private:
    QString m_ticker;
    QDate m_date;
    Deals m_deals;
};

#endif // LOADABLEDEALS_H
