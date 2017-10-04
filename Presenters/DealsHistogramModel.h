#ifndef DEALSHISTOGRAMMODEL_H
#define DEALSHISTOGRAMMODEL_H

#include "Data/LoadableDeals.h"

#include <QAbstractTableModel>

class DealsHistogramModel : public QAbstractTableModel
{
    Q_OBJECT

    Q_PROPERTY(int numberOfIntervals
               READ numberOfIntervals
               WRITE setNumberOfIntervals
               NOTIFY numberOfIntervalsChanged)
    Q_PROPERTY(quint64 volumeFrom READ volumeFrom WRITE setVolumeFrom NOTIFY volumeFromChanged)
    Q_PROPERTY(quint64 volumeTo READ volumeTo WRITE setVolumeTo NOTIFY volumeToChanged)
    Q_PROPERTY(quint64 maxValue READ maxValue NOTIFY maxValueChanged)
    Q_PROPERTY(quint64 minVolume READ minVolume WRITE setMinVolume NOTIFY minVolumeChanged)
    Q_PROPERTY(quint64 maxVolume READ maxVolume WRITE setMaxVolume NOTIFY maxVolumeChanged)
    Q_PROPERTY(quint64 buyMinVolume READ buyMinVolume NOTIFY buyMinVolumeChanged)
    Q_PROPERTY(quint64 sellMinVolume READ sellMinVolume NOTIFY sellMinVolumeChanged)
    Q_PROPERTY(quint64 buyMaxVolume READ buyMaxVolume NOTIFY buyMaxVolumeChanged)
    Q_PROPERTY(quint64 sellMaxVolume READ sellMaxVolume NOTIFY sellMaxVolumeChanged)
    Q_PROPERTY(quint64 buyAverageVolume READ buyAverageVolume NOTIFY buyAverageVolumeChanged)
    Q_PROPERTY(quint64 sellAverageVolume READ sellAverageVolume NOTIFY sellAverageVolumeChanged)
public:
    DealsHistogramModel();

    int rowCount(const QModelIndex& parent) const override;
    int columnCount(const QModelIndex& parent) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex& index, int role) const override;

    int numberOfIntervals() const;

    quint64 volumeFrom() const;
    quint64 volumeTo() const;

    quint64 maxValue() const;

    quint64 buyMinVolume() const;
    quint64 sellMinVolume() const;
    quint64 buyMaxVolume() const;
    quint64 sellMaxVolume() const;
    quint64 buyAverageVolume() const;
    quint64 sellAverageVolume() const;

    quint64 minVolume() const;
    quint64 maxVolume() const;

public slots:
    void reload();
    void updateData();

    void setNumberOfIntervals(int numberOfIntervals);

    void setVolumeFrom(quint64 volumeFrom);
    void setVolumeTo(quint64 volumeTo);

signals:
    void numberOfIntervalsChanged(int numberOfIntervals);

    void maxValueChanged(quint64 maxValue);

    void buyMinVolumeChanged(quint64 buyMinVolume);
    void sellMinVolumeChanged(quint64 sellMinVolume);
    void buyMaxVolumeChanged(quint64 buyMaxVolume);
    void sellMaxVolumeChanged(quint64 sellMaxVolume);
    void buyAverageVolumeChanged(quint64 buyAverageVolume);
    void sellAverageVolumeChanged(quint64 sellAverageVolume);

    void volumeFromChanged(quint64 volumeFrom);
    void volumeToChanged(quint64 volumeTo);

    void minVolumeChanged(quint64 minVolume);
    void maxVolumeChanged(quint64 maxVolume);

private:
    void setBuyMinVolume(quint64 buyMinVolume);
    void setSellMinVolume(quint64 sellMinVolume);
    void setBuyMaxVolume(quint64 buyMaxVolume);
    void setSellMaxVolume(quint64 sellMaxVolume);
    void setBuyAverageVolume(quint64 buyAverageVolume);
    void setSellAverageVolume(quint64 sellAverageVolume);
    void setMinVolume(quint64 minVolume);
    void setMaxVolume(quint64 maxVolume);

    LoadableDeals m_loadableDeals;
    QList<quint64> m_histogramSeriesData;
    QList<quint64> m_buyHistogramSeriesData;
    QList<quint64> m_sellHistogramSeriesData;
    int m_numberOfIntervals;
    quint64 m_volumeFrom;
    quint64 m_volumeTo;
    quint64 m_buyMinVolume;
    quint64 m_sellMinVolume;
    quint64 m_buyMaxVolume;
    quint64 m_sellMaxVolume;
    quint64 m_buyAverageVolume;
    quint64 m_sellAverageVolume;
    quint64 m_minVolume;
    quint64 m_maxVolume;
};

//Q_DECLARE_METATYPE(DealsHistogramModel)

#endif // DEALSHISTOGRAMMODEL_H
