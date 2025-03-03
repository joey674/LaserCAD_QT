#include "protocol.h"

QPen defaultLinePen = QPen(Qt::black, 1);

QPainterPath createArcPath(const QPointF& p1, const QPointF& p2,const double & bulge)
{
    QPointF center = QPointF{};
    double  radius = 0;
    getCircleFromBulge(p1,p2,bulge,center,radius);
    // qDebug() << "createArcPath" << p1<< p2 << bulge << center << radius;

    QLineF line0(center , QPointF{center.x()+1,center.y()});
    QLineF line1(center, p1);
    double startAngle = line0.angleTo(line1);

    double sweepAngle = atan(std::abs(bulge)) * 4 * 180 / M_PI;
    if (bulge < 0) sweepAngle = -sweepAngle;

    QPainterPath path;
    path.moveTo(p1);
    path.arcTo(QRectF(center.x() - radius, center.y() - radius, 2 * radius, 2 * radius),
               startAngle, sweepAngle);
    return path;
}

void getCircleFromBulge(const QPointF& p1, const QPointF& p2, const double & bulge, QPointF& center,double & radius)
{
    // 1. 计算 θ（弧度）
    double theta = atan(std::abs(bulge)) * 4;

    // 2. 计算弦长 AB
    double AB = sqrt(pow(p1.x() - p2.x(), 2) + pow(p1.y() - p2.y(), 2));

    // 3. 计算半径 R
    radius = (AB / 2) / sin(theta / 2);

    // 4. 计算 a 和 c
    double a = acos(std::min(1.0, (AB / 2) / radius));
    double c = atan2(p2.y() - p1.y(), p2.x() - p1.x());

    // 5. 计算两个可能的圆心坐标
    double CX1 = p1.x() + cos(c + a) * radius;
    double CY1 = p1.y() + sin(c + a) * radius;
    double CX2 = p1.x() + cos(c - a) * radius;
    double CY2 = p1.y() + sin(c - a) * radius;

    // qDebug() << CX1 << CY1;
    // qDebug() << CX2 << CY2;

    // 6. 选择正确的圆心
    if (bulge < -1 || (bulge > 0 && bulge < 1)) {
        center =  QPointF(CX2, CY2);
    } else {
        center =  QPointF(CX1, CY1);
    }

    // qDebug() << "getCircleFromBulge" << center << radius;
}
void getCircleFromThreePoints(const QPointF& p1, const QPointF& p2, const QPointF& p3, QPointF& center, double & radius)
{
    double A = p1.x()*(p2.y() - p3.y()) - p1.y()*(p2.x() - p3.x()) + p2.x()*p3.y() - p3.x()*p2.y();
    double B = (p1.x()*p1.x() + p1.y()*p1.y())*(p3.y() - p2.y()) + (p2.x()*p2.x() + p2.y()*p2.y())*(p1.y() - p3.y()) + (p3.x()*p3.x() + p3.y()*p3.y())*(p2.y() - p1.y());
    double C = (p1.x()*p1.x() + p1.y()*p1.y())*(p2.x() - p3.x()) + (p2.x()*p2.x() + p2.y()*p2.y())*(p3.x() - p1.x()) + (p3.x()*p3.x() + p3.y()*p3.y())*(p1.x() - p2.x());
    double D = (p1.x()*p1.x() + p1.y()*p1.y())*(p3.x()*p2.y() - p2.x()*p3.y()) + (p2.x()*p2.x() + p2.y()*p2.y())*(p1.x()*p3.y() - p3.x()*p1.y()) + (p3.x()*p3.x ()+ p3.y()*p3.y())*(p2.x()*p1.y() - p1.x()*p2.y());

    center.setX(  -(B / (2 * A)) );
    center.setY( -(C / (2 * A)) );
    radius = sqrt((B*B + C*C - 4 * A * D) / (4 * A * A));

    // qDebug() << "center"<<center <<" radius" <<radius;
}
void getBulgeFromThreePoints(const QPointF& p1, const QPointF& p2, const QPointF& p3,const QPointF& center,const double & radius, double  &bulge)
{
    QLineF line1(center,p1);
    QLineF line2(center,p2);
    QLineF line3(center,p3);

    double angle12 = line1.angleTo(line2);
    double angle13 = line1.angleTo(line3);
    // qDebug() <<  "getBulgeFromThreePoints" << angle12 << angle13;

    if (angle13 >= angle12)
    {
        double angle13Rad = qDegreesToRadians(angle13);
        bulge = std::tan(angle13Rad / 4.0);
    }
    else
    {
        double angle13Rad = qDegreesToRadians(360-angle13);
        bulge = std::tan(-angle13Rad / 4.0);
    }
}
