#ifndef LOGGER_H
#define LOGGER_H
#include <QApplication>

#define DEBUG_VAR(var) \
do { \
        qDebug() << #var " =" << (var); \
} while (0)

#define FATAL_VAR(var) \
do { \
        qFatal() << #var " =" << (var); \
} while (0)

#define INFO_VAR(var) \
do { \
        qInfo() << #var " =" << (var); \
} while (0)

#define DEBUG_VAR(var) \
do { \
        qDebug() << #var " =" << (var); \
} while (0)

#define FATAL_MSG(var) \
    do { \
        qFatal()  << (var); \
} while (0)

#define INFO_MSG(var) \
    do { \
            qInfo()  << (var); \
    } while (0)

#define DEBUG_MSG(var) \
do { \
        qDebug()  << (var); \
} while (0)


void initLogger();


#endif // LOGGER_H
