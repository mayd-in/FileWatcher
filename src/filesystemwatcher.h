#ifndef FILESYSTEMWATCHER_H
#define FILESYSTEMWATCHER_H

#include <QObject>
#include <QFileSystemWatcher>
#include <QHash>
#include <QSet>

class FileSystemWatcher : public QObject
{
    Q_OBJECT

public:
    FileSystemWatcher(QObject *parent = nullptr);

    void addPath(const QString& path);
    void removePath(const QString& path);

signals:
    void pathAdded(QString path);
    void pathRemoved(QString path);

    void eventOccurred(QString path, QString action, bool isFolder, QDateTime timestamp);

private:
    QFileSystemWatcher mFileSystemWatcher;
    QSet<QString> mPaths;
    QHash<QString, int> mNonExistentPaths;

    void onDirectoryChanged(const QString& path);
    void onFileChanged(const QString& path);
};

#endif // FILESYSTEMWATCHER_H
