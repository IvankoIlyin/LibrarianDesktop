#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , db_manager(std::make_unique<DataBase_Manager>())
{
    ui->setupUi(this);
    table = new TableWidget(this, db_manager.get());

    ui->sort_id->setVisible(false);
    ui->sort_popular_of_document->setVisible(false);
    ui->sort_librarian_activity->setVisible(false);
    ui->sort_reader_activity->setVisible(false);
    ui->label->setVisible(false);

    ui->radioButton_transactions->setChecked(1);
    display_entity();
    ui->frame->setFrameShape(QFrame::Box);
    ui->frame->setFrameShadow(QFrame::Raised);
    ui->frame->setLineWidth(2);
    ui->frame->setMidLineWidth(1);



    layout = new QVBoxLayout(ui->frame);
    layout->setContentsMargins(5, 5, 5, 5);
    layout->setSpacing(0);

    layout->addWidget(table->table_widget);
    connect(ui->radioButton_users, &QRadioButton::clicked,this, &MainWindow::display_entity);
    connect(ui->radioButton_documets,&QRadioButton::clicked, this, &MainWindow::display_entity);
    connect(ui->radioButton_transactions,&QRadioButton::clicked, this, &MainWindow::display_entity);
    connect(ui->pushButton_create, &QPushButton::clicked, this, &MainWindow::create_entity);
    connect(ui->pushButton_upd_storage, &QPushButton::clicked, this, &MainWindow::update_storage);
    connect(ui->about_author_Button, &QPushButton::clicked, this, &MainWindow::about_author);

    connect(ui->sort_id, &QRadioButton::clicked, this, &MainWindow::set_sort_code);
    connect(ui->sort_popular_of_document, &QRadioButton::clicked, this, &MainWindow::set_sort_code);
    connect(ui->sort_librarian_activity, &QRadioButton::clicked, this, &MainWindow::set_sort_code);
    connect(ui->sort_reader_activity, &QRadioButton::clicked, this, &MainWindow::set_sort_code);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete table;
    layout = nullptr;
}

void MainWindow::display_entity(){
    if(ui->radioButton_users->isChecked()){
        table->display_users();
        ui->sort_id->setVisible(false);
        ui->sort_popular_of_document->setVisible(false);
        ui->sort_librarian_activity->setVisible(false);
        ui->sort_reader_activity->setVisible(false);
        ui->label->setVisible(false);
    }
    if(ui->radioButton_documets->isChecked()){
        table->display_documents();
        ui->sort_id->setVisible(false);
        ui->sort_popular_of_document->setVisible(false);
        ui->sort_librarian_activity->setVisible(false);
        ui->sort_reader_activity->setVisible(false);
        ui->label->setVisible(false);
    }
    if(ui->radioButton_transactions->isChecked()){
        table->display_transaction(sort_code);
        ui->sort_id->setVisible(true);
        ui->sort_popular_of_document->setVisible(true);
        ui->sort_librarian_activity->setVisible(true);
        ui->sort_reader_activity->setVisible(true);
        ui->label->setVisible(true);
    }
}


void MainWindow::create_entity() {
    if(ui->radioButton_users->isChecked()) {
        UserWidget* user_widget = new UserWidget(this, -1, db_manager.get());
        user_widget->user_form->setAttribute(Qt::WA_DeleteOnClose);
        connect(user_widget->user_form, &QDialog::finished,
                [this](int result) {
                    if(result == QDialog::Accepted) {
                        display_entity();
                    }
                });
        user_widget->user_form->open();
    }
    if(ui->radioButton_documets->isChecked()) {
        DocumentWidget* document_widget = new DocumentWidget(this, -1, db_manager.get());
        document_widget->document_form->setAttribute(Qt::WA_DeleteOnClose);
        connect(document_widget->document_form, &QDialog::finished,
                [this](int result) {
                    if(result == QDialog::Accepted) {
                        display_entity();
                    }
                });
        document_widget->document_form->open();
    }
    if(ui->radioButton_transactions->isChecked()) {
        TransactionWidget* transaction_widget = new TransactionWidget(this, -1, db_manager.get());
        transaction_widget->transaction_form->setAttribute(Qt::WA_DeleteOnClose);
        connect(transaction_widget->transaction_form, &QDialog::finished,
                [this](int result) {
                    if(result == QDialog::Accepted) {
                        display_entity();
                    }
                });
        transaction_widget->transaction_form->open();
    }
}

void MainWindow::update_storage(){
    ReportSnapshots* report = new ReportSnapshots(db_manager.get());
    report->load_transactions_from_json();
    report->saveTransactionsToJson();
    qDebug()<<"storage updated";
}


void MainWindow::about_author(){
    AboutAuthor* about_author = new AboutAuthor();
    about_author->about_author_form->setAttribute(Qt::WA_DeleteOnClose);
    about_author->about_author_form->open();
}

//0-id 1-popular_of_doc 2-reader_activity 3-librarian_activity
void MainWindow::set_sort_code(){
    if(ui->sort_id->isChecked()){sort_code=0;}
    if(ui->sort_popular_of_document->isChecked()){sort_code=1;}
    if(ui->sort_librarian_activity->isChecked()){sort_code=3;}
    if(ui->sort_reader_activity->isChecked()){sort_code=2;}
    table->display_transaction(sort_code);
}

