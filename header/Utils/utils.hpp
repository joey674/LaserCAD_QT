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


inline QString GenerateUUID()
{
    QUuid uuid = QUuid::createUuid();
    return uuid.toString(QUuid::WithoutBraces);
}

inline QPointF parseStringToPointF(const QString &text) {
    static const QRegularExpression re(R"(\(\s*([-+]?\d*\.?\d+)\s*,\s*([-+]?\d*\.?\d+)\s*\))");
    auto match = re.match(text);
    if (match.hasMatch()) {
        bool ok1, ok2;
        double x = match.captured(1).toDouble(&ok1);
        double y = match.captured(2).toDouble(&ok2);
        if (ok1 && ok2) return QPointF(x, y);
    }
    WARN_MSG("Fail to parse String to Point: " + text );
    return QPointF();
}

inline QString parsePointFToString(const QPointF &point) {
    return QString("(%1, %2)").arg(point.x(), 0, 'f', 1).arg(point.y(), 0, 'f', 1);
}

inline Vertex parseStringToVertex(const QString &text) {
    // 预期格式：((x, y),angle)
    static const QRegularExpression re(R"(\(\(\s*([-+]?\d*\.?\d+)\s*,\s*([-+]?\d*\.?\d+)\s*\)\s*,\s*([-+]?\d*\.?\d+)\s*\))");
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
    return QString("((%1, %2),%3)").arg(vertex.point.x(), 0, 'f', 1).arg(vertex.point.y(), 0, 'f', 1).arg(vertex.angle, 0, 'f', 1);
}

#endif // UTILS_H
