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
    TableModel* model = qobject_cast < TableModel * > (UiManager::getIns().UI()->tableView->model());
    // 物体位置变换后的操作
    if (change == QGraphicsItem::ItemPositionHasChanged) {
        // Manager::getIns().propertyMapFind(this->getUUID(), PropertyIndex::Position) = this->getCenterPos();
        // DEBUG_MSG(Manager::getIns().propertyMapFind(this->getUUID(),PropertyIndex::Position).toPointF());
        Manager::getIns().setItemPosition (this->getUUID(), this->getCenterPos());
        model->update();
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







