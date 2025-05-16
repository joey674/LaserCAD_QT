#include "mainwindow.h"

#include <QApplication>
#include "laserworker.h"
#include "logger.h"
#include "protocol.h"

int main(int argc, char *argv[]) {
    // logger
    initLogger();
    //
    LaserWorker::getIns().startLaserWorker();
    // mainWindow
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
