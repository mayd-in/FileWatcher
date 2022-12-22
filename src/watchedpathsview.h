#ifndef WATCHEDPATHSVIEW_H
#define WATCHEDPATHSVIEW_H

#include <QTableView>
#include <QString>

class WatchedPathsView : public QTableView
{
    Q_OBJECT

signals:
    void removeRequested(QString path);

protected slots:
    void rowsInserted(const QModelIndex& /*parent*/, int start, int /*end*/) override;
};

#endif // WATCHEDPATHSVIEW_H
