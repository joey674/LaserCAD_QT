#include "utils.h"
#include "logger.h"
#include <QUuid>
#include <QString>
#include <QDebug>


QString GenerateUUID()
{
    QUuid uuid = QUuid::createUuid();
    return uuid.toString(QUuid::WithoutBraces);
}

void test()
{
    DEBUG_MSG("aa");
}
