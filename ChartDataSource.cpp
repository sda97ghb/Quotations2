#include "Application.h"
#include "ChartDataSource.h"

#include <QCandlestickSet>
#include <QXYSeries>

using namespace QtCharts;

Q_DECLARE_METATYPE(QAbstractSeries*)
Q_DECLARE_METATYPE(QAbstractAxis*)

ChartDataSource::ChartDataSource(QObject* parent) :
    QObject(parent)
{
    // Designed as empty
}

int ChartDataSource::hourFrom() const
{
    return m_hourFrom;
}

int ChartDataSource::minuteFrom() const
{
    return m_minuteFrom;
}

int ChartDataSource::intervalLength() const
{
    return m_intervalLength;
}

double ChartDataSource::minValue() const
{
    return m_minValue;
}

double ChartDataSource::maxValue() const
{
    return m_maxValue;
}

QDateTime ChartDataSource::from() const
{
    return m_from;
}

QDateTime ChartDataSource::to() const
{
    return m_to;
}

void ChartDataSource::update()
{
    Quotations allQuotations = Application::instance().dataManager().quotations();
    if (allQuotations.isEmpty())
    {
        m_currentQuotations = Quotations();
        setMinValue(0.0);
        setMaxValue(0.0);
        setFrom(QDateTime(QDate(2000, 1, 1), QTime(0, 0)));
        setTo(QDateTime(QDate(2000, 1, 1), QTime(0, 1)));
        updateSeries();
        emit updated();
        return;
    }

    QDateTime from(allQuotations.first().datetime.date(), QTime(m_hourFrom, m_minuteFrom));
    m_currentQuotations = allQuotations.laterThan(from).inInterval(m_intervalLength - 1);

    if (m_currentQuotations.isEmpty())
    {
        m_currentQuotations = Quotations();
        setMinValue(0.0);
        setMaxValue(0.0);
        setFrom(QDateTime(QDate(2000, 1, 1), QTime(0, 0)));
        setTo(QDateTime(QDate(2000, 1, 1), QTime(0, 1)));
        updateSeries();
        emit updated();
        return;
    }

    setMinValue(m_currentQuotations.min());
    setMaxValue(m_currentQuotations.max());

    setFrom(m_currentQuotations.first().datetime.addSecs(-30));
    setTo(m_currentQuotations.last().datetime.addSecs(30));

    updateSeries();

    emit updated();
}

void ChartDataSource::updateSeries(QAbstractSeries* series)
{
    if (series == nullptr)
        return;

    QCandlestickSeries* candlestickSeries = static_cast<QCandlestickSeries*>(series);
    candlestickSeries->clear();
    candlestickSeries->append(m_candlestickSeries);
}

void ChartDataSource::setHourFrom(int hourFrom)
{
    if (m_hourFrom == hourFrom)
        return;

    m_hourFrom = hourFrom;
    emit hourFromChanged(m_hourFrom);
}

void ChartDataSource::setMinuteFrom(int minuteFrom)
{
    if (m_minuteFrom == minuteFrom)
        return;

    m_minuteFrom = minuteFrom;
    emit minuteFromChanged(m_minuteFrom);
}

void ChartDataSource::setIntervalLength(int intervalLength)
{
    if (m_intervalLength == intervalLength)
        return;

    m_intervalLength = intervalLength;
    emit intervalLengthChanged(m_intervalLength);
}

void ChartDataSource::setMinValue(double minValue)
{
    if (m_minValue == minValue)
        return;

    m_minValue = minValue;
    emit minValueChanged(m_minValue);
}

void ChartDataSource::setMaxValue(double maxValue)
{
    if (m_maxValue == maxValue)
        return;

    m_maxValue = maxValue;
    emit maxValueChanged(m_maxValue);
}

void ChartDataSource::setFrom(QDateTime from)
{
    if (m_from == from)
        return;

    m_from = from;
    emit fromChanged(m_from);
}

void ChartDataSource::setTo(QDateTime to)
{
    if (m_to == to)
        return;

    m_to = to;
    emit toChanged(m_to);
}

void ChartDataSource::updateSeries()
{
    m_candlestickSeries.clear();
    for (Quotation quotation : m_currentQuotations.toList())
    {
        m_candlestickSeries.append(new QCandlestickSet(quotation.open, quotation.high,
                                                       quotation.low, quotation.close,
                                                       quotation.datetime.toMSecsSinceEpoch()));
    }
}
