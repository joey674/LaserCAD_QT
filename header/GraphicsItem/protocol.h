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
    float bulge;
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

void getCircleFromBulge(const QPointF& p1, const QPointF& p2, const float & bulge, QPointF& center,float & radius);
void getCircleFromThreePoints(const QPointF& p1, const QPointF& p2, const QPointF& p3, QPointF& center, float & radius);
void getBulgeFromThreePoints(const QPointF& p1, const QPointF& p2, const QPointF& p3,const QPointF& center,const float & radius, float  &bulge);
QPainterPath createArcPath(const QPointF& p1, const QPointF& p3, const float & bulge);
#endif // PROTOCOL_H
