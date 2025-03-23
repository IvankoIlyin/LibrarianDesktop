#include "reportsnapshots.h"

ReportSnapshots::ReportSnapshots(std::shared_ptr<DataBase_Manager> db_manager): db_manager(std::move(db_manager)) {

}


QVector<Transaction*> ReportSnapshots:: snapshot_by_date(const QString& start_date, const QString& end_date){
    QDate start_d = QDate::fromString(start_date, "yyyy-MM-dd");
    QDate end_d = QDate::fromString(end_date, "yyyy-MM-dd");
    all_transaction = db_manager->read_transaction_list();
    QVector<Transaction*> snapshot;
    for(int i=0; i<all_transaction.size(); i++){
        QDate curr_date = QDate::fromString(all_transaction[i]->get_date(),"yyyy-MM-dd");
        if(curr_date>=start_d && curr_date<= end_d){
            snapshot.append(all_transaction[i]);
        }
    }
    return snapshot;
}


QVector<Transaction*> ReportSnapshots:: snapshot_by_reader(const QString& reader_name){
    all_transaction = db_manager->read_transaction_list();
    QVector<Transaction*> snapshot;
    for(int i=0; i<all_transaction.size(); i++){
        QString curr_reader_name = db_manager->get_user_by_id(all_transaction[i]->get_reader_id())->get_name();
        if(curr_reader_name==reader_name){
            snapshot.append(all_transaction[i]);
        }
    }
    return snapshot;
}


QVector<Transaction*> ReportSnapshots:: snapshot_by_librarian(const QString& librarian_name){
    all_transaction = db_manager->read_transaction_list();
    QVector<Transaction*> snapshot;
    for(int i=0; i<all_transaction.size(); i++){
        QString curr_librarian_name = db_manager->get_user_by_id(all_transaction[i]->get_librarian_id())->get_name();
        if(curr_librarian_name==librarian_name){
            snapshot.append(all_transaction[i]);
        }
    }
    return snapshot;
}


QVector<Transaction*> ReportSnapshots:: snapshot_by_document_type(const QString& document_type){
    all_transaction = db_manager->read_transaction_list();
    QVector<Transaction*> snapshot;
    for(int i=0; i<all_transaction.size(); i++){
        QString curr_document_type = db_manager->get_document_by_id(all_transaction[i]->get_document_id())->get_type();
        if(curr_document_type==document_type){
            snapshot.append(all_transaction[i]);
        }
    }
    return snapshot;
}


QVector<Transaction*> ReportSnapshots:: snapshot_by_document_author(const QString& document_author){
    all_transaction = db_manager->read_transaction_list();
    QVector<Transaction*> snapshot;
    for(int i=0; i<all_transaction.size(); i++){
        QString curr_document_author = db_manager->get_document_by_id(all_transaction[i]->get_document_id())->get_author();
        if(curr_document_author==document_author){
            snapshot.append(all_transaction[i]);
        }
    }
    return snapshot;
}
