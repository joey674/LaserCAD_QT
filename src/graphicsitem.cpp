#include "graphicsitem.h"
#include "logger.h"
#include "utils.hpp"
#include "manager.h"

GraphicsItem::GraphicsItem()
{
    this->m_uuid = GenerateUUID();

    this->setFlag(QGraphicsItem::ItemSendsGeometryChanges);
}

QString GraphicsItem::getName()
{
    return "GraphicsItem";
}

const QString GraphicsItem::getUUID()
{
    return this->m_uuid;
}

const QPen GraphicsItem::getPen()
{
    return this->m_pen;
}

QVariant GraphicsItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    // 物体位置变换后的操作
    if (change == QGraphicsItem::ItemPositionHasChanged) {
        Manager::getIns().propertyMapFind(this->getUUID(),PropertyIndex::Position) = this->getCenterPos();
        // DEBUG_MSG(Manager::getIns().propertyMapFind(this->getUUID(),PropertyIndex::Position).toPointF());
    }

    // 物体选中后的操作
    if (change == QGraphicsItem::ItemSelectedHasChanged) {
        bool selected = value.toBool();
        if (selected)
            Manager::getIns().setItemRenderPen(this->getUUID(), EDIT_PEN);
        else
            Manager::getIns().setItemRenderPen(this->getUUID(),DISPLAY_PEN);
    }

    return QGraphicsItem::itemChange(change, value);
}





