#include "mainwindow.h"

#include <QApplication>
#include "logger.h"
#include "protocol.h"

int main(int argc, char *argv[]) {
    initLogger();
    qRegisterMetaType < Vertex > ("Vertex");
    qRegisterMetaType < MarkParams > ("MarkParams");
    qRegisterMetaType < DelayParams > ("DelayParams");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
