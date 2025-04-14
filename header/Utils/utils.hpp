#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QUuid>
#include <QVariant>
#include <magic_enum.hpp>
#include <QRegularExpression>
#include <QGraphicsScene>
#include "logger.h"
#include "protocol.h"
#include <QPainter>


inline QString GenerateUUID() {
    QUuid uuid = QUuid::createUuid();
    return uuid.toString(QUuid::WithoutBraces);
}

///
/// \brief getAngleFromBulge 绘制圆弧时的转换 vertex<->Point/bulge
/// \param bulge
/// \param angle
///
inline void getAngleFromBulge(const double &bulge, double &angle) {
    double theta = atan(std::abs(bulge)) * 4;
    if (bulge >= 0) {
        angle = qRadiansToDegrees(theta);
    } else {
        angle = -qRadiansToDegrees(theta);
    }
}
inline void getBulgeFromAngle(const double &angle, double &bulge) {
    double theta = qDegreesToRadians(abs(angle));
    if (angle >= 0) {
        bulge = tan(theta / 4);
    } else {
        bulge = -tan(theta / 4);
    }
}
// 从点获取圆以及对应弧信息
inline void getCircleFromTwoPointsAndAngle(
    const QPointF &p1, const QPointF &p2, const double &angle, QPointF &center, double &radius) {
    double theta = qDegreesToRadians(abs(angle));
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
    if ((angle > -360 && angle < -180) || (angle > 0 && angle < 180)) {
        center = QPointF(CX2, CY2);
    } else {
        center = QPointF(CX1, CY1);
    }
}
inline void getCircleFromThreePoints(
    const QPointF &p1, const QPointF &p2, const QPointF &p3, QPointF &center, double &radius) {
    double A = p1.x() * (p2.y() - p3.y()) - p1.y() * (p2.x() - p3.x()) + p2.x() * p3.y()
               - p3.x() * p2.y();
    double B = (p1.x() * p1.x() + p1.y() * p1.y()) * (p3.y() - p2.y())
               + (p2.x() * p2.x() + p2.y() * p2.y()) * (p1.y() - p3.y())
               + (p3.x() * p3.x() + p3.y() * p3.y()) * (p2.y() - p1.y());
    double C = (p1.x() * p1.x() + p1.y() * p1.y()) * (p2.x() - p3.x())
               + (p2.x() * p2.x() + p2.y() * p2.y()) * (p3.x() - p1.x())
               + (p3.x() * p3.x() + p3.y() * p3.y()) * (p1.x() - p2.x());
    double D = (p1.x() * p1.x() + p1.y() * p1.y()) * (p3.x() * p2.y() - p2.x() * p3.y())
               + (p2.x() * p2.x() + p2.y() * p2.y()) * (p1.x() * p3.y() - p3.x() * p1.y())
               + (p3.x() * p3.x() + p3.y() * p3.y()) * (p2.x() * p1.y() - p1.x() * p2.y());
    center.setX(-(B / (2 * A)));
    center.setY(-(C / (2 * A)));
    radius = sqrt((B * B + C * C - 4 * A * D) / (4 * A * A));
}
inline void getAngleFromThreePoints(const QPointF &p1,
                                    const QPointF &p2,
                                    const QPointF &p3,
                                    double &angle) {
    QPointF center = QPointF{};
    double radius = 0;
    getCircleFromThreePoints(p1, p2, p3, center, radius);
    QLineF line1(center, p1);
    QLineF line2(center, p2);
    QLineF line3(center, p3);
    double angle12 = line1.angleTo(line2);
    double angle13 = line1.angleTo(line3);
    if (angle13 >= angle12) {
        angle = angle13;
    } else {
        angle = angle13 - 360;
    }
}
// 从一条弧中获取一定角度的截点
inline void getIntersectPoint(const QPointF &p1,
                              const QPointF &p3,
                              const double &p1p3Angle,
                              const double &sweepAngle,
                              QPointF &intersectPoint) {
    if (sweepAngle < 0) {
        FATAL_MSG("intersect angle must be positive");
    }
    QPointF center = QPointF{};
    double radius = 0;
    getCircleFromTwoPointsAndAngle(p1, p3, p1p3Angle, center, radius);
    double p1p2Angle = sweepAngle;
    if (p1p3Angle <= 0) {
        p1p2Angle = -p1p2Angle;
    }
    QLineF line(center, p1);
    line.setAngle(line.angle() + p1p2Angle);
    intersectPoint = line.p2();
}
//
inline QPainterPath createArcPath(const QPointF &p1, const QPointF &p3, const double &angle) {
    QPointF center = QPointF{};
    double radius = 0;
    getCircleFromTwoPointsAndAngle(p1, p3, angle, center, radius);
    QLineF line0(center, QPointF{center.x() + 1, center.y()});
    QLineF line1(center, p1);
    double startAngle = line0.angleTo(line1);
    QPainterPath path;
    path.moveTo(p1);
    path.arcTo(QRectF(center.x() - radius, center.y() - radius, 2 * radius, 2 * radius),
               startAngle,
               angle);
    return path;
}

///
/// \brief parseStringToPointF
/// \param text
/// \return
///
inline QPointF parseStringToPointF(const QString &text) {
    static const QRegularExpression re(R"(\s*([-+]?\d*\.?\d+)\s*,\s*([-+]?\d*\.?\d+)\s*)");
    auto match = re.match(text);
    if (match.hasMatch()) {
        bool ok1, ok2;
        double x = match.captured(1).toDouble(&ok1);
        double y = match.captured(2).toDouble(&ok2);
        if (ok1 && ok2) {
            return QPointF(x, y);
        }
    }
    WARN_MSG("Fail to parse String to Point: " + text );
    return QPointF();
}

inline QString parsePointFToString(const QPointF &point) {
    return QString("%1, %2").arg(point.x(), 0, 'f', 1).arg(point.y(), 0, 'f', 1);
}

inline Vertex parseStringToVertex(const QString &text) {
    static const QRegularExpression re(R"(\s*([-+]?\d*\.?\d+)\s*,\s*([-+]?\d*\.?\d+)\s*,\s*([-+]?\d*\.?\d+)\s*)");
    auto match = re.match(text);
    if (match.hasMatch()) {
        bool ok1, ok2, ok3;
        double x = match.captured(1).toDouble(&ok1);
        double y = match.captured(2).toDouble(&ok2);
        double angle = match.captured(3).toDouble(&ok3);
        if (ok1 && ok2 && ok3) {
            return Vertex{ QPointF(x, y), angle };
        }
    }
    WARN_MSG("Fail to parse String to Vertex: " + text);
    return Vertex{ QPointF(), 0.0 };
}

inline QString parseVertexToString(const Vertex &vertex) {
    return QString("%1, %2, %3").arg(vertex.point.x(), 0, 'f', 1).arg(vertex.point.y(), 0, 'f', 1).arg(vertex.angle, 0, 'f', 1);
}


#endif // UTILS_H
