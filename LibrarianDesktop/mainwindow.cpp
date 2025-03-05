#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    table = new TableWidget(this);
    table->display_documents();
    ui->frame->setFrameShape(QFrame::Box);
    ui->frame->setFrameShadow(QFrame::Raised);
    ui->frame->setLineWidth(2);
    ui->frame->setMidLineWidth(1);

    layout = new QVBoxLayout(ui->frame);
    layout->setContentsMargins(5, 5, 5, 5);
    layout->setSpacing(0);

    layout->addWidget(table->table_widget);
    connect(ui->radioButton_users, &QRadioButton::clicked,this, &MainWindow::display_users);
    connect(ui->radioButton_documets,&QRadioButton::clicked, this, &MainWindow::display_documents);
    connect(ui->radioButton_transactions,&QRadioButton::clicked, this, &MainWindow::display_transactions);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::display_users() {
    table->display_users();
}

void MainWindow::display_documents() {
    table->display_documents();
}

void MainWindow::display_transactions() {
    table->display_transaction();
}





