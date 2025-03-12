#include "transactionwidget.h"

TransactionWidget::TransactionWidget(QWidget *parent, int id, DataBase_Manager* db_manager)
    : QWidget(parent)
    , isEditMode(id!=-1)
    , db_manager(db_manager)
{
    int reader_id=-1;
    int librarian_id=-1;
    int document_id=-1;
    QString date = "";
    QString status ="";
    if(isEditMode){
        Transaction* transaction = db_manager->get_transaction_by_id(id);
        reader_id = transaction->get_reader_id();
        librarian_id = transaction->get_librarian_id();
        document_id = transaction->get_document_id();
        date = transaction->get_date();
        status = transaction->get_status();
    }

    QVector<User*> users_list = db_manager->read_user_list();
    QVector<Document*> documents_list = db_manager->read_document_list();

    transaction_form = new QDialog(this);
    transaction_form->setWindowTitle(isEditMode ? "Edit Transaction" : "New Transaction");
    transaction_form->resize(300, 200);

    QVBoxLayout* mainLayout = new QVBoxLayout(transaction_form);
    QHBoxLayout* buttonsLayout = new QHBoxLayout();

    QPushButton* cancel_btn = new QPushButton("Cancel", transaction_form);
    QPushButton* ok_btn = new QPushButton(isEditMode ? "Save" : "Create", transaction_form);

    buttonsLayout->addStretch();
    buttonsLayout->addWidget(cancel_btn);
    buttonsLayout->addWidget(ok_btn);

    QFrame* fieldsFrame = new QFrame(transaction_form);

    QVBoxLayout* fieldsLayout = new QVBoxLayout(fieldsFrame);
    fieldsLayout->setContentsMargins(20, 20, 20, 20);
    fieldsLayout->setSpacing(15);

    QHBoxLayout* readerLayout = new QHBoxLayout();
    QLabel* reader_lbl = new QLabel("Reader:", fieldsFrame);
    reader_combo = new QComboBox(fieldsFrame);
    reader_combo->addItem("None");
    reader_combo->setCurrentIndex(0);
    for(int i=0;i<users_list.size();i++){
        if(users_list[i]->get_role()=="Reader"){reader_combo->addItem(users_list[i]->get_name());}
    }
    if(isEditMode){
        QString reader_name = db_manager->get_user_by_id(reader_id)->get_name();
        reader_combo->setCurrentText(reader_name);
    }
    readerLayout->addWidget(reader_lbl);
    readerLayout->addStretch();
    readerLayout->addWidget(reader_combo);

    QHBoxLayout* librarianLayout = new QHBoxLayout();
    QLabel* librarian_lbl = new QLabel("Librarian:", fieldsFrame);
    librarian_combo = new QComboBox(fieldsFrame);
    librarian_combo->addItem("None");
    librarian_combo->setCurrentIndex(0);
    for(int i=0;i<users_list.size();i++){
        if(users_list[i]->get_role()=="Librarian"){librarian_combo->addItem(users_list[i]->get_name());}
    }
    if(isEditMode){
        QString librarian_name = db_manager->get_user_by_id(librarian_id)->get_name();
        librarian_combo->setCurrentText(librarian_name);
    }
    librarianLayout->addWidget(librarian_lbl);
    librarianLayout->addStretch();
    librarianLayout->addWidget(librarian_combo);

    QHBoxLayout* documentLayout = new QHBoxLayout();
    QLabel* document_lbl = new QLabel("Document:", fieldsFrame);
    document_combo = new QComboBox(fieldsFrame);
    document_combo->addItem("None");
    document_combo->setCurrentIndex(0);
    for(int i=0;i<documents_list.size();i++){
        document_combo->addItem(documents_list[i]->get_title());
    }
    if(isEditMode){
        QString document_title = db_manager->get_document_by_id(document_id)->get_title();
        document_combo->setCurrentText(document_title);
    }
    documentLayout->addWidget(document_lbl);
    documentLayout->addStretch();
    documentLayout->addWidget(document_combo);


    QHBoxLayout* dateLayout = new QHBoxLayout();
    QLabel* date_lbl = new QLabel("Date:", fieldsFrame);
    date_edit = new QLineEdit(fieldsFrame);
    date_edit->setText(date);
    dateLayout->addWidget(date_lbl);
    dateLayout->addStretch();
    dateLayout->addWidget(date_edit);
    if(!isEditMode){
        date_edit->setEnabled(false);
    }


    QHBoxLayout* statusLayout = new QHBoxLayout();
    QLabel* status_lbl = new QLabel("Status:", fieldsFrame);
    status_combo = new QComboBox(fieldsFrame);
    status_combo->addItem("None");
    status_combo->addItem("Taken");
    status_combo->addItem("Returned");
    status_combo->addItem("Continued");
    status_combo->setCurrentIndex(0);

    if(isEditMode){
        status_combo->setCurrentText(status);
    }
    statusLayout->addWidget(status_lbl);
    statusLayout->addStretch();
    statusLayout->addWidget(status_combo);



    fieldsLayout->addLayout(readerLayout);
    fieldsLayout->addLayout(librarianLayout);
    fieldsLayout->addLayout(documentLayout);
    fieldsLayout->addLayout(dateLayout);
    fieldsLayout->addLayout(statusLayout);

    mainLayout->addLayout(fieldsLayout);
    mainLayout->addWidget(fieldsFrame);
    mainLayout->addLayout(buttonsLayout);

    connect(cancel_btn, &QPushButton::clicked, transaction_form, &QDialog::reject);
    if(isEditMode){
        connect(ok_btn, &QPushButton::clicked,
                std::bind(&TransactionWidget::save_transaction, this, id));
    }
    else{
         connect(ok_btn, &QPushButton::clicked, this, &TransactionWidget::create_transaction);
    }

}

