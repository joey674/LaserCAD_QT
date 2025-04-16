#include "graphicsitem.h"
#include "manager.h"
#include "tablemodel.h"
#include "uimanager.h"



QString GraphicsItem::getName()const {
    return "GraphicsItem";
}

const QString GraphicsItem::getUUID()const {
    return this->m_uuid;
}

const QPen GraphicsItem::getPen()const {
    return this->m_pen;
}

QVariant GraphicsItem::itemChange(GraphicsItemChange change, const QVariant &value) {
    // 物体位置变换后的操作 (实时更新; 注意只有table可以实时更新, tab就不要一直更新了 不然很卡)
    if (change == QGraphicsItem::ItemPositionHasChanged) {
        EditManager::getIns().updateTableViewModel();
        Manager::getIns().setItemPosition (this->getUUID(), this->getCenterPos());
    }
    // 物体选中后的操作
    if (change == QGraphicsItem::ItemSelectedHasChanged) {
        bool selected = value.toBool();
        if (selected) {
            Manager::getIns().setItemRenderPen(this->getUUID(), EDIT_PEN);
        } else {
            Manager::getIns().setItemRenderPen(this->getUUID(), DISPLAY_PEN);
        }
    }
    return QGraphicsItem::itemChange(change, value);
}

void GraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    EditManager::getIns().updateTabWidget();
    QGraphicsItem::mouseReleaseEvent(event);
}

