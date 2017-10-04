#ifndef LOADABLEDEALS_H
#define LOADABLEDEALS_H

#include "LoadableData.h"

#include "Entities/Deals.h"

#include <QObject>

class LoadableDeals : public QObject, public LoadableData
{
    Q_OBJECT
    Q_INTERFACES(LoadableData)
public:
    LoadableDeals();

    QString url() const override;
    void updateFrom(QByteArray data) override;
    void onError() override;

    QString ticker() const;
    QDate date() const;

    void setTicker(const QString& ticker);
    void setDate(const QDate& date);

    Deals toDeals() const;

signals:
    void updated();

private:
    QString m_ticker;
    QDate m_date;
    Deals m_deals;
};

#endif // LOADABLEDEALS_H
