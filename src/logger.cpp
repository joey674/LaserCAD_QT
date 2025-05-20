#include "logger.h"
#include <QDateTime>
#include <QDebug>
#include <QFileInfo>
#include <QDir>

QFile logFile;

void initLogger()
{
     initLogFile();
    qInstallMessageHandler(MessageHandler);
    INFO_MSG("Logger init success");
}

void initLogFile()
{
    // 使用相对路径（当前工作目录下的 logFile）
    QString logDirPath = "logFile";
    QDir logDir;

    if (!logDir.exists(logDirPath)) {
        if (!logDir.mkpath(logDirPath)) {
            qWarning() << "can not create log file dir:" << logDirPath;
        }
    }

    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd_HH-mm-ss");
    QString logFilePath = QString("%1/log_%2.txt").arg(logDirPath).arg(timestamp);

    logFile.setFileName(logFilePath);
    if (!logFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "can not open logfile" << logFilePath;
    }
}



void MessageHandler(QtMsgType type,
                    const QMessageLogContext &context,
                    const QString &msg)
{
    QFileInfo fi(context.file ? context.file : "");
    QString fileName = fi.fileName();

    QString colorLevel;
    switch (type) {
    case QtDebugMsg:
        colorLevel = "\033[36mDEBUG\033[0m";
        break;
    case QtInfoMsg:
        colorLevel = "\033[32mINFO\033[0m";
        break;
    case QtWarningMsg:
        colorLevel = "\033[33mWARN\033[0m";
        break;
    case QtCriticalMsg:
        colorLevel = "\033[31mCRITICAL\033[0m";
        break;
    case QtFatalMsg:
        colorLevel = "\033[41m\033[97mFATAL\033[0m";
        break;
    }

    QString plainLevel;
    switch (type) {
    case QtDebugMsg:
        plainLevel = "DEBUG";
        break;
    case QtInfoMsg:
        plainLevel = "INFO";
        break;
    case QtWarningMsg:
        plainLevel = "WARN";
        break;
    case QtCriticalMsg:
        plainLevel = "CRITICAL";
        break;
    case QtFatalMsg:
        plainLevel = "FATAL";
        break;
    }

    QString consoleMsg = QString("[%1]  [%2]  [%3:%4]  [%5]  %6")
                           .arg(QDateTime::currentDateTime().toString("MMdd h:mm:ss"))
                           .arg(colorLevel)
                           .arg(fileName)
                           .arg(context.line)
                           .arg(context.function)
                           .arg(msg);

    QString fileMsg = QString("[%1]  [%2]  [%3:%4]  [%5]  %6")
                          .arg(QDateTime::currentDateTime().toString("MMdd h:mm:ss"))
                          .arg(plainLevel)
                          .arg(fileName)
                          .arg(context.line)
                          .arg(context.function)
                          .arg(msg);

    // 打印到控制台
    fprintf(stdout, "%s\n", consoleMsg.toLocal8Bit().constData());
    fflush(stdout);

    // 写入日志文件
    if (logFile.isOpen()) {
        QTextStream stream(&logFile);
        stream << fileMsg << '\n';
        stream.flush();
    }

    if (type == QtFatalMsg) {
        abort();
    }
}