void TransactionWidget::create_transaction(){
    QString reader_name = reader_combo->currentText();
    QString librarian_name = librarian_combo->currentText();
    QString document_title = document_combo->currentText();
    QString status = status_combo->currentText();

    if(reader_name=="None" || librarian_name=="None" ||document_title=="None" ||document_title=="None" || status=="None"){
        QMessageBox::warning(transaction_form, "Error", "Somethimg is empty");
        return;
    }

    int reader_id = db_manager->get_user_by_name(reader_name)->get_id();
    int librarian_id = db_manager->get_user_by_name(librarian_name)->get_id();
    int document_id = db_manager->get_document_by_title(document_title)->get_id();

    if (db_manager->create_transaction(reader_id,librarian_id,document_id,status)) {
        transaction_form->accept();
    } else {
        QMessageBox::critical(transaction_form, "Error",
                              "Failed to create transaction. Please try again.");
    }

}

void TransactionWidget::save_transaction(int id){
    QString reader_name = reader_combo->currentText();
    QString librarian_name = librarian_combo->currentText();
    QString document_title = document_combo->currentText();
    QString date = date_edit->text();
    QString status = status_combo->currentText();
    if(reader_name=="None" || librarian_name=="None" ||document_title=="None" || date.isEmpty() || document_title=="None" || status=="Name"){
        QMessageBox::warning(transaction_form, "Error", "Somethimg is empty");
        return;
    }

    int reader_id = db_manager->get_user_by_name(reader_name)->get_id();
    int librarian_id = db_manager->get_user_by_name(librarian_name)->get_id();
    int document_id = db_manager->get_document_by_title(document_title)->get_id();

    if (db_manager->update_transaction_by_id(id,reader_id,librarian_id,document_id,date,status)) {
        transaction_form->accept();
    } else {
        QMessageBox::critical(transaction_form, "Error",
                              "Failed to update transaction. Please try again.");
    }


}




