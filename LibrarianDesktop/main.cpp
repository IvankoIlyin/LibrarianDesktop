#include "mainwindow.h"

#include <QApplication>
#include<QVector>
#include"database_manager.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DataBase_Manager db_manager;

    //db_manager.create_document("test","test","test");
    //db_manager.update_document_by_id(243,"aaa","aaa","aaa");
    //db_manager.delete_document_by_id(243);

    // QVector<Document> docs = db_manager.read_document_list();
    // for(int i=0; i<docs.length(); i++){
    //     qDebug()<<docs[i].get_id()<<"-"<<docs[i].get_title()<<"-"<<docs[i].get_author()<<"-"<<docs[i].get_type();
    // }

    //db_manager.create_user("John Doe","Reader");
    //db_manager.update_user_by_id(113, "Bill Doe", "Reader");
    // db_manager.delete_user_by_id(113);

    // QVector<User> users = db_manager.read_user_list();
    // for(int i=0; i<users.length(); i++){
    //      qDebug()<<users[i].get_id()<<"-"<<users[i].get_name()<<"-"<<users[i].get_role();
    // }


    // User *u = db_manager.get_user_by_id(1);
    // if (u != nullptr) {
    //     qDebug() << u->get_name();
    //     delete u;
    // }

    // Document *u = db_manager.get_document_by_id(1);
    // if (u != nullptr) {
    //     qDebug() << u->get_title();
    //     delete u;
    // }

    // QVector<Document*> docs = db_manager.get_documents_by_type("Journal");
    // for(int i=0; i<docs.length(); i++){
    //     qDebug()<<docs[i]->get_id()<<"-"<<docs[i]->get_title()<<"-"<<docs[i]->get_author()<<"-"<<docs[i]->get_type();
    // }

    //db_manager.create_transaction(1,101,1,"Taken");
    //db_manager.update_transaction(503,1,101,1,"Continued");
    //db_manager.delete_transaction(503);
    // QVector<Transaction*> tr = db_manager.read_transaction_list();
    // for(int i=0; i<tr.length(); i++){
    //     qDebug()<<tr[i]->get_id()<<"-"<<tr[i]->get_date()<<"-"<<tr[i]->get_status();
    // }


    // Transaction *tr = db_manager.get_transaction_by_id(500);
    // if (tr != nullptr) {
    //     qDebug() << tr->get_date();
    //     delete tr;
    // }

    // QVector<Transaction*> trs = db_manager.get_transactions_by_status("Taken");
    // for(int i=0; i<trs.length(); i++){
    //     qDebug()<<trs[i]->get_date();
    // }


    MainWindow w;
    //w.show();
    return a.exec();
}
