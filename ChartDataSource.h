#ifndef CHARTDATASOURCE_H
#define CHARTDATASOURCE_H

#include "Quotations.h"

#include <QAbstractSeries>
#include <QCandlestickSeries>

using QtCharts::QAbstractSeries;
using QtCharts::QCandlestickSet;

class ChartDataSource : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int hourFrom READ hourFrom WRITE setHourFrom NOTIFY hourFromChanged)
    Q_PROPERTY(int minuteFrom READ minuteFrom WRITE setMinuteFrom NOTIFY minuteFromChanged)
    Q_PROPERTY(int intervalLength READ intervalLength WRITE setIntervalLength NOTIFY intervalLengthChanged)

    Q_PROPERTY(double minValue READ minValue NOTIFY minValueChanged)
    Q_PROPERTY(double maxValue READ maxValue NOTIFY maxValueChanged)

    Q_PROPERTY(QDateTime from READ from WRITE setFrom NOTIFY fromChanged)
    Q_PROPERTY(QDateTime to READ to WRITE setTo NOTIFY toChanged)
public:
    explicit ChartDataSource(QObject* parent = nullptr);

    int hourFrom() const;
    int minuteFrom() const;
    int intervalLength() const;

    double minValue() const;
    double maxValue() const;

    QDateTime from() const;
    QDateTime to() const;

public slots:
    void update();

    void updateSeries(QAbstractSeries* series);

    void setHourFrom(int hourFrom);
    void setMinuteFrom(int minuteFrom);
    void setIntervalLength(int intervalLength);

signals:
    void updated();

    void hourFromChanged(int hourFrom);
    void minuteFromChanged(int minuteFrom);
    void intervalLengthChanged(int intervalLength);

    void minValueChanged(double minValue);
    void maxValueChanged(double maxValue);

    void fromChanged(QDateTime from);
    void toChanged(QDateTime to);

private:
    void setMinValue(double minValue);
    void setMaxValue(double maxValue);

    void setFrom(QDateTime from);
    void setTo(QDateTime to);

    void updateSeries();

    int m_hourFrom;
    int m_minuteFrom;
    int m_intervalLength;

    double m_minValue;
    double m_maxValue;

    Quotations m_currentQuotations;

    QList<QCandlestickSet*> m_candlestickSeries;
    QDateTime m_from;
    QDateTime m_to;
};

#endif // CHARTDATASOURCE_H
