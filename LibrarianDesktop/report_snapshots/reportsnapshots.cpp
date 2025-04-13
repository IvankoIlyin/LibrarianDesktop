#include "reportsnapshots.h"

ReportSnapshots::ReportSnapshots(DataBase_Manager* db_manager): db_manager(db_manager) {
    initializeStorage();
}



//STORAGE OPERATIONS
void ReportSnapshots::initializeStorage() {
    QDir currentDir = QDir::current();

    if (!currentDir.exists("storage")) {
        if (!currentDir.mkdir("storage")) {
            qDebug() << "Failed to create storage directory";
            storagePath.clear();
            return;
        }
    }

    storagePath = currentDir.absoluteFilePath("storage/storage.json");
    QFile jsonFile(storagePath);

    if (!jsonFile.exists()) {
        // Створюємо порожній JSON об'єкт
        QJsonObject initialObj;
        initialObj["transactions"] = QJsonArray();
        QJsonDocument doc(initialObj);

        if (jsonFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            jsonFile.write(doc.toJson());
            jsonFile.close();
            qDebug() << "Created new empty storage.json";
        } else {
            qDebug() << "Failed to create storage.json";
            return;
        }
    }

    QJsonParseError parseError;
    if (jsonFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QByteArray rawData = jsonFile.readAll();
        jsonFile.close();

        QJsonDocument jsonDoc = QJsonDocument::fromJson(rawData, &parseError);
        if (parseError.error != QJsonParseError::NoError) {
            qDebug() << "JSON parse error:" << parseError.errorString();
            storageData = QJsonObject();
        } else {
            storageData = jsonDoc.object();
        }
    } else {
        qDebug() << "Failed to open storage.json";
        storageData = QJsonObject();
    }
}


bool ReportSnapshots::saveTransactionsToJson() {
    if (storagePath.isEmpty()) {
        qDebug() << "Storage path is empty";
        return false;
    }

    QJsonObject transactionsObj;
    QJsonArray transactionsArray;

    all_transaction = db_manager->read_transaction_list();
    load_transactions_from_json();

    QSet<int> existingIds;
    for (int i=0;i<storage_transaction.size();i++) {
        existingIds.insert(storage_transaction[i]->get_id());
    }

    QFile file(storagePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error opening file for reading";
        return false;
    }

    QByteArray rawData = file.readAll();
    file.close();

    QJsonDocument existingDoc = QJsonDocument::fromJson(rawData, nullptr);
    if (existingDoc.isNull()) {
        qDebug() << "Error parsing JSON";
        return false;
    }

    QJsonObject existingObj = existingDoc.object();
    QJsonArray existingArray = existingObj.value("transactions").toArray();

    for (int i = 0; i < all_transaction.size(); i++) {

        if (existingIds.contains(all_transaction[i]->get_id())) {
            continue;
        }

        QJsonObject transactionObj;
        transactionObj["id"] = all_transaction[i]->get_id();
        transactionObj["readerId"] = all_transaction[i]->get_reader_id();
        transactionObj["librarianId"] = all_transaction[i]->get_librarian_id();
        transactionObj["documentId"] = all_transaction[i]->get_document_id();
        transactionObj["date"] = all_transaction[i]->get_date();
        transactionObj["status"] = all_transaction[i]->get_status();

        existingArray.append(transactionObj);
    }

    transactionsObj["transactions"] = existingArray;
    QJsonDocument newDoc(transactionsObj);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Error opening file for writing";
        return false;
    }

    QByteArray jsonData = newDoc.toJson();
    qint64 bytesWritten = file.write(jsonData);
    file.close();

    return bytesWritten == jsonData.size();
}


