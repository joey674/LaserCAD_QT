#include "mainwindow.h"

#include <QApplication>
#include "logger.h"
#include "utils.hpp"

int main(int argc, char *argv[])
{
    initLogger();
    test();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
