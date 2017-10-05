#ifndef MONTHSTATISTICS_H
#define MONTHSTATISTICS_H

#include "Data/DataLoader.h"
#include "Data/LoadableDeals.h"

/// @brief Load information about all deals in given period.
///
/// @details This class is useful because some servers (such as finam)
/// don't permit to load data in interval longer than one day.
///
/// @note Objects of this class is disposable. If you need to load information
/// for other period you should create new instance.
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

    /// @arg ticker "SBER" and "GAZP" is only supported.
    LongPeriodDealsLoader(QString ticker, QDate from, QDate to);

    /// @return List of loadable deals. One loadable deals for each day in the interval.
    /// @warning Probably you don't need this method. Use allDeals() instead.
    QList<LoadableDeals*> loadableDealsList() const;

    /// @return All loaded deals in interval. If there are no deals loaded
    /// returns empty deals object.
    Deals allDeals() const;

signals:
    /// Emitted when information about deals is loaded for each day in the interval.
    void allDaysLoaded();

private slots:
    void onDealsUpdated();

private:
    int m_daysLoaded;
    QList<LoadableDeals*> m_loadableDealsList;
};

#endif // MONTHSTATISTICS_H
