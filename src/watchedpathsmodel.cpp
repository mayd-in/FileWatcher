#include "watchedpathsmodel.h"

WatchedPathsModel::WatchedPathsModel(QObject *parent)
    : QAbstractTableModel{parent}
{
    mPaths;
}

void WatchedPathsModel::addPath(QString path)
{
    beginInsertRows(QModelIndex(), mPaths.size(), mPaths.size());
    mPaths << path;
    endInsertRows();
}

void WatchedPathsModel::removePath(QString path)
{
    auto index = mPaths.indexOf(path);
    if (index < 0) {
        return;
    }

    beginRemoveRows(QModelIndex(), index, index);
    mPaths.removeAt(index);
    endRemoveRows();
}

void WatchedPathsModel::removePath(int index)
{
    if (index < 0 || index >= mPaths.size()) {
        return;
    }

    beginRemoveRows(QModelIndex(), index, index);
    mPaths.removeAt(index);
    endRemoveRows();
}

int WatchedPathsModel::rowCount(const QModelIndex&) const
{
    return mPaths.size();
}

int WatchedPathsModel::columnCount(const QModelIndex&) const
{
    return 2;
}

QVariant WatchedPathsModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();

    auto path = mPaths.at(index.row());
    switch (index.column()) {
        case 0: return path;
    }

    return QVariant();
}

QVariant WatchedPathsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
            case 0: return tr("Path");
            case 1: return tr("Action");
        }
        return "";
    }

    return QAbstractTableModel::headerData(section, orientation, role);
}
