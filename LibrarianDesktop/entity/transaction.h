#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QString>
#include <QDateTime>

class Transaction {
public:
    Transaction();
    Transaction(int id, int reader_id, int librarian_id, int document_id, const QString& status);
    Transaction(int id, int reader_id, int librarian_id, int document_id, const QString& date, const QString& status);

    int get_id() const;
    int get_reader_id() const;
    int get_librarian_id() const;
    int get_document_id() const;
    QString get_date() const;
    QString get_status() const;

private:
    int id;
    int reader_id;
    int librarian_id;
    int document_id;
    QString date;
    QString status;
};

#endif // TRANSACTION_H
