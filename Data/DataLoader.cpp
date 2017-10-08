#include "DataLoader.h"

#include <QTextCodec>

namespace
{
    static const int DATA_IS_TOO_SMALL_SIZE = 100;
}

DataLoader::DataLoader(QObject *parent) :
    QObject(parent),
    m_isRunned(false)
{
    connect(this, &DataLoader::loadFinished,
            this, &DataLoader::run);
}

void DataLoader::load(LoadableData& loadable)
{
    load(&loadable);
}

void DataLoader::load(LoadableData* loadable)
{
    m_queue.enqueue(loadable);
    run();
}

void DataLoader::run()
{
    if (m_queue.isEmpty() || m_isRunned)
        return;

    m_isRunned = true;

    m_data.clear();

    LoadableData* loadableData = m_queue.head();
    QString url = loadableData->url();

    if (m_cache.check(url))
    {
        qInfo() << "Load from cache" << url;
        m_data = m_cache.get(url);
        qInfo() << "All data is loaded";
        if (m_data.size() < DATA_IS_TOO_SMALL_SIZE)
            qWarning() << QTextCodec::codecForMib(2251)->toUnicode(m_data);
        m_queue.dequeue()->updateFrom(m_data);
        m_isRunned = false;
        emit loadFinished(QPrivateSignal());
        return;
    }

    qInfo() << "Make request at" << url;

    QNetworkRequest request;
    request.setUrl(QUrl(url));

    m_reply = m_networkAccessManager.get(request);

    connect(m_reply, &QNetworkReply::readyRead,
            this, &DataLoader::onReadyRead);
    connect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)),
            this, SLOT(onError(QNetworkReply::NetworkError)));
    connect(m_reply, &QNetworkReply::sslErrors,
            this, &DataLoader::onSslErrors);
    connect(m_reply, &QNetworkReply::downloadProgress,
            this, &DataLoader::onDownloadProgress);
}

void DataLoader::handleError()
{
    qCritical() << "Error happens";
    m_queue.head()->onError();
    m_queue.dequeue();
    m_isRunned = false;
    emit loadFinished(QPrivateSignal());
}

void DataLoader::onReadyRead()
{
    qInfo() << "Ready read";
    m_data.append(m_reply->readAll());
}

void DataLoader::onError(QNetworkReply::NetworkError)
{
    handleError();
}

void DataLoader::onSslErrors(QList<QSslError>)
{
    handleError();
}

void DataLoader::onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    qInfo() << QString("Downloaded %1 bytes of %2 total.").arg(bytesReceived).arg(bytesTotal);
    if (bytesReceived == bytesTotal)
    {
        qInfo() << "All data is loaded";
//        m_cache.save(m_queue.head()->url(), m_data);
        if (m_data.size() < DATA_IS_TOO_SMALL_SIZE)
            qWarning() << QTextCodec::codecForMib(2251)->toUnicode(m_data);
        m_queue.dequeue()->updateFrom(m_data);
        m_isRunned = false;
        emit loadFinished(QPrivateSignal());
    }
}
