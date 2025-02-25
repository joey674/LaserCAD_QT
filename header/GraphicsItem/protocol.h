#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <qgraphicsitem.h>
#include <qgraphicsscene.h>
#include <QPainter>
#include <QDebug.h>
#include <QStyleOptionGraphicsItem>

struct Vertex
{
    QPointF point;
    double bulge;
};

enum LineType
{
    OriginItem,
    offsetItem,
};

enum ItemTypeId /* 只用于对照 不参与实际使用 */
{
    Polyline = 6270,
    Arc = 6271,
};

extern  QPen defaultLinePen;

#endif // PROTOCOL_H
