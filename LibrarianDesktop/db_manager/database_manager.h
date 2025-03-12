// database_manager.h
#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QCoreApplication>
#include <QSqlError>
#include<QVector>

#include"user.h"
#include"document.h"
#include"transaction.h"


class DataBase_Manager {
private:
    //DATABASE, DB_PATH
    QSqlDatabase db;
    QString dbPath;

public:
    //CONSTRUCTOR
    DataBase_Manager();
    //DESTRUCTOR
    ~DataBase_Manager();

    //TEST DB CONNECTION
    void debugDatabase();
    void debugConnection();

    //CREATE
    bool create_user(const QString& _name, const QString& _role);
    bool create_document(const QString& _title, const QString& _author,const QString& _type);
    bool create_transaction(int reader_id, int librarian_id, int document_id, const QString& status);

    //READ
    QVector<User*> read_user_list();
    QVector<Document*> read_document_list();
    QVector<Transaction*>read_transaction_list();

    //UPDATE
    bool update_user_by_id(int id, const QString& _name, const QString& _role);
    bool update_document_by_id(int id, const QString& _title, const QString& _author,const QString& _type);
    bool update_transaction_by_id(int id, int reader_id, int librarian_id, int document_id,const QString& date, const QString& status);

    //DELETE
    bool delete_user_by_id(int id);
    bool delete_document_by_id(int id);
    bool delete_transaction(int id);

    //GET BY ID
    User* get_user_by_id(int id);
    Document* get_document_by_id(int id);
    Transaction* get_transaction_by_id(int id);

    // GET USER BY NAME
    User* get_user_by_name(const QString& name);

    //GET USERS BY ROLE
    QVector<User*> get_users_by_role(const QString& role);

    //GET DOCUMENT BY TITLE
    Document* get_document_by_title(const QString& title);

    //GET DOCUMENTS BY AUTHOR
    QVector<Document*> get_documents_by_author(const QString& author);

    //GET DOCUMENTS BY TYPE
    QVector<Document*> get_documents_by_type(const QString& type);

    //GET TRANSACTIONS BY READER_ID
    QVector<Transaction*> get_transactions_by_reader_id(int reader_id);

    //GET TRANSACTIONS BY LIBRARIAN_ID
    QVector<Transaction*> get_transactions_by_librarian_id(int librarian_id);

    //GET TRANSACTIONS BY DOCUMENT_ID
    QVector<Transaction*> get_transactions_by_document_id(int document_id);

    //GET TRANSACTIONS BY
    QVector<Transaction*> get_transactions_by_date(const QString& date);

    //GET TRANSACTIONS BY STATUS
    QVector<Transaction*> get_transactions_by_status(const QString& status);


};

#endif // DATABASE_MANAGER_H
