#ifndef DATALOADER_H
#define DATALOADER_H

#include "Cache.h"
#include "LoadableData.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>
#include <QQueue>
#include <QTimer>

class DataLoader : public QObject
{
    Q_OBJECT
public:
    explicit DataLoader(QObject* parent = nullptr);

signals:
    void loadFinished(QPrivateSignal);

public slots:
    void load(LoadableData& loadable);
    void load(LoadableData* loadable);

private slots:
    void run();

    void handleError();

    void onReadyRead();
    void onError(QNetworkReply::NetworkError);
    void onSslErrors(QList<QSslError>);
    void onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);

private:
    QQueue<LoadableData*> m_queue;

    QNetworkAccessManager m_networkAccessManager;
    QNetworkReply* m_reply;
    QByteArray m_data;

    bool m_isRunned;

    Cache m_cache;

//    QTimer m_timer;
};

#endif // DATALOADER_H
