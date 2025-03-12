#include "itemtreewidget.h"
#include "logger.h"

bool ItemTreeWidget::ItemTreeWidget::isLayerNode(QTreeWidgetItem *item)
{
    if (!item) return false;
    return item->text(0).startsWith("Layer");
}

void ItemTreeWidget::dragMoveEvent(QDragMoveEvent *event)
{
    QTreeWidgetItem *draggingItem = currentItem();
    QTreeWidgetItem *targetPositionItem = itemAt(event->position().toPoint());

    if (!targetPositionItem || !draggingItem) {
        event->ignore();
        return;
    }

    DEBUG_VAR(draggingItem->text(0));
    DEBUG_VAR(targetPositionItem->text(0));

    QRect targetRect = visualItemRect(targetPositionItem);
    int yPos = event->position().toPoint().y();
    int topThreshold = targetRect.top() + targetRect.height() / 4;
    int bottomThreshold = targetRect.bottom() - targetRect.height() / 4;

    if (isLayerNode(draggingItem)) // layer节点不允许并入
    {
        if (yPos < topThreshold)
        {
            event->accept();
            return;
        }
        else if (yPos > bottomThreshold)
        {
            event->accept();
            return;
        }
        else
        {
            event->ignore();
            return;
        }
    }
    else // 其他类型节点
    {
        if (!isLayerNode(targetPositionItem) && targetPositionItem->parent() ==nullptr) //
        {
            if (yPos < topThreshold)
            {
                event->accept();
                return;
            }
            else if (yPos > bottomThreshold)
            {
                event->accept();
                return;
            }
            else
            {
                event->ignore();
                return;
            }
        }
        else
        {
            event->accept();
            return;
        }
    }
}

void ItemTreeWidget::dropEvent(QDropEvent *event)
{
    QTreeWidgetItem *draggingItem = currentItem();  // 被拖拽的节点
    QTreeWidgetItem *targetPositionItem = itemAt(event->position().toPoint());  // 目标位置

    // if (!draggingItem || !targetPositionItem) {
    //     event->ignore();
    //     return;
    // }

    // if (isLayerNode(draggingItem)) {
    //     event->ignore();
    //     return;
    // }

    // // 2. 如果目标节点是 layer，拒绝放入
    // if (isLayerNode(targetPositionItem)) {
    //     event->ignore();
    //     return;
    // }

    QTreeWidget::dropEvent(event);
}
