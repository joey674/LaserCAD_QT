#include "graphicsitem.h"
#include "editcontroller.h"

QString GraphicsItem::getName()const {
    return "GraphicsItem";
}

const QString GraphicsItem::getUUID()const {
    return this->m_uuid;
}



QVariant GraphicsItem::itemChange(GraphicsItemChange change, const QVariant &value) {
    if (change == QGraphicsItem::ItemPositionHasChanged) {
        EditController::getIns().onGraphicsItemPositionHasChanged(this->getUUID());
    }
    if (change == QGraphicsItem::ItemSelectedHasChanged) {
        bool selected = value.toBool();
        EditController::getIns().onGraphicsItemSelectedHasChanged(this->getUUID(), selected);
    }
    return QGraphicsItem::itemChange(change, value);
}

void GraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsItem::mouseReleaseEvent(event);
    EditController::getIns().onGraphicsItemMouseRelease(this->getUUID());
}

void GraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsItem::mousePressEvent(event);
    EditController::getIns().onGraphicsItemMousePress(this->getUUID ());
}

