#include "documentwidget.h"

DocumentWidget::DocumentWidget(QWidget *parent, int id,  DataBase_Manager* db_manager)
    : QWidget(parent)
    , isEditMode(id != -1)
    , db_manager(db_manager)
{
    QString title = "";
    QString author = "";
    QString type = "";

    if (isEditMode) {
        Document* doc = db_manager->get_document_by_id(id);
        if (doc) {
            title = doc->get_title();
            author = doc->get_author();
            type = doc->get_type();
        } else {
            QMessageBox::critical(this, "Error",
                                  "Document not found with ID: " + QString::number(id));
            return;
        }
    }

    document_form = new QDialog(this);
    document_form->setWindowTitle(isEditMode ? "Edit Document" : "New Document");
    document_form->resize(300, 250);

    QVBoxLayout* mainLayout = new QVBoxLayout(document_form);
    QHBoxLayout* buttonsLayout = new QHBoxLayout();

    QPushButton* cancel_btn = new QPushButton("Cancel", document_form);
    QPushButton* ok_btn = new QPushButton(isEditMode ? "Save" : "Create", document_form);

    buttonsLayout->addStretch();
    buttonsLayout->addWidget(cancel_btn);
    buttonsLayout->addWidget(ok_btn);

    QFrame* fieldsFrame = new QFrame(document_form);

    QVBoxLayout* fieldsLayout = new QVBoxLayout(fieldsFrame);
    fieldsLayout->setContentsMargins(20, 20, 20, 20);
    fieldsLayout->setSpacing(15);

    QHBoxLayout* titleLayout = new QHBoxLayout();
    QLabel* title_lbl = new QLabel("Title:", fieldsFrame);
    title_edit = new QLineEdit(fieldsFrame);
    title_edit->setText(title);
    titleLayout->addWidget(title_lbl);
    titleLayout->addStretch();
    titleLayout->addWidget(title_edit);

    QHBoxLayout* authorLayout = new QHBoxLayout();
    QLabel* author_lbl = new QLabel("Author:", fieldsFrame);
    author_edit = new QLineEdit(fieldsFrame);
    author_edit->setText(author);
    authorLayout->addWidget(author_lbl);
    authorLayout->addStretch();
    authorLayout->addWidget(author_edit);

    QHBoxLayout* typeLayout = new QHBoxLayout();
    QLabel* type_lbl = new QLabel("Type:", fieldsFrame);
    type_edit = new QLineEdit(fieldsFrame);
    type_edit->setText(type);
    typeLayout->addWidget(type_lbl);
    typeLayout->addStretch();
    typeLayout->addWidget(type_edit);

    fieldsLayout->addLayout(titleLayout);
    fieldsLayout->addLayout(authorLayout);
    fieldsLayout->addLayout(typeLayout);

    mainLayout->addWidget(fieldsFrame);
    mainLayout->addStretch();
    mainLayout->addLayout(buttonsLayout);

    connect(cancel_btn, &QPushButton::clicked, document_form, &QDialog::reject);
    if(isEditMode) {
        connect(ok_btn, &QPushButton::clicked,
                std::bind(&DocumentWidget::save_document, this, id));
    }
    else {
        connect(ok_btn, &QPushButton::clicked, this, &DocumentWidget::create_document);
    }
}

void DocumentWidget::save_document(int id) {
    QString title = title_edit->text();
    QString author = author_edit->text();
    QString type = type_edit->text();

    if (title.isEmpty()) {
        QMessageBox::warning(document_form, "Error", "Title cannot be empty");
        return;
    }

    if (author.isEmpty()) {
        QMessageBox::warning(document_form, "Error", "Author cannot be empty");
        return;
    }

    if (type.isEmpty()) {
        QMessageBox::warning(document_form, "Error", "Type cannot be empty");
        return;
    }


    if (db_manager->update_document_by_id(id, title, author, type)) {
        document_form->accept();
    } else {
        QMessageBox::critical(document_form, "Error",
                              "Failed to update document. Please try again.");
    }
}

void DocumentWidget::create_document() {
    QString title = title_edit->text();
    QString author = author_edit->text();
    QString type = type_edit->text();

    if (title.isEmpty()) {
        QMessageBox::warning(document_form, "Error", "Title cannot be empty");
        return;
    }

    if (author.isEmpty()) {
        QMessageBox::warning(document_form, "Error", "Author cannot be empty");
        return;
    }

    if (type.isEmpty()) {
        QMessageBox::warning(document_form, "Error", "Type cannot be empty");
        return;
    }

    if (db_manager->create_document(title, author, type)) {
        document_form->accept();
    } else {
        QMessageBox::critical(document_form, "Error",
                              "Failed to create document. Please try again.");
    }
}
