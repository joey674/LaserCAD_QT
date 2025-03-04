#include "logger.h"

void initLogger()
{
    qDebug() <<"init logger";
    qInstallMessageHandler(MessageHandler);
    // qSetMessagePattern( "[%{time MMdd h:mm:ss }] "
    //                    "[%{if-debug}DEBUG%{endif}"
    //                    "%{if-info}INFO%{endif}"
    //                    "%{if-warning}WARN%{endif}"
    //                    "%{if-critical}CRITICAL%{endif}"
    //                    "%{if-fatal}FATAL%{endif}] "
    //                    "[%{file}:%{line}] "
    //                    " [%{function}] "
    //                    "%{message}" );

}

#include <QFileInfo>
#include <QDebug>
#include <QDateTime>

void MessageHandler(QtMsgType type,
                      const QMessageLogContext &context,
                      const QString &msg)
{
    // modify msg
    QFileInfo fi(context.file ? context.file : "");
    QString fileName = fi.fileName();

    QString level;
    switch (type) {
    case QtDebugMsg:    level = "DEBUG";    break;
    case QtInfoMsg:     level = "INFO";     break;
    case QtWarningMsg:  level = "WARN";     break;
    case QtCriticalMsg: level = "CRITICAL"; break;
    case QtFatalMsg:    level = "FATAL";    break;
    }

    // msg
    QString finalMsg = QString("[%1] [%2] [%3:%4] [%5]  %6")
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
