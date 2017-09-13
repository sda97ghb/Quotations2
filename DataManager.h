#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QNetworkAccessManager>

#include "Quotations.h"

class DataManager : public QObject
{
    Q_OBJECT
public:
    DataManager();
    DataManager(const DataManager& other);

    void loadData();

    Quotations quotations() const;

private slots:
    void processReply(QNetworkReply* reply);

private:
    void doSomethingWith();

    Quotations m_quotations;

    QNetworkAccessManager m_networkAccessManager;
};

Q_DECLARE_METATYPE(DataManager)

#endif // DATAMANAGER_H
