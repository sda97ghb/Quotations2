#ifndef MONTHSTATISTICS_H
#define MONTHSTATISTICS_H

#include "Data/DataLoader.h"
#include "Data/LoadableDeals.h"

class LongPeriodDealsLoader : public QObject
{
    Q_OBJECT
public:
    class InvalidInputException : public std::logic_error
    {
    public:
        InvalidInputException(const std::string& comment = "Invalid input or dateFrom > dateTo") :
            std::logic_error(comment)
        {
            // Designed as empty
        }
    };

    LongPeriodDealsLoader(QString ticker, QDate from, QDate to);

    QList<LoadableDeals*> loadableDealsList() const;

    Deals allDeals() const;

signals:
    void allDaysLoaded();

private slots:
    void onDealsUpdated();

private:
    int m_daysLoaded;
    QList<LoadableDeals*> m_loadableDealsList;
//    DataLoader m_dataLoader;
};

#endif // MONTHSTATISTICS_H
