#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QTreeView>
#include <QItemSelection>
#include <QItemSelectionModel>
#include <QTimer>
#include "logger.h"

class TreeView : public QTreeView {
    Q_OBJECT
public:
    explicit TreeView(QWidget *parent = nullptr) : QTreeView(parent) {}
    void bindModel() {
        auto model = this->model();
        if (model == nullptr) {
            FATAL_MSG("set model before bind");
        }
    }
    void expandToIndex(const QModelIndex& index) {
        QModelIndex parent = index.parent();
        while (parent.isValid()) {
            this->expand(parent);
            parent = parent.parent();
        }
        this->scrollTo(index, QAbstractItemView::PositionAtCenter);
    }

protected:
    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) override;
    void dropEvent(QDropEvent *event) override;
    void keyPressEvent(QKeyEvent * event) override;
    void keyReleaseEvent(QKeyEvent * event) override;
};


#endif // TREEVIEW_H
