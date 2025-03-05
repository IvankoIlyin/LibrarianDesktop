#include "mainwindow.h"

#include <QApplication>
#include<QVector>
#include"database_manager.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DataBase_Manager db_manager;

    MainWindow w;
    w.show();
    return a.exec();
}
