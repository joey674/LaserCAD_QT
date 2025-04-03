#include "graphicsitem.h"
#include "logger.h"
#include "utils.hpp"
#include "manager.h"
#include "tablemodel.h"
#include "uimanager.h"

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
    TableModel* model = qobject_cast<TableModel*>(UiManager::getIns().UI()->tableView->model());

    // 物体位置变换后的操作
    if (change == QGraphicsItem::ItemPositionHasChanged) {
        Manager::getIns().propertyMapFind(this->getUUID(),PropertyIndex::Position) = this->getCenterPos();
        // DEBUG_MSG(Manager::getIns().propertyMapFind(this->getUUID(),PropertyIndex::Position).toPointF());
        model->update();
    }

    // 物体选中后的操作
    if (change == QGraphicsItem::ItemSelectedHasChanged) {
        bool selected = value.toBool();
        if (selected){
            Manager::getIns().setItemRenderPen(this->getUUID(), EDIT_PEN);

            model->clear();
            model->setCurrentEditItem(this->getUUID());
        }
        else{
            Manager::getIns().setItemRenderPen(this->getUUID(),DISPLAY_PEN);
            model->clear();
        }
    }

    return QGraphicsItem::itemChange(change, value);
}





