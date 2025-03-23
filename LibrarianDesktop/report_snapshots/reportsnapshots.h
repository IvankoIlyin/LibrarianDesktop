#ifndef REPORTSNAPSHOTS_H
#define REPORTSNAPSHOTS_H
#include<QVector>
#include"database_manager.h"


class ReportSnapshots
{
private:
    std::shared_ptr<DataBase_Manager> db_manager;
    QVector<Transaction*> all_transaction;
public:
    ReportSnapshots(std::shared_ptr<DataBase_Manager> db_manager = nullptr);

    QVector<Transaction*> snapshot_by_date(const QString& start_date, const QString& end_date);
    QVector<Transaction*> snapshot_by_reader(const QString& reader_name);
    QVector<Transaction*> snapshot_by_librarian(const QString& librarian_name);
    QVector<Transaction*> snapshot_by_document_type(const QString& document_type);
    QVector<Transaction*> snapshot_by_document_author(const QString& document_author);

};

#endif // REPORTSNAPSHOTS_H
