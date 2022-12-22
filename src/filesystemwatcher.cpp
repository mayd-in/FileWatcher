#include "filesystemwatcher.h"

#include <QFileInfo>
#include <QDirIterator>

FileSystemWatcher::FileSystemWatcher(QObject* parent) : QObject(parent)
{
    connect(&mFileSystemWatcher, &QFileSystemWatcher::directoryChanged, this, &FileSystemWatcher::onDirectoryChanged);
    connect(&mFileSystemWatcher, &QFileSystemWatcher::fileChanged, this, &FileSystemWatcher::onFileChanged);
}

void FileSystemWatcher::addPath(const QString& path)
{
    QFileInfo fileInfo(path);
    if (!fileInfo.exists() || !fileInfo.isDir()) {
        qWarning() << "This is not an existent directory:" << fileInfo;
        return;
    }

    mFileSystemWatcher.addPath(path);

    QDirIterator it(path, QDir::Dirs | QDir::Files | QDir::NoDot | QDir::NoDotDot, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        auto entry = it.next();
        mFileSystemWatcher.addPath(entry);
    }

    mPaths.insert(path);
    emit pathAdded(path);
}

void FileSystemWatcher::removePath(const QString& path)
{
    if (!mPaths.contains(path)) {
        return;
    }

    mFileSystemWatcher.removePath(path);
    mPaths.remove(path);
    emit pathRemoved(path);
}

void FileSystemWatcher::onDirectoryChanged(const QString& path)
{
    QFileInfo dir(path);
    if (dir.exists()) {
        auto dirs = mFileSystemWatcher.directories();
        auto files = mFileSystemWatcher.files();
        QDirIterator it(path, QDir::Dirs | QDir::Files | QDir::NoDot | QDir::NoDotDot, QDirIterator::NoIteratorFlags);
        while (it.hasNext()) {
            auto entry = it.next();
            if (dirs.contains(entry)) {
                continue;
            }
            if (files.contains(entry)) {
                continue;
            }

            auto fileInfo = it.fileInfo();
            mFileSystemWatcher.addPath(entry);
            emit eventOccurred(entry, "Create", fileInfo.isDir(), QDateTime::currentDateTime());
        }
    }
    else {
        removePath(path);
        emit eventOccurred(path, "Remove", true, QDateTime::currentDateTime());
    }
}

void FileSystemWatcher::onFileChanged(const QString& path)
{
    QString action;

    QFileInfo file(path);
    if (file.exists()) {
        action = "Edit";
    }
    else {
        action = "Remove";
    }

    emit eventOccurred(path, action, false, QDateTime::currentDateTime());
}
