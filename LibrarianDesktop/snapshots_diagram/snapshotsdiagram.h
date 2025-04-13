#ifndef SNAPSHOTSDIAGRAM_H
#define SNAPSHOTSDIAGRAM_H

#include <QWidget>
#include <QVector>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>
#include <QVBoxLayout>
#include <QDialog>
#include <QValueAxis>
#include <QDateTimeAxis>
#include <QPieSeries>
#include <QBarSet>
#include <QBarSeries>
#include <QBarCategoryAxis>
#include"../entity/transaction.h"
#include"../db_manager/database_manager.h"

class SnapshotsDiagram : public QWidget
{
    Q_OBJECT
private:
    DataBase_Manager* db_manager;
    QDialog *diagram;

public:
    explicit SnapshotsDiagram(QWidget *parent, DataBase_Manager* db_manager = nullptr);

    void setup_line_diagram(QVector<Transaction*> transactions);
    void setup_pie_diagram(QVector<Transaction*> transactions);
    void setup_transaction_by_weekday(QVector<Transaction*> transactions);

    void display_diagram();

signals:
};

#endif // SNAPSHOTSDIAGRAM_H
