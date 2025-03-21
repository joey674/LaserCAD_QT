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
    double angle;
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

// 弧和凸度转化
void getAngleFromBulge(const double& bulge, double& angle);
void getBulgeFromAngle(const double& angle, double& bulge);
// 从点获取圆以及对应弧信息
void getCircleFromTwoPointsAndAngle(const QPointF& p1, const QPointF& p2, const double & angle, QPointF& center,double & radius);
void getCircleFromThreePoints(const QPointF& p1, const QPointF& p2, const QPointF& p3, QPointF& center, double & radius);
void getAngleFromThreePoints(const QPointF& p1, const QPointF& p2, const QPointF& p3, double  &angle);
// 从一条弧中获取一定角度的截点
void getIntersectPoint(const QPointF& p1, const QPointF& p3, const double& p1p3Angle,const double & sweepAngle, QPointF& intersectPoint);
//
QPainterPath createArcPath(const QPointF& p1, const QPointF& p3, const double & angle);
#endif // PROTOCOL_H
