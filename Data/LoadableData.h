#ifndef LOADABLEDATA_H
#define LOADABLEDATA_H

#include <QObject>
#include <QString>

/// Data that can be loaded using DataLoader.
/// When all bytes is loaded updateFrom(data) is called.
class LoadableData
{
public:
    // All interfaces should have vrtual destructor.
    virtual ~LoadableData() = default;

    /// Url from where DataLoader load data.
    virtual QString url() const = 0;

    /// Called when all bytes loaded.
    virtual void updateFrom(QByteArray data) = 0;

    /// Called when error happens. Do nothing by default.
    virtual void onError();
};

Q_DECLARE_INTERFACE(LoadableData, "com.divanosoft.quotations.LoadableData/1.0")

#endif // LOADABLEDATA_H
