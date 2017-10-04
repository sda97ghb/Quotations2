#ifndef LOADABLE_QUOTATIONS_H
#define LOADABLE_QUOTATIONS_H

#include "LoadableData.h"

#include "Entities/Quotations.h"

#include <QObject>

class LoadableQuotations : public QObject, public LoadableData
{
    Q_OBJECT
    Q_INTERFACES(LoadableData)
public:
    LoadableQuotations();

    QString url() const override;
    void updateFrom(QByteArray data) override;
    void onError() override;

    QDate date() const;
    QString ticker() const;

    void setDate(const QDate& date);
    void setTicker(const QString& ticker);

    Quotations toQuotations() const;

signals:
    void updated();

private:
    QString m_ticker;
    QDate m_date;
    Quotations m_quotations;
};

#endif // LOADABLE_QUOTATIONS_H
