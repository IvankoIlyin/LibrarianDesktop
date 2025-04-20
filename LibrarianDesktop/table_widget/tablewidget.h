#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QHeaderView>
#include<QMenu>
#include "database_manager.h"
#include "../user_widget/userwidget.h"
#include "../document_widget/documentwidget.h"
#include"../transaction_widget/transactionwidget.h"

class TableWidget: public QWidget
{
private:

    DataBase_Manager* db_manager;
    QString displayed_entity="";

public:
    QTableWidget* table_widget;
    TableWidget();
    TableWidget(QWidget* parent = nullptr, DataBase_Manager* db_manager = nullptr);
    void display_users();
    void display_documents();
    void display_transaction(int sort_code); //0-id 1-popular_of_doc 2-reader_activity 3-librarian_activity



    QVector<Transaction*> sort_by_popular_of_document(QVector<Transaction*> transactions);
    QVector<Transaction*> sort_by_reader_activity(QVector<Transaction*> transactions);
    QVector<Transaction*> sort_by_librarian_activity(QVector<Transaction*> transactions);

private slots:
    void onTableRowRightClicked(const QPoint &pos);
};

#endif // TABLEWIDGET_H