bool ReportSnapshots::load_transactions_from_json() {
    if (storagePath.isEmpty()) {
        qDebug() << "Storage path is empty";
        return false;
    }

    QFile jsonFile(storagePath);
    QJsonParseError parseError;

    if (!jsonFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error opening file for reading";
        return false;
    }

    QByteArray rawData = jsonFile.readAll();
    jsonFile.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(rawData, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        qDebug() << "JSON parse error:" << parseError.errorString();
        return false;
    }

    QJsonObject rootObj = jsonDoc.object();

    qDeleteAll(storage_transaction);
    storage_transaction.clear();

    QJsonArray transactionsArray = rootObj.value("transactions").toArray();

    for (int i=0; i<transactionsArray.size();i++) {
        QJsonObject transactionObj = transactionsArray[i].toObject();

        int id= transactionObj.value("id").toInt();
        int reader_id=transactionObj.value("readerId").toInt();
        int librarian_id = transactionObj.value("librarianId").toInt();
        int document_id = transactionObj.value("documentId").toInt();
        QString date = transactionObj.value("date").toString();
        QString status = transactionObj.value("status").toString();

        storage_transaction.append(new Transaction(id,reader_id,librarian_id,document_id,date,status));
    }

    return true;
}


// SNAPSHOTS
QVector<Transaction*> ReportSnapshots::snapshot_by_date(const QVector<Transaction*>& transactions, const QString& start_date, const QString& end_date) {
    QDate start_d = QDate::fromString(start_date, "yyyy-MM-dd");
    QDate end_d = QDate::fromString(end_date, "yyyy-MM-dd");
    QVector<Transaction*> snapshot;

    for (Transaction* transaction : transactions) {
        QString date_string = transaction->get_date().left(10);
        QDate curr_date = QDate::fromString(date_string, "yyyy-MM-dd");
        if (curr_date >= start_d && curr_date <= end_d) {
            snapshot.append(transaction);
        }
    }

    return snapshot;
}

QVector<Transaction*> ReportSnapshots::snapshot_by_reader(const QVector<Transaction*>& transactions, const QString& reader_name) {
    QVector<Transaction*> snapshot;

    for (Transaction* transaction : transactions) {
        QString curr_reader_name = db_manager->get_user_by_id(transaction->get_reader_id())->get_name();
        if (curr_reader_name == reader_name) {
            snapshot.append(transaction);
        }
    }

    return snapshot;
}

QVector<Transaction*> ReportSnapshots::snapshot_by_librarian(const QVector<Transaction*>& transactions, const QString& librarian_name) {
    QVector<Transaction*> snapshot;

    for (Transaction* transaction : transactions) {
        QString curr_librarian_name = db_manager->get_user_by_id(transaction->get_librarian_id())->get_name();
        if (curr_librarian_name == librarian_name) {
            snapshot.append(transaction);
        }
    }

    return snapshot;
}

QVector<Transaction*> ReportSnapshots::snapshot_by_document_type(const QVector<Transaction*>& transactions, const QString& document_type) {
    QVector<Transaction*> snapshot;

    for (Transaction* transaction : transactions) {
        QString curr_document_type = db_manager->get_document_by_id(transaction->get_document_id())->get_type();
        if (curr_document_type == document_type) {
            snapshot.append(transaction);
        }
    }

    return snapshot;
}

QVector<Transaction*> ReportSnapshots::snapshot_by_document_author(const QVector<Transaction*>& transactions, const QString& document_author) {
    QVector<Transaction*> snapshot;

    for (Transaction* transaction : transactions) {
        QString curr_document_author = db_manager->get_document_by_id(transaction->get_document_id())->get_author();
        if (curr_document_author == document_author) {
            snapshot.append(transaction);
        }
    }

    return snapshot;
}



QVector<Transaction*> ReportSnapshots::snapshot_by_date_author(const QString& start_date,
                                                                const QString& end_date, const QString& document_author){
    load_transactions_from_json();
    QVector<Transaction*> snapshot;
    snapshot = snapshot_by_date(storage_transaction,start_date,end_date);
    snapshot = snapshot_by_document_author(snapshot,document_author);

    return snapshot;
}

