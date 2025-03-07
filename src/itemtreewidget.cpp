#include "itemtreewidget.h"
#include "logger.h"

bool ItemTreeWidget::ItemTreeWidget::isLayerNode(QTreeWidgetItem *item)
{
    if (!item) return false;
    // DEBUG_VAR(item->text(0));
    return item->text(0).startsWith("Layer");
}

void ItemTreeWidget::ItemTreeWidget::dropEvent(QDropEvent *event)
{
    QTreeWidgetItem *targetItem = itemAt(event->pos());
    QTreeWidgetItem *draggingItem = currentItem();

    if (!targetItem || !draggingItem) {
        event->ignore();
        return;
    }

    // Layer 只能在顶层，不能成为子节点
    if (isLayerNode(draggingItem) && targetItem->parent()) {
        event->ignore();  // 取消拖拽
        return;
    }

    // 执行默认的拖放行为
    QTreeWidget::dropEvent(event);
}

void ItemTreeWidget::ItemTreeWidget::dragMoveEvent(QDragMoveEvent *event)
{
    QTreeWidgetItem *targetItem = itemAt(event->pos());  // 目标位置的节点
    QTreeWidgetItem *draggingItem = currentItem();       // 当前拖拽的节点

    DEBUG_VAR(&targetItem);
    DEBUG_VAR(&draggingItem);
    if (!targetItem || !draggingItem) {
        event->ignore();
        return;
    }

    if (isLayerNode(draggingItem)) {
        if (targetItem->parent()) {  // 目标不是顶层节点（即在其他子节点中）
            event->ignore();  // 禁止拖动
            return;
        }
    }

    // 普通节点的默认拖动逻辑
    event->accept();
}
