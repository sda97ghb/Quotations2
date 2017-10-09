#ifndef STATISTICSDTO_H
#define STATISTICSDTO_H

#include <QMetaType>
#include <QString>

struct StatisticsDTO
{
private:
    Q_GADGET

    Q_PROPERTY(QString title         MEMBER title)
    Q_PROPERTY(int numberOfDeals     MEMBER numberOfDeals)
    Q_PROPERTY(int averageVolume     MEMBER averageVolume)
    Q_PROPERTY(int minVolume         MEMBER minVolume)
    Q_PROPERTY(int maxVolume         MEMBER maxVolume)
    Q_PROPERTY(int numberOfBuyDeals  MEMBER numberOfBuyDeals)
    Q_PROPERTY(int averageBuyVolume  MEMBER averageBuyVolume)
    Q_PROPERTY(int minBuyVolume      MEMBER minBuyVolume)
    Q_PROPERTY(int maxBuyVolume      MEMBER maxBuyVolume)
    Q_PROPERTY(int numberOfSellDeals MEMBER numberOfSellDeals)
    Q_PROPERTY(int averageSellVolume MEMBER averageSellVolume)
    Q_PROPERTY(int minSellVolume     MEMBER minSellVolume)
    Q_PROPERTY(int maxSellVolume     MEMBER maxSellVolume)
public:
    QString title;
    int numberOfDeals;
    int averageVolume;
    int minVolume;
    int maxVolume;
    int numberOfBuyDeals;
    int averageBuyVolume;
    int minBuyVolume;
    int maxBuyVolume;
    int numberOfSellDeals;
    int averageSellVolume;
    int minSellVolume;
    int maxSellVolume;

    StatisticsDTO() :
        title(""),
        numberOfDeals(0),
        averageVolume(0),
        minVolume(0),
        maxVolume(0),
        numberOfBuyDeals(0),
        averageBuyVolume(0),
        minBuyVolume(0),
        maxBuyVolume(0),
        numberOfSellDeals(0),
        averageSellVolume(0),
        minSellVolume(0),
        maxSellVolume(0)
    {
        // Designed as empty
    }

    // TODO: add operator =
};

Q_DECLARE_METATYPE(StatisticsDTO)

#endif // STATISTICSDTO_H
