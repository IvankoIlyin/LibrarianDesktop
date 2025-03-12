#ifndef TRANSACTIONWIDGET_H
#define TRANSACTIONWIDGET_H

#include <QWidget>
#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include<QMessageBox>
#include <QComboBox>
#include<QVector>
#include"database_manager.h"

class TransactionWidget : public QWidget
{
    Q_OBJECT

private:
    QComboBox* reader_combo;
    QComboBox* librarian_combo;
    QComboBox* document_combo;
    QComboBox* status_combo;
    QLineEdit* date_edit;
    bool isEditMode;
    std::shared_ptr<DataBase_Manager> db_manager;

public:
    QDialog* transaction_form;
    explicit TransactionWidget(QWidget *parent = nullptr, int id = -1,  DataBase_Manager* db_manager = nullptr);


private slots:
    void create_transaction();
    void save_transaction(int id);
};

#endif // TRANSACTIONWIDGET_H
