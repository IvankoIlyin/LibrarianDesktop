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
    auto db_manager = std::make_unique<DataBase_Manager>();
    ReportSnapshots report(db_manager.get());
    SnapshotsDiagram diagram(&w, db_manager.get());
    report.saveTransactionsToJson();

    report.load_transactions_from_json();
    QVector<Transaction*> tr = report.snapshot_by_date_reader("2024-01-01","2026-01-01","James Smith");

    for (int i = 0; i < tr.size(); i++) {
        qDebug() << tr[i]->get_full_data();
    }

    w.show();

    diagram.setup_transaction_by_weekday(tr);
    diagram.display_diagram();

    return a.exec();
}
