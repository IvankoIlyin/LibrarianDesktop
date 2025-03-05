#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QHeaderView>
#include "database_manager.h"
class TableWidget: public QWidget
{
private:

    DataBase_Manager db_manager;

public:
    QTableWidget* table_widget;
    TableWidget();
    TableWidget(QWidget* parent = nullptr);
    void display_users();
    void display_documents();
    void display_transaction();
};

#endif // TABLEWIDGET_H
