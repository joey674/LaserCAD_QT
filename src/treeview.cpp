#include "treeview.h"
#include <QDebug>
#include "treemodel.h"
#include "logger.h"

TreeView::TreeView(QWidget *parent) : QTreeView(parent)
{
    // DEBUG_MSG("use custom treeview");
}

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
