#ifndef WATCHEDPATHSMODEL_H
#define WATCHEDPATHSMODEL_H

#include <QAbstractTableModel>
#include <QObject>
#include <QFileSystemWatcher>

class FileSystemWatcher;

class WatchedPathsModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit WatchedPathsModel(QObject *parent = nullptr);

    void addPath(QString path);
    void removePath(QString path);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

private:
    QList<QString> mPaths;
};

#endif // WATCHEDPATHSMODEL_H
