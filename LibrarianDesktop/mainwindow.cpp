#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , db_manager(std::make_unique<DataBase_Manager>())
{
    ui->setupUi(this);
    table = new TableWidget(this, db_manager.get());

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
    }
    if(ui->radioButton_documets->isChecked()){
        table->display_documents();
    }
    if(ui->radioButton_transactions->isChecked()){
        table->display_transaction();
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

