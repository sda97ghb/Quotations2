#ifndef LOADABLEDATA_H
#define LOADABLEDATA_H

#include <QObject>
#include <QString>

class LoadableData
{
public:
    virtual ~LoadableData() = default;

    virtual QString url() const = 0;

    virtual void updateFrom(QByteArray data) = 0;

    virtual void onError();
};

Q_DECLARE_INTERFACE(LoadableData, "com.divanosoft.quotations.LoadableData/1.0")

#endif // LOADABLEDATA_H
