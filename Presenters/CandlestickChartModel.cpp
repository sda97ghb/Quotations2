#include "Global.h"
#include "BetterCpp.h"
#include "CandlestickChartModel.h"

CandlestickChartModel::CandlestickChartModel(QObject* parent) :
    QAbstractTableModel(parent)
{
    resetData();

    connect(this, &CandlestickChartModel::hourFromChanged,
            this, &CandlestickChartModel::updateDisplayedData);
    connect(this, &CandlestickChartModel::minuteFromChanged,
            this, &CandlestickChartModel::updateDisplayedData);
    connect(this, &CandlestickChartModel::intervalLengthChanged,
            this, &CandlestickChartModel::updateDisplayedData);

    connect(&m_loadableQuotations, &LoadableQuotations::updated,
            this, &CandlestickChartModel::updateDisplayedData);
}

int CandlestickChartModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    // Can be less than interval length when hour and minute is too large.
    return m_displayedQuotations.size();
}

int CandlestickChartModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return 5; // Timestamp + OHLC, one column for each parameter
}

QVariant CandlestickChartModel::data(const QModelIndex& index, int role) const
{
    Q_UNUSED(role)

    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_displayedQuotations.size() || index.row() < 0)
        return QVariant();

    switch (index.column())
    {
        case 0: return m_displayedQuotations.at(index.row()).datetime().toMSecsSinceEpoch();
        case 1: return m_displayedQuotations.at(index.row()).open();
        case 2: return m_displayedQuotations.at(index.row()).high();
        case 3: return m_displayedQuotations.at(index.row()).low();
        case 4: return m_displayedQuotations.at(index.row()).close();

        default: return QVariant();
    }
}

QString CandlestickChartModel::ticker() const
{
    return m_ticker;
}

QDate CandlestickChartModel::date() const
{
    return m_date;
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

QDateTime CandlestickChartModel::seriesFrom() const
{
    return dateTimeFrom().addSecs(-30);
}

QDateTime CandlestickChartModel::seriesTo() const
{
    return dateTimeTo().addSecs(30);
}

QString CandlestickChartModel::seriesName() const
{
    return m_seriesName;
}

int CandlestickChartModel::seriesSize() const
{
    return rowCount();
}

void CandlestickChartModel::loadData()
{
    m_loadableQuotations.setTicker(ticker());
    m_loadableQuotations.setDate(date());
    Global::instance().dataLoader().load(m_loadableQuotations);
}

void CandlestickChartModel::updateDisplayedData()
{
    Quotations allQuotations = m_loadableQuotations.toQuotations();
    if (allQuotations.isEmpty())
        return_after resetData();

    Quotations currentQuotations = allQuotations.inInterval(dateTimeFrom(), dateTimeTo());
    if (currentQuotations.isEmpty())
        return_after resetData();

    beginResetModel();
    m_displayedQuotations = currentQuotations.toList();
    endResetModel();

    setMinValue(currentQuotations.min());
    setMaxValue(currentQuotations.max());

    emit seriesFromChanged(seriesFrom());
    emit seriesToChanged(seriesTo());

    setSeriesName(ticker());

    emit seriesSizeChanged(seriesSize());
}

void CandlestickChartModel::resetData()
{
    beginResetModel();
    m_displayedQuotations.clear();
    endResetModel();
    setMinValue(0.0);
    setMaxValue(1.0);
    emit seriesFromChanged(seriesFrom());
    emit seriesToChanged(seriesTo());
    setSeriesName("Data is unavailable");
    emit seriesSizeChanged(seriesSize());
}

void CandlestickChartModel::setTicker(QString ticker)
{
    if (m_ticker == ticker)
        return;

    m_ticker = ticker;
    emit tickerChanged(m_ticker);
}

void CandlestickChartModel::setDate(QDate date)
{
    if (m_date == date)
        return;

    m_date = date;
    emit dateChanged(m_date);
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

void CandlestickChartModel::setSeriesName(QString seriesName)
{
    if (m_seriesName == seriesName)
        return;

    m_seriesName = seriesName;
    emit seriesNameChanged(m_seriesName);
}

QDateTime CandlestickChartModel::dateTimeFrom() const
{
    return QDateTime(date(), QTime(hourFrom(), minuteFrom()));
}

QDateTime CandlestickChartModel::dateTimeTo() const
{
    return QDateTime(date(), QTime(hourFrom(), minuteFrom()))
            .addSecs(60 * intervalLength());
}
