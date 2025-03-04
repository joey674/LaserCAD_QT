#include "mainwindow.h"

#include <QApplication>
#include "logger.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    initLogger();
    return a.exec();
}
