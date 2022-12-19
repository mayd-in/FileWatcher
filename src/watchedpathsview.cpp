#include "watchedpathsview.h"
#include "watchedpathsmodel.h"

#include <QPushButton>

void WatchedPathsView::rowsInserted(const QModelIndex&, int start, int)
{
    // Remove button
    auto removeButton = new QPushButton(tr("Remove"));
    auto path = model()->index(start, 0).data().toString();
    connect(removeButton, &QPushButton::clicked, model(), [this, path]() {
        auto watchedPathsModel = qobject_cast<WatchedPathsModel*>(model());
        watchedPathsModel->removePath(path);
    });
    setIndexWidget(model()->index(start, 1), removeButton);
}
