#include "mainwindow.h"

#include <QApplication>
#include<QVector>
#include"database_manager.h"
#include"report_snapshots/reportsnapshots.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //auto db_manager = std::make_shared<DataBase_Manager>();
    //ReportSnapshots report(db_manager);
    // QVector<Transaction*> tr = report.snapshot_by_date("2024-01-01","2024-02-01");
    // for(int i=0; i<tr.size();i++){
    //     qDebug()<<tr[i]->get_full_data();
    // }

    // QVector<Transaction*> reader = report.snapshot_by_librarian("William Carter");
    // for(int i=0; i<reader.size();i++){
    //     qDebug()<<reader[i]->get_full_data();
    // }

    // QVector<Transaction*> type = report.snapshot_by_document_author("Stephen King");
    // for(int i=0; i<type.size();i++){
    //     qDebug()<<type[i]->get_full_data();
    // }



    MainWindow w;
    w.show();
    return a.exec();



}
