#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "filesystemwatcher.h"
#include "filedownloader.h"

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    FileSystemWatcher mFileSystemWatcher;
    FileDownloader mFileDownloader;
};
#endif // MAINWINDOW_H
