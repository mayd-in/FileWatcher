#include "eventmodel.h"

EventModel::EventModel(QObject *parent)
    : QAbstractTableModel{parent}
{
    // TODO: Remove
    Event event1 = {
        QString("Create"),
        QString("/tmp/repository"),
        true,
        QDateTime::currentDateTime()
    };

    // TODO: Remove
    Event event2 = {
        QString("Edit"),
        QString("/tmp/lock"),
        false,
        QDateTime::currentDateTime()
    };

    mEvents << event1 << event2;
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
        case 0: return event.type;
        case 1: return event.path;
        case 2: return (event.isFolder ? tr("Yes") : tr("No"));
        case 3: return event.timestamp;
    }

    return QVariant();
}

QVariant EventModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
            case 0: return tr("Type");
            case 1: return tr("Path");
            case 2: return tr("Folder");
            case 3: return tr("Timestamp");
        }
        return "";
    }

    return QAbstractTableModel::headerData(section, orientation, role);
}
