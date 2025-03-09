#ifndef USERWIDGET_H
#define USERWIDGET_H

#include <QWidget>
#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include<QMessageBox>
#include"database_manager.h"

class UserWidget : public QWidget
{
    Q_OBJECT

private:
    QLineEdit* name_edit;
    QLineEdit* role_edit;
    bool isEditMode;
    std::shared_ptr<DataBase_Manager> db_manager;
public:
    QDialog* user_form;
    explicit UserWidget(QWidget *parent = nullptr, int id = -1,  DataBase_Manager* db_manager = nullptr);

private slots:
    void save_user(int id);
    void create_user();
};

#endif // USERWIDGET_H
