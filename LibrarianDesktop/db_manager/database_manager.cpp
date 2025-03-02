// database_manager.cpp
#include "database_manager.h"

//CONSTRUCTOR
DataBase_Manager::DataBase_Manager() {
    QString executableDir = QCoreApplication::applicationDirPath();
    dbPath = executableDir + "/Library.db";

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);

    if (db.open()) {
        qDebug() << "Database connection successful";
    } else {
        qDebug() << "Database connection failed: " << db.lastError().text();
    }
    debugConnection();
    debugDatabase();
}

//DESTRUCTOR
DataBase_Manager::~DataBase_Manager() {
    db.close();
}

//TEST DB CONNECTION
void DataBase_Manager::debugDatabase() {
    if (!db.isOpen()) {
        qDebug() << "Database is not open";
        return;
    }

    QSqlQuery query(db);
    QString query1 = "PRAGMA database_list";
    if (!query.exec(query1)) {
        qDebug() << "Failed to get database list:" << query.lastError().text();
        return;
    }

    qDebug() << "\nAttached databases:";
    while (query.next()) {
        qDebug() << "- Name:" << query.value(1).toString()
        << ", File:" << query.value(2).toString();
    }

    QStringList schemas = {"main.", "temp.", ""};
    foreach(const QString& schema, schemas) {
        QString testQuery = QString("SELECT sql FROM %1sqlite_master WHERE type='table' AND name='Users'")
        .arg(schema);

        if (!query.exec(testQuery)) {
            qDebug() << "Failed to check schema '" << schema << "':"
                     << query.lastError().text();
            continue;
        }

        if (query.first()) {
            qDebug() << "\nFound Users table in schema '" << schema << "':";
            qDebug() << "- Table definition:" << query.value(0).toString();

            QString selectQuery = QString("SELECT * FROM %1Users LIMIT 1")
                                      .arg(schema);
            QSqlQuery dataQuery(db);
            if (!dataQuery.exec(selectQuery)) {
                qDebug() << "Failed to query Users table:"
                         << dataQuery.lastError().text();
            } else if (dataQuery.first()) {
                qDebug() << "- Successfully retrieved data";
            } else {
                qDebug() << "- Table exists but contains no data";
            }
        }
    }

    QString permQuery = "PRAGMA schema_version";
    if (!query.exec(permQuery)) {
        qDebug() << "\nPermission test failed:" << query.lastError().text();
    } else if (query.first()) {
        qDebug() << "- Schema version:" << query.value(0).toString();
    }
}

void DataBase_Manager::debugConnection() {
    if (!db.isOpen()) {
        qDebug() << "Database is not open";
        return;
    }

    qDebug() << "Database connection details:";
    qDebug() << "- Connection name:" << db.connectionName();
    qDebug() << "- Database name:" << db.databaseName();
    qDebug() << "- Driver name:" << db.driverName();

    QSqlQuery query(db);
    QString testQuery = "SELECT sql FROM sqlite_master WHERE type='table' AND name='Users'";
    if (!query.exec(testQuery)) {
        qDebug() << "Failed to execute query:" << query.lastError().text();
        return;
    }

    if (query.first()) {
        qDebug() << "Raw table definition:" << query.value(0).toString();
    } else {
        qDebug() << "Could not find Users table in sqlite_master";
    }
}

/*
.
...THERE CRUD OPERATION FOR LIBRARYb DATABASE...
.
*/

//CREATE
bool  DataBase_Manager::create_user(const QString& _name, const QString& _role){
    if (!db.isOpen()) {
        qDebug() << "Database is not open";
        return false;
    }

    QSqlQuery query(db);

    query.prepare("INSERT INTO users (name, role) VALUES (:name, :role)");

    query.bindValue(":name", _name);
    query.bindValue(":role", _role);

    if (!query.exec()) {
        qDebug() << "Failed to create user: " << query.lastError().text();
        return false;
    }

    return true;
}

bool DataBase_Manager::create_document(const QString& _title, const QString& _author,const QString& _type){
    if (!db.isOpen()) {
        qDebug() << "Database is not open";
        return false;
    }

    QSqlQuery query(db);

    query.prepare("INSERT INTO documents (title, author, document_type) VALUES (:title, :author, :document_type)");

    query.bindValue(":title", _title);
    query.bindValue(":author", _author);
    query.bindValue(":document_type", _type);

    if (!query.exec()) {
        qDebug() << "Failed to create user: " << query.lastError().text();
        return false;
    }

    return true;
}

