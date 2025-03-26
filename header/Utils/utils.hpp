#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include "manager.h"
#include "logger.h"
#include <QUuid>
#include <QVariant>
#include <magic_enum.hpp>


inline QString GenerateUUID()
{
    QUuid uuid = QUuid::createUuid();
    return uuid.toString(QUuid::WithoutBraces);
}

inline void test() {
    // INFO_MSG("TEST");
    // auto map = DefaultPropertyMap;
    // DEBUG_VAR(map.find("Visible")->second);
    // map.find("Visible")->second = false;
    // DEBUG_VAR(map.find("Visible")->second);
}
#endif // UTILS_H
