#ifndef ITEMTREEWIDGET_H
#define ITEMTREEWIDGET_H

#include <QTreeWidget>
#include <QDragMoveEvent>
#include <QDropEvent>

class ItemTreeWidget : public QTreeWidget
{
    Q_OBJECT

public:
    explicit ItemTreeWidget(QWidget *parent = nullptr){};

    bool isLayerNode(QTreeWidgetItem *item);
protected:
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event);

};

#endif // ITEMTREEWIDGET_H
