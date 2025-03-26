#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QUuid>
#include <QVariant>
#include <magic_enum.hpp>


inline QString GenerateUUID()
{
    QUuid uuid = QUuid::createUuid();
    return uuid.toString(QUuid::WithoutBraces);
}
#endif // UTILS_H
