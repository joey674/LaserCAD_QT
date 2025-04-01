#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QUuid>
#include <QVariant>
#include <magic_enum.hpp>
#include <QRegularExpression>
#include <QGraphicsScene>


inline QString GenerateUUID()
{
    QUuid uuid = QUuid::createUuid();
    return uuid.toString(QUuid::WithoutBraces);
}

inline QVariant parseStringToPointF(const QString &text) {
    static const QRegularExpression re(R"(\(\s*([-+]?\d*\.?\d+)\s*,\s*([-+]?\d*\.?\d+)\s*\))");
    auto match = re.match(text);
    if (match.hasMatch()) {
        bool ok1, ok2;
        double x = match.captured(1).toDouble(&ok1);
        double y = match.captured(2).toDouble(&ok2);
        if (ok1 && ok2) return QPointF(x, y);
    }
    return {};
}
#endif // UTILS_H
