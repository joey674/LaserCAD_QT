#include "mainwindow.h"

#include <QApplication>
#include "css.h"
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

    initGlobalStyle();
    //
    MainWindow w;
    w.show();
    return a.exec();
}
