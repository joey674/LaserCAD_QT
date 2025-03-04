#include "laseritem.h"
#include "logger.h"



LaserItem::LaserItem()
{
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

void LaserItem::createParallelOffset(const double &offset, const double &offsetNum)
{
    WARN_MSG("need to be realized");
}

void LaserItem::rotate(const double &angle)
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

