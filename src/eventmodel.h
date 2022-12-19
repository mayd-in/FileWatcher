#ifndef EVENTMODEL_H
#define EVENTMODEL_H

#include <QAbstractTableModel>
#include <QDateTime>

struct Event {
    QString type;
    QString path;
    bool isFolder;
    QDateTime timestamp;
};

class EventModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit EventModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

private:
    QList<Event> mEvents;
};

#endif // EVENTMODEL_H
