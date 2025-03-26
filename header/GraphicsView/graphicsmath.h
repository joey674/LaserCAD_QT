#ifndef MATH_H
#define MATH_H

#include <QPainter>

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

#endif // MATH_H
