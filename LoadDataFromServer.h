#ifndef LOADDATAFROMSERVER_H
#define LOADDATAFROMSERVER_H

#include <QObject>
#include <QMetaType>

class LoadDataFromServer : public QObject
{
    Q_OBJECT
public:
    LoadDataFromServer() = default;
    LoadDataFromServer(const LoadDataFromServer&);

    Q_INVOKABLE void execute();
};

Q_DECLARE_METATYPE(LoadDataFromServer)

#endif // LOADDATAFROMSERVER_H
