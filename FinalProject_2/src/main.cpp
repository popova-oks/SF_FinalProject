﻿#include "../headers/mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Project Popova O.S.");
    w.resize(800, 600);

    w.show();
    return a.exec();
}