bool DataBase_Manager::create_transaction(int reader_id, int librarian_id, int document_id, const QString& status) {
    if (!db.isOpen()) {
        qDebug() << "Database is not open";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("INSERT INTO transactions (reader_id, librarian_id, document_id, date ,status) "
                  "VALUES (:reader_id, :librarian_id, :document_id, :date, :status)");

    query.bindValue(":reader_id", reader_id);
    query.bindValue(":librarian_id", librarian_id);
    query.bindValue(":document_id", document_id);
    query.bindValue(":status", status);
    query.bindValue(":date", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));

    if (!query.exec()) {
        qDebug() << "Failed to create transaction: " << query.lastError().text();
        return false;
    }

    return true;
}

//READ
QVector<User*> DataBase_Manager::read_user_list() {
    QVector<User*> users;

    if (!db.isOpen()) {
        qDebug() << "Database is not open";
        return users;
    }

    QSqlQuery query(db);
    if (!query.exec("SELECT * FROM users")) {
        qDebug() << "Query failed: " << query.lastError().text();
        return users;
    }

    while (query.next()) {
        int id = query.value("id").toInt();
        QString name = query.value("name").toString();
        QString role = query.value("role").toString();
        users.append(new User(id, name, role));
    }
    return users;
}

QVector<Document*> DataBase_Manager::read_document_list() {
    QVector<Document*> documents;

    if (!db.isOpen()) {
        qDebug() << "Database is not open";
        return documents;
    }

    QSqlQuery query(db);
    if (!query.exec("SELECT * FROM documents")) {
        qDebug() << "Query failed: " << query.lastError().text();
        return documents;
    }

    while (query.next()) {
        int id = query.value("id").toInt();
        QString title = query.value("title").toString();
        QString author = query.value("author").toString();
        QString type = query.value("document_type").toString();
        documents.append(new Document(id, title, author, type));
    }
    return documents;
}

QVector<Transaction*> DataBase_Manager::read_transaction_list() {
    QVector<Transaction*> transactions;

    if (!db.isOpen()) {
        qDebug() << "Database is not open";
        return transactions;
    }

    QSqlQuery query(db);
    if (!query.exec("SELECT * FROM transactions")) {
        qDebug() << "Query failed: " << query.lastError().text();
        return transactions;
    }

    while (query.next()) {
        int id = query.value("id").toInt();
        int reader_id = query.value("reader_id").toInt();
        int librarian_id = query.value("librarian_id").toInt();
        int document_id = query.value("document_id").toInt();
        QString date = query.value("date").toString();
        QString status = query.value("status").toString();

        transactions.append(new Transaction(id, reader_id, librarian_id, document_id, date, status));
    }
    return transactions;
}

//UPDATE
bool DataBase_Manager::update_user_by_id(int id, const QString& name, const QString& role) {
    if (!db.isOpen()) {
        qDebug() << "Database is not open";
        return false;
    }

    QSqlQuery query(db);

    query.prepare("UPDATE users SET name = :name, role = :role WHERE id = :id");

    query.bindValue(":name", name);
    query.bindValue(":role", role);
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Failed to update user: " << query.lastError().text();
        return false;
    }

    return query.numRowsAffected() > 0;
}

bool DataBase_Manager::update_document_by_id(int id, const QString& title, const QString& author,const QString& type){
    if (!db.isOpen()) {
        qDebug() << "Database is not open";
        return false;
    }

    QSqlQuery query(db);

    query.prepare("UPDATE documents SET title = :title, author = :author, document_type = :type WHERE id = :id");

    query.bindValue(":title", title);
    query.bindValue(":author", author);
    query.bindValue(":type", type);
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Failed to update document: " << query.lastError().text();
        return false;
    }

    return query.numRowsAffected() > 0;
}

