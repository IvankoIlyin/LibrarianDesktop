#ifndef REPORTSNAPSHOTS_H
#define REPORTSNAPSHOTS_H
#include<QVector>
#include"database_manager.h"
#include <QFile>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonArray>
#include <QMap>



class ReportSnapshots
{
private:
     DataBase_Manager* db_manager;
    QVector<Transaction*> all_transaction;

    QJsonObject storageData;
    QString storagePath;

    void initializeStorage();

public:
    ReportSnapshots(DataBase_Manager* db_manager = nullptr);
    QVector<Transaction*> storage_transaction;
    bool saveTransactionsToJson();
    bool load_transactions_from_json();
    QVector<Transaction*> snapshot_by_date(const QVector<Transaction*>& transactions, const QString& start_date, const QString& end_date);
    QVector<Transaction*> snapshot_by_reader(const QVector<Transaction*>& transactions, const QString& reader_name);
    QVector<Transaction*> snapshot_by_librarian(const QVector<Transaction*>& transactions, const QString& librarian_name);
    QVector<Transaction*> snapshot_by_document_type(const QVector<Transaction*>& transactions, const QString& document_type);
    QVector<Transaction*> snapshot_by_document_author(const QVector<Transaction*>& transactions, const QString& document_author);


    QVector<Transaction*> snapshot_by_date_author(const QString& start_date, const QString& end_date, const QString& document_author);
    QVector<Transaction*> snapshot_by_date_type(const QString& start_date, const QString& end_date, const QString& document_type);
    QVector<Transaction*> snapshot_by_date_reader(const QString& start_date, const QString& end_date, const QString& reader_name);
    QVector<Transaction*> snapshot_by_date_librarian(const QString& start_date, const QString& end_date, const QString& librarian_name);
    QVector<Transaction*> snapshot_by_reader_type(const QString& reader_name, const QString& document_type);
    QVector<Transaction*> snapshot_by_reader_author(const QString& reader_name, const QString& document_author);

    QVector<Transaction*> sort_by_popular_of_document(QVector<Transaction*> transactions);
    QVector<Transaction*> sort_by_reader_activity(QVector<Transaction*> transactions);
    QVector<Transaction*> sort_by_librarian_activity(QVector<Transaction*> transactions);






};

#endif // REPORTSNAPSHOTS_H
