#include "logger.h"

void initLogger()
{
    qInstallMessageHandler(MessageHandler);
    INFO_MSG("Logger init success");
}

#include <QFileInfo>
#include <QDebug>
#include <QDateTime>

void MessageHandler(QtMsgType type,
                    const QMessageLogContext &context,
                    const QString &msg)
{
    QFileInfo fi(context.file ? context.file : "");
    QString fileName = fi.fileName();

    QString level;
    const char *colorCode = "";
    const char *resetCode = "\033[0m";

    switch (type) {
    case QtDebugMsg:
        level = "\033[36mDEBUG\033[0m";
        break;
    case QtInfoMsg:
        level = "\033[32mINFO\033[0m";
        break;
    case QtWarningMsg:
        level = "\033[33mWARN\033[0m";
        break;
    case QtCriticalMsg:
        level = "\033[31mCRITICAL\033[0m";
        break;
    case QtFatalMsg:
        level = "\033[41m\033[97mFATAL\033[0m";
        break;
    }

    QString finalMsg = QString("[%1]  [%2]  [%3:%4]  [%5]  %6")
                           .arg(QDateTime::currentDateTime().toString("MMdd h:mm:ss"))
                           .arg(level)
                           .arg(fileName)
                           .arg(context.line)
                           .arg(context.function)
                           .arg(msg);

    fprintf(stdout, "%s\n", finalMsg.toLocal8Bit().constData());
    fflush(stdout);

    if (type == QtFatalMsg) {
        abort();
    }
}
