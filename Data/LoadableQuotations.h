#ifndef LOADABLE_QUOTATIONS_H
#define LOADABLE_QUOTATIONS_H

#include "LoadableData.h"

#include "Entities/Quotations.h"

#include <QObject>

/// Implementation of LoadableData that load quotations.
/// Usage example:
///     LoadableQuotations loadableQuotations;
///     loadableQuotations.setTicker("TICKER");
///     loadableQuotations.setDate(QDate::currentDate());
///     connect(&loadableQuotations, &LoadableQuotations::updated, [&loadableQuotations]()
///     {
///         Quotations quotations = loadableQuotations.toQuotations();
///         /* do something with quotations */
///     });
///     dataLoader.load(loadableQuotations);
class LoadableQuotations : public QObject, public LoadableData
{
    Q_OBJECT
    Q_INTERFACES(LoadableData)
public:
    LoadableQuotations();

    /// @return Url from where data will be loaded.
    QString url() const override;

    /// Called when all data is loaded.
    /// @arg data Loaded raw data
    void updateFrom(QByteArray data) override;

    /// Called when error happened.
    void onError() override;

    QDate date() const;
    QString ticker() const;

    void setDate(const QDate& date);
    void setTicker(const QString& ticker);

    /// @return Loaded usual quotations.
    /// If there are no quotations loaded return empty quotations object.
    Quotations toQuotations() const;

signals:
    /// Emitted after updateFrom(data).
    void updated();

private:
    QString m_ticker;
    QDate m_date;
    Quotations m_quotations;
};

#endif // LOADABLE_QUOTATIONS_H
