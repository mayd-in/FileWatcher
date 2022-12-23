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

    void addPath(const QString& dir);
    void removePath(const QString& dir);
    void clear();

signals:
    void pathAdded(QString dir);
    void pathRemoved(QString dir);

    void eventOccurred(QString path, QString action, bool isFolder, QDateTime timestamp);

private:
    QFileSystemWatcher mFileSystemWatcher;
    QSet<QString> mDirs;

    void onDirectoryChanged(const QString& path);
    void onFileChanged(const QString& path);
};

#endif // FILESYSTEMWATCHER_H
