#ifndef CANDLESTICKCHARTMODEL_H
#define CANDLESTICKCHARTMODEL_H

#include "Data/LoadableQuotations.h"

#include <QAbstractTableModel>

class CandlestickChartModel : public QAbstractTableModel
{
    Q_OBJECT

    Q_PROPERTY(QString ticker READ ticker WRITE setTicker NOTIFY tickerChanged)
    Q_PROPERTY(QDate date READ date WRITE setDate NOTIFY dateChanged)

    Q_PROPERTY(int hourFrom READ hourFrom WRITE setHourFrom NOTIFY hourFromChanged)
    Q_PROPERTY(int minuteFrom READ minuteFrom WRITE setMinuteFrom NOTIFY minuteFromChanged)
    Q_PROPERTY(int intervalLength READ intervalLength WRITE setIntervalLength NOTIFY intervalLengthChanged)

    Q_PROPERTY(double minValue READ minValue NOTIFY minValueChanged)
    Q_PROPERTY(double maxValue READ maxValue NOTIFY maxValueChanged)

    Q_PROPERTY(QDateTime seriesFrom READ seriesFrom NOTIFY seriesFromChanged)
    Q_PROPERTY(QDateTime seriesTo READ seriesTo NOTIFY seriesToChanged)

    Q_PROPERTY(QString seriesName READ seriesName NOTIFY seriesNameChanged)

    // Number of displayed values
    Q_PROPERTY(int seriesSize READ seriesSize NOTIFY seriesSizeChanged)

public:
    explicit CandlestickChartModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

    QString ticker() const;
    QDate date() const;

    int hourFrom() const;
    int minuteFrom() const;
    int intervalLength() const;

    double minValue() const;
    double maxValue() const;

    QDateTime seriesFrom() const;
    QDateTime seriesTo() const;

    QString seriesName() const;

    int seriesSize() const;

signals:
    void tickerChanged(QString ticker);
    void dateChanged(QDate date);

    void hourFromChanged(int hourFrom);
    void minuteFromChanged(int minuteFrom);
    void intervalLengthChanged(int intervalLength);

    void minValueChanged(double minValue);
    void maxValueChanged(double maxValue);

    void seriesFromChanged(QDateTime seriesFrom);
    void seriesToChanged(QDateTime seriesTo);

    void seriesNameChanged(QString seriesName);

    void seriesSizeChanged(int seriesSize);

public slots:
    void loadData();
    void updateDisplayedData();
    void resetData();

    void setTicker(QString ticker);
    void setDate(QDate date);

    void setHourFrom(int hourFrom);
    void setMinuteFrom(int minuteFrom);
    void setIntervalLength(int intervalLength);

private:
    void setMinValue(double minValue);
    void setMaxValue(double maxValue);

    void setSeriesName(QString seriesName);

    QDateTime dateTimeFrom() const;
    QDateTime dateTimeTo() const;

    LoadableQuotations m_loadableQuotations;

    QList<Quotation> m_displayedQuotations;

    QString m_ticker;
    QDate m_date;

    int m_hourFrom;
    int m_minuteFrom;
    int m_intervalLength;

    double m_minValue;
    double m_maxValue;

    QString m_seriesName;
};

#endif // CANDLESTICKCHARTMODEL_H
