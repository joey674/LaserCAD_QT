#include "mainwindow.h"

#include <QApplication>
#include "logger.h"
#include "protocol.h"

int main(int argc, char *argv[]) {
    initLogger();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
