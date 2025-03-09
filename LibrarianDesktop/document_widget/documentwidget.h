#ifndef DOCUMENTWIDGET_H
#define DOCUMENTWIDGET_H

#include <QWidget>
#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include "database_manager.h"

class DocumentWidget : public QWidget
{
    Q_OBJECT

private:
    QLineEdit* title_edit;
    QLineEdit* author_edit;
    QLineEdit* type_edit;
    bool isEditMode;
    std::shared_ptr<DataBase_Manager> db_manager;

public:
    QDialog* document_form;
    explicit DocumentWidget(QWidget *parent = nullptr, int id = -1, DataBase_Manager* db_manager = nullptr);

private slots:
    void save_document(int id);
    void create_document();
};

#endif // DOCUMENTWIDGET_H
