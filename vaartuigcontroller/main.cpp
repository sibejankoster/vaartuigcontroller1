#include "mainwindow.h"
#include "wptlijst.h"
#include <QApplication>
#include <QtWidgets>
#include <QtSql>
#include <QtDebug>

int main(int argc, char *argv[])
{   QApplication a(argc, argv);
    MainWindow w;
//    WPTlijst w;
    w.setWindowTitle("Vaartuigcontroller");
    //w.resize (750,570);

    w.show();

    return a.exec();
}
