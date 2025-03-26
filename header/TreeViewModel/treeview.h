#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QTreeView>
#include <QItemSelection>
#include <QItemSelectionModel>
#include <QTimer>
#include "logger.h"

class TreeView : public QTreeView
{
    Q_OBJECT
public:
    explicit TreeView(QWidget *parent = nullptr) : QTreeView(parent) {}
    void bindModel() {
        auto model = this->model();
        if (model == nullptr)
            FATAL_MSG("set model before bind");
    }

protected:
    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) override;
    void dropEvent(QDropEvent *event) override;
};


#endif // TREEVIEW_H
