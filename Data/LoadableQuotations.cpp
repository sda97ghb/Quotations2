#include "FinamRequestParameters.h"
#include "LoadableQuotations.h"

#include <QtDebug>

LoadableQuotations::LoadableQuotations() :
    QObject(nullptr)
{
    // Designed as empty
}

QString LoadableQuotations::url() const
{
    finam::Ticker ticker = (m_ticker == "SBER") ? finam::Ticker::SBER :
                                                  finam::Ticker::GAZP;
    return QString("%1?%2")
            .arg(finam::EXPORT_SERVICE_ADDRESS)
            .arg(finam::FinamRequestParameters::forQuotations(ticker, date())
                 .toGetRequestParameters());
}

void LoadableQuotations::updateFrom(QByteArray data)
{
    m_quotations = Quotations::from(data);
    emit updated();
}

void LoadableQuotations::onError()
{
    qWarning() << "Quotations loading error";
}

QDate LoadableQuotations::date() const
{
    return m_date;
}

QString LoadableQuotations::ticker() const
{
    return m_ticker;
}

void LoadableQuotations::setDate(const QDate& date)
{
    m_date = date;
}

void LoadableQuotations::setTicker(const QString& ticker)
{
    m_ticker = ticker;
}

Quotations LoadableQuotations::toQuotations() const
{
    return m_quotations;
}
