#include "tablewidget.h"

TableWidget::TableWidget() : QWidget(nullptr) {
    table_widget = new QTableWidget(this);
    table_widget->verticalHeader()->setVisible(false);
    table_widget->setSelectionBehavior(QAbstractItemView::SelectRows);
    table_widget->setSelectionMode(QAbstractItemView::SingleSelection);
}

TableWidget::TableWidget(QWidget* parent, DataBase_Manager* db_manager)
    : QWidget(parent)
    , db_manager(db_manager)
{
    table_widget = new QTableWidget(this);
    table_widget->verticalHeader()->setVisible(false);
    table_widget->setSelectionBehavior(QAbstractItemView::SelectRows);
    table_widget->setSelectionMode(QAbstractItemView::SingleSelection);
}

void TableWidget::display_users() {
    if (!db_manager) {
        qWarning() << "Database manager is null";
        return;
    }

    QVector<User*> users = db_manager->read_user_list();
    table_widget->setRowCount(users.size());
    table_widget->setColumnCount(3);
    QStringList headers;
    headers << "id" << "name" << "role";
    table_widget->setHorizontalHeaderLabels(headers);
    for(int i=0;i<users.size();i++) {
        table_widget->setItem(i,0,new QTableWidgetItem(QString::number(users[i]->get_id())));
        table_widget->setItem(i,1,new QTableWidgetItem(users[i]->get_name()));
        table_widget->setItem(i,2,new QTableWidgetItem(users[i]->get_role()));
    }
}

void TableWidget::display_documents() {
    if (!db_manager) {
        qWarning() << "Database manager is null";
        return;
    }

    QVector<Document*> documents = db_manager->read_document_list();
    table_widget->setRowCount(documents.size());
    table_widget->setColumnCount(4);
    QStringList headers;
    headers << "id" << "title" << "author" << "type";
    table_widget->setHorizontalHeaderLabels(headers);
    for(int i=0;i<documents.size();i++) {
        table_widget->setItem(i,0,new QTableWidgetItem(QString::number(documents[i]->get_id())));
        table_widget->setItem(i,1,new QTableWidgetItem(documents[i]->get_title()));
        table_widget->setItem(i,2,new QTableWidgetItem(documents[i]->get_author()));
        table_widget->setItem(i,3,new QTableWidgetItem(documents[i]->get_type()));
    }
}

void TableWidget::display_transaction() {
    if (!db_manager) {
        qWarning() << "Database manager is null";
        return;
    }

    QVector<Transaction*> transactions = db_manager->read_transaction_list();
    table_widget->setRowCount(transactions.size());
    table_widget->setColumnCount(6);
    QStringList headers;
    headers << "id" << "reader" << "librarian" << "document" << "date" << "status";
    table_widget->setHorizontalHeaderLabels(headers);
    for(int i=0;i<transactions.size();i++) {
        table_widget->setItem(i,0,new QTableWidgetItem(QString::number(transactions[i]->get_id())));
        QString reader_name = db_manager->get_user_by_id(transactions[i]->get_reader_id())->get_name();
        QString librarian_name = db_manager->get_user_by_id(transactions[i]->get_librarian_id())->get_name();
        QString document_title = db_manager->get_document_by_id(transactions[i]->get_document_id())->get_title();
        table_widget->setItem(i,0,new QTableWidgetItem(QString::number(transactions[i]->get_id())));
        table_widget->setItem(i,1,new QTableWidgetItem(reader_name));
        table_widget->setItem(i,2,new QTableWidgetItem(librarian_name));
        table_widget->setItem(i,3,new QTableWidgetItem(document_title));
        table_widget->setItem(i,4,new QTableWidgetItem(transactions[i]->get_date()));
        table_widget->setItem(i,5,new QTableWidgetItem(transactions[i]->get_status()));
    }
}
