#ifndef FILEDOWNLOADER_H
#define FILEDOWNLOADER_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>

class FileDownloader : public QObject
{
    Q_OBJECT
public:
    explicit FileDownloader(QObject *parent = nullptr);

    void downloadCat(QString path, QString action, bool isFolder, QDateTime timestamp);

private:
    QNetworkAccessManager mManager;
    int mCatCounter = 1;

    void replyFinished(QNetworkReply* reply);
};

#endif // FILEDOWNLOADER_H
