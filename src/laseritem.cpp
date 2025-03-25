#include "laseritem.h"
#include "logger.h"
#include "utils.hpp"


LaserItem::LaserItem()
{
    this->uuid = GenerateUUID();
}

void LaserItem::addVertex(const QPointF &point, const double &angle)
{
    WARN_MSG("need to be realized");
}

void LaserItem::editVertex(const int &index, const QPointF &point, const double &angle)
{
    WARN_MSG("need to be realized");
}

void LaserItem::deleteVetex(const int &index)
{
    WARN_MSG("need to be realized");
}

void LaserItem::updateParallelOffset()
{
        WARN_MSG("need to be realized");
}

void LaserItem::updateItemList()
{
        WARN_MSG("need to be realized");
}

void LaserItem::animate()
{
    prepareGeometryChange();
    update();
}

double LaserItem::getParallelOffset()
{
    WARN_MSG("need to be realized");
}

double LaserItem::getParallelOffsetNum()
{
    WARN_MSG("need to be realized");
}

Vertex LaserItem::getVertex(const int &index)
{
    WARN_MSG("need to be realized");
}

QPointF LaserItem::getVertexPos(const int &index)
{
    WARN_MSG("need to be realized");
}

QPointF LaserItem::getCenterPos()
{
    WARN_MSG("need to be realized");
}

QString LaserItem::getName()
{
    return "LaserItem";
}

const QString& LaserItem::getUUID()
{
    return this->uuid;
}


