#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "filesystemwatcher.h"

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    FileSystemWatcher mFileSystemWatcher;
};
#endif // MAINWINDOW_H
