#include "eventmodel.h"

EventModel::EventModel(QObject *parent)
    : QAbstractTableModel{parent}
{
}

void EventModel::addEvent(QString path, QString action, bool isFolder, QDateTime timestamp)
{
    Event event = {
        action,
        path,
        isFolder,
        timestamp
    };

    beginInsertRows(QModelIndex(), mEvents.size(), mEvents.size());
    mEvents << event;
    endInsertRows();
}

int EventModel::rowCount(const QModelIndex&) const
{
    return mEvents.size();
}

int EventModel::columnCount(const QModelIndex&) const
{
    return 4;
}

QVariant EventModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();

    auto event = mEvents.at(index.row());
    switch (index.column()) {
        case 0: return event.action;
        case 1: return event.path;
        case 2: return (event.isFolder ? tr("Yes") : tr("No"));
        case 3: return event.timestamp.toString("yyyy.MM.dd hh:mm:ss");
    }

    return QVariant();
}

QVariant EventModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
            case 0: return tr("Action");
            case 1: return tr("Path");
            case 2: return tr("Folder");
            case 3: return tr("Timestamp");
        }
        return "";
    }

    return QAbstractTableModel::headerData(section, orientation, role);
}
