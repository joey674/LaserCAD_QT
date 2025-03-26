#include "treeview.h"
#include <QDebug>
#include "treemodel.h"
#include "logger.h"
#include "manager.h"


void TreeView::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    QModelIndexList selectedIndexes = selectionModel()->selectedIndexes();

    if (selectedIndexes.size() > 1) {
        TreeModel *model = qobject_cast<TreeModel *>(this->model());

        for (const QModelIndex &index : selectedIndexes) {
            QString type = model->nodeProperty(index, NodePropertyIndex::Type).toString();

            if (type == "Layer") {
                selectionModel()->select(index, QItemSelectionModel::Deselect);
            }
        }
    }

    QTreeView::selectionChanged(selected, deselected);
}

void TreeView::dropEvent(QDropEvent *event)
{
    QTreeView::dropEvent(event);

    // QTimer::singleShot(10, [this]() {
    //     DEBUG_MSG("after moved");
    //     Manager::getIns().setVisibleSync();
    // });

}
