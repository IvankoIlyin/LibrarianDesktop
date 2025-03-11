#include "userwidget.h"

UserWidget::UserWidget(QWidget *parent, int id, DataBase_Manager* db_manager)
    : QWidget(parent)
    , isEditMode(id!=-1)
    , db_manager(db_manager)
{
    QString name="";
    QString role="";
    if(isEditMode){
        User* user = db_manager->get_user_by_id(id);
        name = user->get_name();
        role = user->get_role();
    }
    user_form = new QDialog(this);
    user_form->setWindowTitle(isEditMode ? "Edit User" : "New User");
    user_form->resize(300, 200);

    QVBoxLayout* mainLayout = new QVBoxLayout(user_form);
    QHBoxLayout* buttonsLayout = new QHBoxLayout();

    QPushButton* cancel_btn = new QPushButton("Cancel", user_form);
    QPushButton* ok_btn = new QPushButton(isEditMode ? "Save" : "Create", user_form);

    buttonsLayout->addStretch();
    buttonsLayout->addWidget(cancel_btn);
    buttonsLayout->addWidget(ok_btn);

    QFrame* fieldsFrame = new QFrame(user_form);

    QVBoxLayout* fieldsLayout = new QVBoxLayout(fieldsFrame);
    fieldsLayout->setContentsMargins(20, 20, 20, 20);
    fieldsLayout->setSpacing(15);

    QHBoxLayout* nameLayout = new QHBoxLayout();
    QLabel* name_lbl = new QLabel("Name:", fieldsFrame);
    name_edit = new QLineEdit(fieldsFrame);
    nameLayout->addWidget(name_lbl);
    nameLayout->addStretch();
    nameLayout->addWidget(name_edit);

    QHBoxLayout* roleLayout = new QHBoxLayout();
    QLabel* role_lbl = new QLabel("Role:", fieldsFrame);
    role_combo = new QComboBox(fieldsFrame);
    role_combo->addItem("Librarian");
    role_combo->addItem("Reader");
    role_combo->setCurrentIndex(0);

    roleLayout->addWidget(role_lbl);
    roleLayout->addStretch();
    roleLayout->addWidget(role_combo);

    fieldsLayout->addLayout(nameLayout);
    fieldsLayout->addLayout(roleLayout);

    mainLayout->addWidget(fieldsFrame);
    mainLayout->addLayout(buttonsLayout);

    connect(cancel_btn, &QPushButton::clicked, user_form, &QDialog::reject);
    if(isEditMode){
        connect(ok_btn, &QPushButton::clicked,
                std::bind(&UserWidget::save_user, this, id));
    }
    else{
        connect(ok_btn, &QPushButton::clicked, this, &UserWidget::create_user);
    }
}

void UserWidget::save_user(int id) {
    QString name = name_edit->text();
    QString role = role_combo->currentText();

    if (name.isEmpty()) {
        QMessageBox::warning(user_form, "Error", "Name cannot be empty");
        return;
    }

    if (db_manager->update_user_by_id(id, name, role)) {
        user_form->accept();
    } else {
        QMessageBox::critical(user_form, "Error",
                              "Failed to update user. Please try again.");
    }
}

void UserWidget::create_user() {
    QString name = name_edit->text();
    QString role = role_combo->currentText();

    if (name.isEmpty()) {
        QMessageBox::warning(user_form, "Error", "Name cannot be empty");
        return;
    }

    if (db_manager->create_user(name, role)) {
        user_form->accept();
    } else {
        QMessageBox::critical(user_form, "Error",
                              "Failed to create user. Please try again.");
    }
}
