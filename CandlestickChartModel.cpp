#include "CandlestickChartModel.h"

CandlestickChartModel::CandlestickChartModel(QObject* parent) :
    QAbstractTableModel(parent)
{
    updateData();
}

int CandlestickChartModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return m_quotations.size();
}

int CandlestickChartModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return 5; // Timestamp + OHLC, one column for one parameter
}

QVariant CandlestickChartModel::data(const QModelIndex& index, int role) const
{
    Q_UNUSED(role)

    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_quotations.size() || index.row() < 0)
        return QVariant();

    switch (index.column())
    {
        case 0: return m_quotations.at(index.row()).datetime.toMSecsSinceEpoch();
        case 1: return m_quotations.at(index.row()).open;
        case 2: return m_quotations.at(index.row()).high;
        case 3: return m_quotations.at(index.row()).low;
        case 4: return m_quotations.at(index.row()).close;

        default: return QVariant();
    }
}

QDateTime CandlestickChartModel::seriesFrom() const
{
    return m_seriesFrom;
}

QDateTime CandlestickChartModel::seriesTo() const
{
    return m_seriesTo;
}

QString CandlestickChartModel::seriesName() const
{
    return m_seriesName;
}

int CandlestickChartModel::seriesSize() const
{
    return m_seriesSize;
}

int CandlestickChartModel::hourFrom() const
{
    return m_hourFrom;
}

int CandlestickChartModel::minuteFrom() const
{
    return m_minuteFrom;
}

int CandlestickChartModel::intervalLength() const
{
    return m_intervalLength;
}

double CandlestickChartModel::minValue() const
{
    return m_minValue;
}

double CandlestickChartModel::maxValue() const
{
    return m_maxValue;
}

void CandlestickChartModel::updateData()
{
    beginResetModel();

    //    Quotations allQuotations = Application::instance().dataManager().quotations();
//    if (allQuotations.isEmpty())
//    {
//        m_quotations.clear();
//        setSeriesFrom(QDateTime(QDate(2000, 1, 1), QTime(0, 0)));
//        setSeriesTo(QDateTime(QDate(2000, 1, 1), QTime(0, 1)));
//        setSeriesSize(0);
//    }

    m_quotations.clear();

    for (int m = 45; m < 60; ++ m)
    {
        Quotation quotation;
        quotation.datetime = QDateTime(QDate(2017, 9, 1), QTime(17, m));
        quotation.open = 10.0 + rand() % 20;
        quotation.close = 10.0 + rand() % 20;
        quotation.high = 25.0;
        quotation.low = 5.0;
        m_quotations.append(quotation);
    }

    endResetModel();

    setSeriesFrom(m_quotations.first().datetime.addSecs(-30));
    setSeriesTo(m_quotations.last().datetime.addSecs(30));

    setSeriesName("Sber");

    setSeriesSize(rowCount());
}

void CandlestickChartModel::setSeriesFrom(QDateTime dateFrom)
{
    if (m_seriesFrom == dateFrom)
        return;

    m_seriesFrom = dateFrom;
    emit seriesFromChanged(m_seriesFrom);
}

void CandlestickChartModel::setSeriesTo(QDateTime dateTo)
{
    if (m_seriesTo == dateTo)
        return;

    m_seriesTo = dateTo;
    emit seriesToChanged(m_seriesTo);
}

void CandlestickChartModel::setSeriesName(QString seriesName)
{
    if (m_seriesName == seriesName)
        return;

    m_seriesName = seriesName;
    emit seriesNameChanged(m_seriesName);
}

void CandlestickChartModel::setSeriesSize(int seriesSize)
{
    if (m_seriesSize == seriesSize)
        return;

    m_seriesSize = seriesSize;
    emit seriesSizeChanged(m_seriesSize);
}

void CandlestickChartModel::setHourFrom(int hourFrom)
{
    if (m_hourFrom == hourFrom)
        return;

    m_hourFrom = hourFrom;
    emit hourFromChanged(m_hourFrom);
}

void CandlestickChartModel::setMinuteFrom(int minuteFrom)
{
    if (m_minuteFrom == minuteFrom)
        return;

    m_minuteFrom = minuteFrom;
    emit minuteFromChanged(m_minuteFrom);
}

void CandlestickChartModel::setIntervalLength(int intervalLength)
{
    if (m_intervalLength == intervalLength)
        return;

    m_intervalLength = intervalLength;
    emit intervalLengthChanged(m_intervalLength);
}

void CandlestickChartModel::setMinValue(double minValue)
{
    qWarning("Floating point comparison needs context sanity check");
    if (qFuzzyCompare(m_minValue, minValue))
        return;

    m_minValue = minValue;
    emit minValueChanged(m_minValue);
}

void CandlestickChartModel::setMaxValue(double maxValue)
{
    qWarning("Floating point comparison needs context sanity check");
    if (qFuzzyCompare(m_maxValue, maxValue))
        return;

    m_maxValue = maxValue;
    emit maxValueChanged(m_maxValue);
}