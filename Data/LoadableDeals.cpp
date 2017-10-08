#include "FinamRequestParameters.h"
#include "LoadableDeals.h"

#include <QtDebug>

LoadableDeals::LoadableDeals() :
    QObject(nullptr)
{
    // Designed as empty
}

QString LoadableDeals::url() const
{
    finam::Ticker ticker = (m_ticker == "SBER") ? finam::Ticker::SBER :
                                                  finam::Ticker::GAZP;
    return QString("%1?%2")
            .arg("http://export.finam.ru/export9.out")
            .arg(finam::FinamRequestParameters::forDeals(ticker, date())
                 .toGetRequestParameters());
}

void LoadableDeals::updateFrom(QByteArray data)
{
    m_deals = Deals::from(data);
    m_deals.setTicker(ticker());
    emit updated();
}

void LoadableDeals::onError()
{
    qWarning() << "Deals loading error";
    emit error();
}

QString LoadableDeals::ticker() const
{
    return m_ticker;
}

QDate LoadableDeals::date() const
{
    return m_date;
}

void LoadableDeals::setTicker(const QString& ticker)
{
    m_ticker = ticker;
}

void LoadableDeals::setDate(const QDate& date)
{
    m_date = date;
}

Deals LoadableDeals::toDeals() const
{
    return m_deals;
}
