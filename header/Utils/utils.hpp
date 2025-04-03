#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QUuid>
#include <QVariant>
#include <magic_enum.hpp>
#include <QRegularExpression>
#include <QGraphicsScene>
#include "logger.h"


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

#endif // UTILS_H
