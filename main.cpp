#include "mainwindowstarlight.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindowStarlight w;
    w.show();

    return a.exec();
}
