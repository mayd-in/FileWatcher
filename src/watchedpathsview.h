#ifndef WATCHEDPATHSVIEW_H
#define WATCHEDPATHSVIEW_H

#include <QTableView>

class WatchedPathsView : public QTableView
{
protected slots:
    void rowsInserted(const QModelIndex& /*parent*/, int start, int /*end*/) override;
};

#endif // WATCHEDPATHSVIEW_H
