#ifndef EVENTMODEL_H
#define EVENTMODEL_H

#include <QAbstractTableModel>
#include <QDateTime>

struct Event {
    QString action;
    QString path;
    bool isFolder;
    QDateTime timestamp;
};

class EventModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit EventModel(QObject *parent = nullptr);

    void addEvent(QString path, QString action, bool isFolder, QDateTime timestamp);
    void clear();

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

private:
    QList<Event> mEvents;
};

#endif // EVENTMODEL_H
