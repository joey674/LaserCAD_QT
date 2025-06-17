#include "mainwindow.h"

#include <QApplication>
#include "css.h"
#include "laserworker.h"
#include "motionstageworker.h"
#include "logger.h"
#include "protocol.h"

int main(int argc, char *argv[]) {
    // logger
    initLogger();

    // 硬件线程
    LaserWorker::getIns().start();
    MotionStageWorker::getIns().start();

    // mainWindow
    QApplication a(argc, argv);
    initGlobalStyle();

    //
    MainWindow w;
    w.show();
    return a.exec();
}