bool DataBase_Manager::update_transaction(int id, int reader_id, int librarian_id, int document_id, const QString& status) {
    if (!db.isOpen()) {
        qDebug() << "Database is not open";
        return false;
    }

    QSqlQuery query(db);

    query.prepare("UPDATE transactions SET reader_id = :reader_id, "
                  "librarian_id = :librarian_id, document_id = :document_id, "
                  "status = :status WHERE id = :id");

    query.bindValue(":reader_id", reader_id);
    query.bindValue(":librarian_id", librarian_id);
    query.bindValue(":document_id", document_id);
    query.bindValue(":status", status);
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Failed to update transaction: " << query.lastError().text();
        return false;
    }

    return query.numRowsAffected() > 0;
}

//DELETE
bool DataBase_Manager::delete_user_by_id(int id) {
    if (!db.isOpen()) {
        qDebug() << "Database is not open";
        return false;
    }

    QSqlQuery query(db);

    query.prepare("DELETE FROM users WHERE id = :id");

    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Failed to delete user: " << query.lastError().text();
        return false;
    }

    return query.numRowsAffected() > 0;
}

bool DataBase_Manager::delete_document_by_id(int id){
    if (!db.isOpen()) {
        qDebug() << "Database is not open";
        return false;
    }

    QSqlQuery query(db);

    query.prepare("DELETE FROM documents WHERE id = :id");

    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Failed to delete document: " << query.lastError().text();
        return false;
    }

    return query.numRowsAffected() > 0;
}

bool DataBase_Manager::delete_transaction(int id) {
    if (!db.isOpen()) {
        qDebug() << "Database is not open";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("DELETE FROM transactions WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Failed to delete transaction: " << query.lastError().text();
        return false;
    }

    return true;
}

//GET BY ID
User* DataBase_Manager::get_user_by_id(int id){
    if (!db.isOpen()) {
        qDebug() << "Database is not open";
        return nullptr;
    }

    QSqlQuery query(db);

    query.prepare("SELECT id, name, role FROM users WHERE id = :id");

    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Failed to get user: " << query.lastError().text();
        return nullptr;
    }

    if (!query.next()) {
        return nullptr;
    }

    int userId = query.value("id").toInt();
    QString name = query.value("name").toString();
    QString role = query.value("role").toString();

    return new User(userId, name, role);
}

Document* DataBase_Manager::get_document_by_id(int id){
    if (!db.isOpen()) {
        qDebug() << "Database is not open";
        return nullptr;
    }

    QSqlQuery query(db);

    query.prepare("SELECT id, title, author, document_type FROM documents WHERE id = :id");

    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Failed to get document: " << query.lastError().text();
        return nullptr;
    }

    if (!query.next()) {
        return nullptr;
    }

    int documentId = query.value("id").toInt();
    QString title = query.value("title").toString();
    QString author = query.value("author").toString();
    QString type = query.value("document_type").toString();


    return new Document(documentId, title, author,type);
}

Transaction* DataBase_Manager::get_transaction_by_id(int id) {
    if (!db.isOpen()) {
        qDebug() << "Database is not open";
        return nullptr;
    }

    QSqlQuery query(db);
    query.prepare("SELECT * FROM transactions WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Failed to get transaction: " << query.lastError().text();
        return nullptr;
    }

    if (!query.next()) {
        return nullptr;
    }

    int transactionId = query.value("id").toInt();
    int reader_id = query.value("reader_id").toInt();
    int librarian_id = query.value("librarian_id").toInt();
    int document_id = query.value("document_id").toInt();
    QString date = query.value("date").toString();
    QString status = query.value("status").toString();

    return new Transaction(transactionId, reader_id, librarian_id, document_id, date, status);
}

// GET USER BY NAME
User* DataBase_Manager::get_user_by_name(const QString& name){
    if (!db.isOpen()) {
        qDebug() << "Database is not open";
        return nullptr;
    }

    QSqlQuery query(db);

    query.prepare("SELECT id, name, role FROM users WHERE name = :name");

    query.bindValue(":name", name);

    if (!query.exec()) {
        qDebug() << "Failed to get user: " << query.lastError().text();
        return nullptr;
    }

    if (!query.next()) {
        return nullptr;
    }

    int userId = query.value("id").toInt();
    QString userName = query.value("name").toString();
    QString role = query.value("role").toString();

    return new User(userId, userName, role);
}


