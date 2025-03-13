#include "itemtreewidget.h"
#include "logger.h"
#include <QMenu>

int ItemTreeWidget::getItemLevel(QTreeWidgetItem *item)
{
    int level = 0;
    while (item->parent()) {
        item = item->parent();
        level++;
    }
    return level;
}

void ItemTreeWidget::removeParent(QTreeWidgetItem *childItem)
{
    if (!childItem) return;

    QTreeWidgetItem *oldParent = childItem->parent();
    if (oldParent)
    {
        oldParent->removeChild(childItem);
    }
    else
    {
        int index = this->indexOfTopLevelItem(childItem);
        if (index != -1)
        {
            this->takeTopLevelItem(index);
        }
    }
}

void ItemTreeWidget::onShowContextMenu(const QPoint &pos)
{
    QTreeWidgetItem *selectedItem = itemAt(pos);  // 获取右键点击的节点
    if (!selectedItem) return;

    QMenu menu(this);

    // 添加菜单项
    QAction *addGroupAction = new QAction("添加 Group", this);
    QAction *addItemAction = new QAction("添加 Item", this);
    QAction *renameAction = new QAction("重命名", this);
    QAction *deleteAction = new QAction("删除", this);

    connect(addGroupAction, &QAction::triggered, this, [this, selectedItem]() {
        // QTreeWidgetItem *newGroup = new QTreeWidgetItem(selectedItem, QStringList("New Group"));
        // selectedItem->addChild(newGroup);
        // expandItem(selectedItem);  // 展开父节点
    });

    connect(addItemAction, &QAction::triggered, this, [this, selectedItem]() {
        // QTreeWidgetItem *newItem = new QTreeWidgetItem(selectedItem, QStringList("New Item"));
        // selectedItem->addChild(newItem);
        // expandItem(selectedItem);
    });

    connect(renameAction, &QAction::triggered, this, [this, selectedItem]() {
        // editItem(selectedItem, 0);  // 启动编辑模式
    });

    connect(deleteAction, &QAction::triggered, this, [this, selectedItem]() {
        // delete selectedItem;  // 删除节点
    });

        menu.addAction(addGroupAction);  // 允许 Layer 添加 Group
        menu.addAction(addItemAction);  // 允许 Group 添加 Item
        menu.addAction(deleteAction);   // Group 允许删除
        menu.addAction(deleteAction);   // 仅允许删除 Item
        menu.addAction(renameAction);  // 所有节点都能重命名

    // **在鼠标位置弹出菜单**
    menu.exec(mapToGlobal(pos));
}

void ItemTreeWidget::onItemClicked(QTreeWidgetItem *item, int)
{
    DEBUG_VAR(item->text(0));
}

void ItemTreeWidget::dragMoveEvent(QDragMoveEvent *event)
{
    QTreeWidgetItem *draggingItem = currentItem();
    QTreeWidgetItem *targetPositionItem = itemAt(event->position().toPoint());
    if (!targetPositionItem || !draggingItem)
    {
        dropIndicatorRect = QRect();
        viewport()->update();
        event->ignore();
        return;
    }

    DEBUG_VAR(draggingItem->text(0));
    DEBUG_VAR(targetPositionItem->text(0));
    QRect targetRect = visualItemRect(targetPositionItem);
    auto dropEvent = getDropEventType(event);

    switch(dropEvent)
    {
    case DropEventType::OnItem:{
        dropIndicatorRect = QRect(targetRect.left(), targetRect.top(), targetRect.width(), targetRect.height());
        if (targetPositionItem == draggingItem)
            dropIndicatorRect = QRect();
        break;
    };
    case DropEventType::AboveItem:{
        dropIndicatorRect = QRect(targetRect.left(), targetRect.top(), targetRect.width(), 0);
        break;
    };
    case DropEventType::BelowItem:{
        dropIndicatorRect = QRect(targetRect.left(), targetRect.bottom(), targetRect.width(), 0);
        break;
    };
};

    viewport()->update();
    event->accept();
}

void ItemTreeWidget::dropEvent(QDropEvent *event)
{
    QTreeWidgetItem *dragItem = currentItem();
    QTreeWidgetItem *targetPositionItem = itemAt(event->position().toPoint());
    if (!targetPositionItem || !dragItem|| dragItem == targetPositionItem)
    {
        event->ignore();
        return;
    }

    auto dropEvent = getDropEventType(event);
    removeParent(dragItem);
    if (dropEvent == DropEventType::OnItem)
    {
        DEBUG_MSG("OnItem");
        targetPositionItem->addChild(dragItem);
    }
    else
    {
        QTreeWidgetItem *parentItem = targetPositionItem->parent();
        int targetIndex = (parentItem) ? parentItem->indexOfChild(targetPositionItem) : indexOfTopLevelItem(targetPositionItem);

        if (dropEvent == DropEventType::AboveItem)
        {
            DEBUG_MSG("AboveItem");
            if (parentItem)
                parentItem->insertChild(targetIndex, dragItem);
            else
                insertTopLevelItem(targetIndex, dragItem);
        }
        else if (dropEvent == DropEventType::BelowItem)
        {
            DEBUG_MSG("BelowItem");
            if (parentItem)
                parentItem->insertChild(targetIndex + 1, dragItem);
            else
                insertTopLevelItem(targetIndex + 1, dragItem);
        }
    }

    dropIndicatorRect = QRect();
    this->viewport()->update();
    event->accept();
}

void ItemTreeWidget::paintEvent(QPaintEvent *event)
{
    QTreeWidget::paintEvent(event);

    if (!dropIndicatorRect.isNull()) {
        QPainter painter(viewport());
        QPen pen(Qt::black, 2, Qt::SolidLine);
        painter.setPen(pen);

        if (dropIndicatorRect.height() == 0) {
            painter.drawLine(dropIndicatorRect.topLeft(), dropIndicatorRect.topRight());
        } else {
            painter.drawRect(dropIndicatorRect);
        }
    }
}

void ItemTreeWidget::dragLeaveEvent(QDragLeaveEvent *event) {
    dropIndicatorRect = QRect();
    viewport()->update();
    QTreeWidget::dragLeaveEvent(event);
}

ItemTreeWidget::DropEventType ItemTreeWidget:: getDropEventType(QDropEvent  *event)
{
    QTreeWidgetItem *draggingItem = currentItem();
    QTreeWidgetItem *targetPositionItem = itemAt(event->position().toPoint());
    if (!targetPositionItem || !draggingItem)
    {
        FATAL_MSG("empty drag item");
    }

    auto dropType = DropEventType::OnItem;
    QRect targetRect = visualItemRect(targetPositionItem);  // 获取目标项的矩形区域
    int yPos = event->position().toPoint().y();     // 获取鼠标的 y 坐标
    int topThreshold = targetRect.top() + targetRect.height() / 4;  // 顶部 25% 区域
    int bottomThreshold = targetRect.bottom() - targetRect.height() / 4;  // 底部 25% 区域

    if (yPos < topThreshold) {
        dropType = DropEventType::AboveItem;
    } else if (yPos > bottomThreshold) {
        dropType = DropEventType::BelowItem;
    } else {
        dropType = DropEventType::OnItem;
    }

    return dropType;
}
