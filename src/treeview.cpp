#include "treeview.h"
#include <QDebug>
#include "treemodel.h"
#include "keyboardmanager.h"


void TreeView::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) {
    QModelIndexList selectedIndexes = selectionModel()->selectedIndexes();
    if (selectedIndexes.size() > 1) {
        TreeModel *model = qobject_cast < TreeModel * > (this->model());
        for (const QModelIndex &index : selectedIndexes) {
            QString type = model->nodeProperty(index, TreeNodePropertyIndex::Type).toString();
            if (type == "Layer") { // layer不可选中
                selectionModel()->select(index, QItemSelectionModel::Deselect);
            }
        }
    }
    QTreeView::selectionChanged(selected, deselected);
}

void TreeView::dropEvent(QDropEvent *event) {
    QTreeView::dropEvent(event);
    QTimer::singleShot(10, [this]() {
        DEBUG_MSG("after moved");
        ItemManager::getIns().setLayerItemStateSync();
    });
}

void TreeView::keyPressEvent(QKeyEvent *event) {
    KeyboardManager::getIns().onTreeViewKeyPressEvent(event);
}

void TreeView::keyReleaseEvent(QKeyEvent *event) {
    KeyboardManager::getIns().onTreeViewKeyReleaseEvent(event);
}
