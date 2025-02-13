#include "utils.h"
#include <QPointF>
#include <cmath>

QPointF calculateArcCenter(QPointF p1, QPointF p2, double bulge, double &radius)
{
    // 1. 计算 θ（弧度）
    double theta = atan(std::abs(bulge)) * 4;

    // 2. 计算弦长 AB
    double AB = sqrt(pow(p1.x() - p2.x(), 2) + pow(p1.y() - p2.y(), 2));

    // 3. 计算半径 R
    radius = (AB / 2) / sin(theta / 2);

    // 4. 计算 a 和 c
    double a = acos(std::min(1.0, (AB / 2) / radius));  // 防止浮点误差
    double c = atan2(p2.y() - p1.y(), p2.x() - p1.x()); // 计算 p1 到 p2 的角度

    // 5. 计算两个可能的圆心坐标
    double CX1 = p1.x() + cos(c + a) * radius;
    double CY1 = p1.y() + sin(c + a) * radius;
    double CX2 = p1.x() + cos(c - a) * radius;
    double CY2 = p1.y() + sin(c - a) * radius;

    // 6. 选择正确的圆心
    if (bulge < -1 || (bulge > 0 && bulge < 1)) {
        return QPointF(CX1, CY1);
    } else {
        return QPointF(CX2, CY2);
    }
}

QPainterPath createArcPath(QPointF p1, QPointF p2, double bulge)
{
    double radius;
    QPointF center = calculateArcCenter(p1, p2, bulge, radius);

    // 计算起始角度
    QLineF startVector(center, p1);
    double startAngle = startVector.angle();

    // 计算圆弧角度
    double sweepAngle = atan(std::abs(bulge)) * 4 * 180 / M_PI; // 转换为角度
    if (bulge < 0) sweepAngle = -sweepAngle; // 负 bulge 逆时针，正 bulge 顺时针

    // 创建圆弧路径
    QPainterPath path;
    path.moveTo(p1);
    path.arcTo(QRectF(center.x() - radius, center.y() - radius, 2 * radius, 2 * radius),
               startAngle, sweepAngle);
    return path;
}
