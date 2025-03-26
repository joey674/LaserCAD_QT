#ifndef LOGGER_H
#define LOGGER_H
#include <QDebug>

///
///
///
#define DEBUG_VAR(var) \
do { \
        qDebug() << #var " =" << (var); \
} while (0)

#define WARN_VAR(var) \
do { \
        qWarning() << #var " =" << (var); \
} while (0)

#define FATAL_VAR(var) \
do { \
        qFatal() << #var " =" << (var); \
} while (0)

#define INFO_VAR(var) \
do { \
        qInfo() << #var " =" << (var); \
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

#define WARN_MSG(var) \
do { \
        qWarning()  << (var); \
} while (0)

void initLogger();
void MessageHandler(QtMsgType type,const QMessageLogContext &context,const QString &msg);

#endif // LOGGER_H
