#ifndef CANDLESTICKCHARTMODEL_H
#define CANDLESTICKCHARTMODEL_H

#include "Quotations.h"

#include <QAbstractTableModel>

class CandlestickChartModel : public QAbstractTableModel
{
    Q_OBJECT

    Q_PROPERTY(int hourFrom READ hourFrom WRITE setHourFrom NOTIFY hourFromChanged)
    Q_PROPERTY(int minuteFrom READ minuteFrom WRITE setMinuteFrom NOTIFY minuteFromChanged)
    Q_PROPERTY(int intervalLength READ intervalLength WRITE setIntervalLength NOTIFY intervalLengthChanged)

    Q_PROPERTY(double minValue READ minValue WRITE setMinValue NOTIFY minValueChanged)
    Q_PROPERTY(double maxValue READ maxValue WRITE setMaxValue NOTIFY maxValueChanged)

    Q_PROPERTY(QDateTime seriesFrom READ seriesFrom WRITE setSeriesFrom NOTIFY seriesFromChanged)
    Q_PROPERTY(QDateTime seriesTo READ seriesTo WRITE setSeriesTo NOTIFY seriesToChanged)

    Q_PROPERTY(QString seriesName READ seriesName WRITE setSeriesName NOTIFY seriesNameChanged)

    Q_PROPERTY(int seriesSize READ seriesSize WRITE setSeriesSize NOTIFY seriesSizeChanged)

public:
    explicit CandlestickChartModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

    QDateTime seriesFrom() const;
    QDateTime seriesTo() const;

    QString seriesName() const;

    int seriesSize() const;

    int hourFrom() const;
    int minuteFrom() const;
    int intervalLength() const;

    double minValue() const;
    double maxValue() const;

signals:
    void seriesFromChanged(QDateTime seriesFrom);
    void seriesToChanged(QDateTime seriesTo);

    void seriesNameChanged(QString seriesName);

    void seriesSizeChanged(int seriesSize);

    void hourFromChanged(int hourFrom);
    void minuteFromChanged(int minuteFrom);
    void intervalLengthChanged(int intervalLength);

    void minValueChanged(double minValue);
    void maxValueChanged(double maxValue);

public slots:
    void updateData();

    void setSeriesFrom(QDateTime seriesFrom);
    void setSeriesTo(QDateTime seriesTo);

    void setSeriesName(QString seriesName);

    void setSeriesSize(int seriesSize);

    void setHourFrom(int hourFrom);
    void setMinuteFrom(int minuteFrom);
    void setIntervalLength(int intervalLength);

    void setMinValue(double minValue);
    void setMaxValue(double maxValue);

private:
    QList<Quotation> m_quotations;

    QDateTime m_seriesFrom;
    QDateTime m_seriesTo;

    QString m_seriesName;

    int m_seriesSize;

    int m_hourFrom;
    int m_minuteFrom;
    int m_intervalLength;

    double m_minValue;
    double m_maxValue;
};



#endif // CANDLESTICKCHARTMODEL_H
