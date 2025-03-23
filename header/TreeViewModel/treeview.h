#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QTreeView>
#include <QItemSelection>
#include <QItemSelectionModel>

class TreeView : public QTreeView
{
    Q_OBJECT
public:
    explicit TreeView(QWidget *parent = nullptr);

protected:
    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) override;
};


#endif // TREEVIEW_H
