#include "mainwindow.h"

#include <QApplication>
#include<QVector>
#include"database_manager.h"
#include"report_snapshots/reportsnapshots.h"
#include"snapshots_diagram/snapshotsdiagram.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    // auto db_manager = std::make_unique<DataBase_Manager>();
    // ReportSnapshots report(db_manager.get());
    // SnapshotsDiagram diagram(&w, db_manager.get());
    // report.saveTransactionsToJson();

    //QVector<Transaction*> tr = report.snapshot_by_date_reader("2024-01-01","2026-01-01","James Smith");

    // QVector<Transaction*> tr = report.storage_transaction;
    // tr = report.sort_by_librarian_activity(tr);
    //tr = report.sort_by_reader_activity(tr);
    //tr = report.sort_by_popular_of_document(tr);


    // for (int i = 0; i < tr.size(); i++) {
    //     qDebug() << tr[i]->get_id()<<" --" <<
    //         db_manager.get()->get_user_by_id(tr[i]->get_reader_id())->get_name()<< "--" <<
    //         db_manager.get()->get_user_by_id(tr[i]->get_librarian_id())->get_name()<< "--"<<
    //         db_manager.get()->get_document_by_id(tr[i]->get_document_id())->get_title();
    // }

    w.show();

    // diagram.setup_transaction_by_weekday(tr);
    // diagram.display_diagram();

    return a.exec();
}
