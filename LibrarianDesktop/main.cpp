#include "mainwindow.h"

#include <QApplication>
#include<QVector>
#include"database_manager.h"
#include"report_snapshots/reportsnapshots.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // auto db_manager = std::make_unique<DataBase_Manager>();
    // ReportSnapshots report(db_manager.get());

    // QVector<Transaction*> tr = report.snapshot_by_reader_type("James Smith","Journal");
    // for(int i=0; i<tr.size();i++){
    //     qDebug()<<tr[i]->get_full_data();
    // }


    MainWindow w;
    w.show();
    return a.exec();



}