QVector<Transaction*> ReportSnapshots::snapshot_by_date_type(const QString& start_date,
                                                                const QString& end_date, const QString& document_type){
    load_transactions_from_json();
    QVector<Transaction*> snapshot;
    snapshot = snapshot_by_date(storage_transaction,start_date,end_date);
    snapshot = snapshot_by_document_type(snapshot,document_type);

    return snapshot;
}


QVector<Transaction*> ReportSnapshots::snapshot_by_date_reader(const QString& start_date,
                                                              const QString& end_date, const QString& reader_name){
    load_transactions_from_json();
    QVector<Transaction*> snapshot;
    snapshot = snapshot_by_date(storage_transaction,start_date,end_date);
    snapshot = snapshot_by_reader(snapshot,reader_name);

    return snapshot;
}

QVector<Transaction*> ReportSnapshots::snapshot_by_date_librarian(const QString& start_date,
                                                                const QString& end_date, const QString& librarian_name){
    load_transactions_from_json();
    QVector<Transaction*> snapshot;
    snapshot = snapshot_by_date(storage_transaction,start_date,end_date);
    snapshot = snapshot_by_librarian(snapshot,librarian_name);

    return snapshot;
}


QVector<Transaction*> ReportSnapshots::snapshot_by_reader_type(const QString& reader_name, const QString& document_type){
    load_transactions_from_json();
    QVector<Transaction*> snapshot;
    snapshot = snapshot_by_reader(storage_transaction,reader_name);
    snapshot = snapshot_by_document_type(snapshot,document_type);

    return snapshot;
}


QVector<Transaction*> ReportSnapshots::snapshot_by_reader_author(const QString& reader_name, const QString& document_author){
    load_transactions_from_json();
    QVector<Transaction*> snapshot;
    snapshot = snapshot_by_reader(storage_transaction,reader_name);
    snapshot = snapshot_by_document_author(snapshot,document_author);

    return snapshot;
}


//SORTING TRANSACTIONS
QVector<Transaction*> ReportSnapshots::sort_by_popular_of_document(QVector<Transaction*> transactions) {
    QMap<int, int> doc_count;
    for (Transaction* t : transactions) {
        int doc_id = t->get_document_id();
        doc_count[doc_id]++;
    }

    std::sort(transactions.begin(), transactions.end(), [&](Transaction* a, Transaction* b) {
        int countA = doc_count[a->get_document_id()];
        int countB = doc_count[b->get_document_id()];

        if (countA != countB)
            return countA > countB;

        return a->get_document_id() < b->get_document_id();
    });

    return transactions;
}


QVector<Transaction*> ReportSnapshots::sort_by_reader_activity(QVector<Transaction*> transactions) {
    QMap<int, int> reader_count;
    for (Transaction* t : transactions) {
        int reader_id = t->get_reader_id();
        reader_count[reader_id]++;
    }

    std::sort(transactions.begin(), transactions.end(), [&](Transaction* a, Transaction* b) {
        int countA = reader_count[a->get_reader_id()];
        int countB = reader_count[b->get_reader_id()];

        if (countA != countB)
            return countA > countB;

        return a->get_reader_id() < b->get_reader_id();
    });

    return transactions;
}


QVector<Transaction*> ReportSnapshots::sort_by_librarian_activity(QVector<Transaction*> transactions) {
    QMap<int, int> librarian_count;
    for (Transaction* t : transactions) {
        int lib_id = t->get_librarian_id();
        librarian_count[lib_id]++;
    }

    std::sort(transactions.begin(), transactions.end(), [&](Transaction* a, Transaction* b) {
        int countA = librarian_count[a->get_librarian_id()];
        int countB = librarian_count[b->get_librarian_id()];

        if (countA != countB)
            return countA > countB;

        return a->get_librarian_id() < b->get_librarian_id();
    });

    return transactions;
}