//GET USERS BY ROLE
QVector<User*> DataBase_Manager::get_users_by_role(const QString& role){
    QVector<User*> users;

    if (!db.isOpen()) {
        qDebug() << "Database is not open";
        return users;
    }

    QSqlQuery query(db);

    query.prepare("SELECT id, name, role FROM users WHERE role = :role");

    query.bindValue(":role", role);

    if (!query.exec()) {
        qDebug() << "Failed to get users: " << query.lastError().text();
        return users;
    }

    while (query.next()) {
        int userId = query.value("id").toInt();
        QString userName = query.value("name").toString();
        QString userRole = query.value("role").toString();

        users.append(new User(userId, userName, userRole));
    }

    return users;
}


//GET DOCUMENT BY TITLE
Document* DataBase_Manager::get_document_by_title(const QString& title) {
    if (!db.isOpen()) {
        qDebug() << "Database is not open";
        return nullptr;
    }

    QSqlQuery query(db);

    query.prepare("SELECT id, title, author, document_type FROM documents WHERE title = :title");

    query.bindValue(":title", title);

    if (!query.exec()) {
        qDebug() << "Failed to get document: " << query.lastError().text();
        return nullptr;
    }

    if (!query.next()) {
        return nullptr;
    }

    int documentId = query.value("id").toInt();
    QString documentTitle = query.value("title").toString();
    QString author = query.value("author").toString();
    QString type = query.value("document_type").toString();

    return new Document(documentId, documentTitle, author, type);
}


//GET DOCUMENTS BY AUTHOR
QVector<Document*> DataBase_Manager::get_documents_by_author(const QString& author) {
    QVector<Document*> documents;

    if (!db.isOpen()) {
        qDebug() << "Database is not open";
        return documents;
    }

    QSqlQuery query(db);

    query.prepare("SELECT id, title, author, document_type FROM documents WHERE author = :author");

    query.bindValue(":author", author);

    if (!query.exec()) {
        qDebug() << "Failed to get documents: " << query.lastError().text();
        return documents;
    }

    while (query.next()) {
        int documentId = query.value("id").toInt();
        QString title = query.value("title").toString();
        QString docAuthor = query.value("author").toString();
        QString type = query.value("document_type").toString();

        documents.append(new Document(documentId, title, docAuthor, type));
    }

    return documents;
}


//GET DOCUMENTS BY TYPE
QVector<Document*> DataBase_Manager::get_documents_by_type(const QString& type) {
    QVector<Document*> documents;

    if (!db.isOpen()) {
        qDebug() << "Database is not open";
        return documents;
    }

    QSqlQuery query(db);

    query.prepare("SELECT id, title, author, document_type FROM documents WHERE document_type = :type");

    query.bindValue(":type", type);

    if (!query.exec()) {
        qDebug() << "Failed to get documents: " << query.lastError().text();
        return documents;
    }

    while (query.next()) {
        int documentId = query.value("id").toInt();
        QString title = query.value("title").toString();
        QString author = query.value("author").toString();
        QString docType = query.value("document_type").toString();

        documents.append(new Document(documentId, title, author, docType));
    }

    return documents;
}


//GET TRANSACTIONS BY READER_ID
QVector<Transaction*> DataBase_Manager::get_transactions_by_reader_id(int reader_id) {
    QVector<Transaction*> transactions;

    if (!db.isOpen()) {
        qDebug() << "Database is not open";
        return transactions;
    }

    QSqlQuery query(db);

    query.prepare("SELECT id, reader_id, librarian_id, document_id, date, status "
                  "FROM transactions WHERE reader_id = :reader_id");

    query.bindValue(":reader_id", reader_id);

    if (!query.exec()) {
        qDebug() << "Failed to get transactions: " << query.lastError().text();
        return transactions;
    }

    while (query.next()) {
        int id = query.value("id").toInt();
        int transaction_reader_id = query.value("reader_id").toInt();
        int librarian_id = query.value("librarian_id").toInt();
        int document_id = query.value("document_id").toInt();
        QString date = query.value("date").toString();
        QString status = query.value("status").toString();

        transactions.append(new Transaction(id, transaction_reader_id, librarian_id,
                                            document_id, date, status));
    }

    return transactions;
}


