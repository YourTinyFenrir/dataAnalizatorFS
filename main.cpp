#include "mainwindow.h"
#include <QApplication>

#include "stats.h"
#include "QFile"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
