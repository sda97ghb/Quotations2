#include "DataManager.h"
#include "RequestParameters.h"

#include <QDebug>
#include <QNetworkReply>
#include <QNetworkRequest>

DataManager::DataManager()
{
    connect(&m_networkAccessManager, &QNetworkAccessManager::finished,
            this, &DataManager::processReply);
}

DataManager::DataManager(const DataManager& other) :
    QObject(other.parent()),
    m_quotations(other.m_quotations)
{
    // Designed as empty
}

void DataManager::loadData()
{
//    for (int h = 10; h < 18; ++ h)
//        for (int m = 0; m < 60; ++ m)
//        {
//            double randOffset = (rand() % 50) / 10.0;
//            Quotation quotation;
//            quotation.datetime = QDateTime(QDate(2017, 9, 7), QTime(h, m));
//            quotation.low = 183.0 + randOffset;
//            quotation.high = 186.0 + randOffset;
//            quotation.open = 183.0 + randOffset;
//            quotation.close = 186.0 + randOffset;
//            m_quotations.append(quotation);
//        }
//    return;

    QString serviceAddress = "http://history.alor.ru/export/file.php";

    RequestParameters requestParameters;
    requestParameters.setMarketPlace(MarketPlace::MICEX);
    requestParameters.setTicker("Сбербанк");
    requestParameters.setTimeFrame(TimeFrame::Minute);
    requestParameters.setFrom(QDate(2017, 9, 11));
    requestParameters.setTo(QDate(2017, 9, 11));
    requestParameters.setFileName("");
    requestParameters.setFileFormat(FileFormat::Txt);
    requestParameters.setRecordFormat(RecordFormat::TICKER_PER_DATE_TIME_OPEN_HIGH_LOW_CLOSE);
    requestParameters.setDateFormat(DateFormat::YYYY_MM_DD);
    requestParameters.setTimeFormat(TimeFormat::HH_MM);
    requestParameters.setFieldSeparator(FieldSeparator::Comma);
    requestParameters.setDecimalSeparator(DecimalSeparator::Dot);
    requestParameters.setAddHeader(false);

    QString address = QString("%1?%2").arg(serviceAddress).arg(requestParameters.toGetRequestParameters());

    qDebug() << "Load data from" << address;
    m_networkAccessManager.get(QNetworkRequest(QUrl(address)));
}

Quotations DataManager::quotations() const
{
    return m_quotations;
}

void DataManager::processReply(QNetworkReply* reply)
{
    if (reply->error() != QNetworkReply::NoError)
    {
        qDebug() << "Bad reply";
        reply->deleteLater();
        return;
    }

    qDebug() << "Got reply";

    m_quotations = Quotations::from(reply->readAll());

    // TODO: delete this call
    doSomethingWith();

    reply->deleteLater();
}

void DataManager::doSomethingWith()
{
    for (Quotation record : m_quotations.toList())
        qDebug() << record;

    Quotations choosenOnes = m_quotations.laterThan(QDateTime(QDate(2017, 9, 7), QTime(10, 0))).inInterval(10);
    qDebug() << choosenOnes.max();
    qDebug() << choosenOnes.min();
}
