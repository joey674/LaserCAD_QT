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

void getCircleFromBulge(const QPointF& p1, const QPointF& p2, const double & bulge, QPointF& center,double & radius);
void getCircleFromThreePoints(const QPointF& p1, const QPointF& p2, const QPointF& p3, QPointF& center, double & radius);
void getBulgeFromThreePoints(const QPointF& p1, const QPointF& p2, const QPointF& p3,const QPointF& center,const double & radius, double  &bulge);
QPainterPath createArcPath(const QPointF& p1, const QPointF& p3, const double & bulge);
#endif // PROTOCOL_H