//GET TRANSACTIONS BY LIBRARIAN_ID
QVector<Transaction*> DataBase_Manager::get_transactions_by_librarian_id(int librarian_id) {
    QVector<Transaction*> transactions;

    if (!db.isOpen()) {
        qDebug() << "Database is not open";
        return transactions;
    }

    QSqlQuery query(db);

    query.prepare("SELECT id, reader_id, librarian_id, document_id, date, status "
                  "FROM transactions WHERE librarian_id = :librarian_id");

    query.bindValue(":librarian_id", librarian_id);

    if (!query.exec()) {
        qDebug() << "Failed to get transactions: " << query.lastError().text();
        return transactions;
    }

    while (query.next()) {
        int id = query.value("id").toInt();
        int reader_id = query.value("reader_id").toInt();
        int transaction_librarian_id = query.value("librarian_id").toInt();
        int document_id = query.value("document_id").toInt();
        QString date = query.value("date").toString();
        QString status = query.value("status").toString();

        transactions.append(new Transaction(id, reader_id, transaction_librarian_id,
                                            document_id,date, status));
    }

    return transactions;
}


//GET TRANSACTIONS BY DOCUMENT_ID
QVector<Transaction*> DataBase_Manager::get_transactions_by_document_id(int document_id) {
    QVector<Transaction*> transactions;

    if (!db.isOpen()) {
        qDebug() << "Database is not open";
        return transactions;
    }

    QSqlQuery query(db);

    query.prepare("SELECT id, reader_id, librarian_id, document_id, date, status "
                  "FROM transactions WHERE document_id = :document_id");

    query.bindValue(":document_id", document_id);

    if (!query.exec()) {
        qDebug() << "Failed to get transactions: " << query.lastError().text();
        return transactions;
    }

    while (query.next()) {
        int id = query.value("id").toInt();
        int reader_id = query.value("reader_id").toInt();
        int librarian_id = query.value("librarian_id").toInt();
        int transaction_document_id = query.value("document_id").toInt();
        QString date = query.value("date").toString();
        QString status = query.value("status").toString();

        transactions.append(new Transaction(id, reader_id, librarian_id,
                                            transaction_document_id,date, status));
    }

    return transactions;
}


//GET TRANSACTIONS BY DATE
QVector<Transaction*> DataBase_Manager::get_transactions_by_date(const QString& date) {
    QVector<Transaction*> transactions;

    if (!db.isOpen()) {
        qDebug() << "Database is not open";
        return transactions;
    }

    QSqlQuery query(db);

    query.prepare("SELECT id, reader_id, librarian_id, document_id, date, status "
                  "FROM transactions WHERE date = :date");

    query.bindValue(":date", date);

    if (!query.exec()) {
        qDebug() << "Failed to get transactions: " << query.lastError().text();
        return transactions;
    }

    while (query.next()) {
        int id = query.value("id").toInt();
        int reader_id = query.value("reader_id").toInt();
        int librarian_id = query.value("librarian_id").toInt();
        int document_id = query.value("document_id").toInt();
        QString transaction_date = query.value("date").toString();
        QString status = query.value("status").toString();

        transactions.append(new Transaction(id, reader_id, librarian_id,
                                            document_id, transaction_date, status));
    }

    return transactions;
}


//GET TRANSACTIONS BY STATUS
QVector<Transaction*> DataBase_Manager::get_transactions_by_status(const QString& status) {
    QVector<Transaction*> transactions;

    if (!db.isOpen()) {
        qDebug() << "Database is not open";
        return transactions;
    }

    QSqlQuery query(db);

    query.prepare("SELECT id, reader_id, librarian_id, document_id, date, status "
                  "FROM transactions WHERE status = :status");

    query.bindValue(":status", status);

    if (!query.exec()) {
        qDebug() << "Failed to get transactions: " << query.lastError().text();
        return transactions;
    }

    while (query.next()) {
        int id = query.value("id").toInt();
        int reader_id = query.value("reader_id").toInt();
        int librarian_id = query.value("librarian_id").toInt();
        int document_id = query.value("document_id").toInt();
        QString date = query.value("date").toString();
        QString transaction_status = query.value("status").toString();

        transactions.append(new Transaction(id, reader_id, librarian_id,
                                            document_id,date, transaction_status));
    }

    return transactions;
}
