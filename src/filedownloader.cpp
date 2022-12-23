#include "filedownloader.h"

#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

#include <QPixmap>

FileDownloader::FileDownloader(QObject *parent)
    : QObject{parent}
{
    connect(&mManager, &QNetworkAccessManager::finished, this, &FileDownloader::replyFinished);
}

void FileDownloader::downloadCat(QString, QString action, bool, QDateTime)
{
    if (action != "Remove")
        return;

    QNetworkRequest request;
    request.setUrl(QUrl("https://cataas.com/cat/says/hello%20world!"));
    mManager.get(request);
}

void FileDownloader::replyFinished(QNetworkReply* reply)
{
    auto data = reply->readAll();
    reply->deleteLater();
    QPixmap image;
    image.loadFromData(data);
    image.save(QString("cat_%1.png").arg(mCatCounter++));
}
