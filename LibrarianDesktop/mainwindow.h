#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include"table_widget/tablewidget.h"
#include"user_widget/userwidget.h"
#include"document_widget/documentwidget.h"
#include"transaction_widget/transactionwidget.h"
#include"report_snapshots/reportsnapshots.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void display_entity();
    void create_entity();
    void update_storage();

private:
    TableWidget* table;
    QVBoxLayout* layout;
    std::unique_ptr<DataBase_Manager> db_manager;
    Ui::MainWindow *ui;
};




#endif // MAINWINDOW_H
