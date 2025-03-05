#include "transaction.h"
#include <QDateTime>

Transaction::Transaction()
    : id(0), reader_id(0), librarian_id(0), document_id(0) {
    date = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    status = "Taken";
}

Transaction::Transaction(int id, int reader_id, int librarian_id,
                         int document_id, const QString& status)
    : id(id), reader_id(reader_id), librarian_id(librarian_id),
    document_id(document_id), date(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")), status(status) {}

Transaction::Transaction(int id, int reader_id, int librarian_id,
                         int document_id, const QString& date, const QString& status)
    : id(id), reader_id(reader_id), librarian_id(librarian_id),
    document_id(document_id), date(date), status(status) {}

int Transaction::get_id() const { return id; }
int Transaction::get_reader_id() const { return reader_id; }
int Transaction::get_librarian_id() const { return librarian_id; }
int Transaction::get_document_id() const { return document_id; }
QString Transaction::get_date() const { return date; }
QString Transaction::get_status() const { return status; }
QString Transaction::get_full_data() const{return QString::number(id)+ " - " + reader_name + " - " + librarian_name+ " - " + document_title+ " - " + date+ " - " + status;}
