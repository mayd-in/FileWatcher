#include "filesystemwatcher.h"

#include <QFileInfo>
#include <QDirIterator>

FileSystemWatcher::FileSystemWatcher(QObject* parent) : QObject(parent)
{
    connect(&mFileSystemWatcher, &QFileSystemWatcher::directoryChanged, this, &FileSystemWatcher::onDirectoryChanged);
    connect(&mFileSystemWatcher, &QFileSystemWatcher::fileChanged, this, &FileSystemWatcher::onFileChanged);
}

void FileSystemWatcher::addPath(const QString& dir)
{
    QFileInfo fileInfo(dir);
    if (!fileInfo.exists() || !fileInfo.isDir()) {
        qWarning() << "This is not an existent directory:" << fileInfo;
        return;
    }

    if (mDirs.contains(dir)) {
        return;
    }

    mFileSystemWatcher.addPath(dir);

    QDirIterator it(dir, QDir::Dirs | QDir::Files | QDir::NoDot | QDir::NoDotDot, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        auto entry = it.next();
        mFileSystemWatcher.addPath(entry);
    }

    mDirs.insert(dir);
    emit pathAdded(dir);
}

void FileSystemWatcher::removePath(const QString& dir)
{
    if (!mDirs.contains(dir)) {
        return;
    }

    mDirs.remove(dir);

    for (auto&& path : mFileSystemWatcher.directories()) {
        bool found = false;
        for (auto&& anotherDir : std::as_const(mDirs)) {
            if (path.startsWith(anotherDir)) {
                found = true;
                break;
            }

        }

        if (!found) {
            mFileSystemWatcher.removePath(path);
        }
    }

    for (auto&& path : mFileSystemWatcher.files()) {
        bool found = false;
        for (auto&& anotherDir : std::as_const(mDirs)) {
            if (path.startsWith(anotherDir)) {
                found = true;
                break;
            }

        }

        if (!found) {
            mFileSystemWatcher.removePath(path);
        }
    }

    emit pathRemoved(dir);
}

void FileSystemWatcher::clear()
{
    mFileSystemWatcher.removePaths(mFileSystemWatcher.directories());
    mFileSystemWatcher.removePaths(mFileSystemWatcher.files());

    for (auto&& dir : mDirs) {
        mDirs.remove(dir);
        emit pathRemoved(dir);
    }
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
