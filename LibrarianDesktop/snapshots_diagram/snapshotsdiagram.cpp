#include "snapshotsdiagram.h"

SnapshotsDiagram::SnapshotsDiagram(QWidget *parent, DataBase_Manager* db_manager)
    : QWidget{parent},
    db_manager(db_manager),
    diagram(nullptr)
{
    connect(this, &QObject::destroyed, this, [this]() {
        if (diagram) {
            diagram->deleteLater();
        }
    });
}

void SnapshotsDiagram::setup_line_diagram(QVector<Transaction*> transactions) {
    if (diagram == nullptr) {
        diagram = new QDialog(this);
        diagram->setWindowTitle("DIAGRAM");
        diagram->resize(700, 700);

        QVBoxLayout *layout = new QVBoxLayout(diagram);

        QChart *chart = new QChart();
        QLineSeries *series = new QLineSeries();

        QMap<QString, int> transactionsByDate;
        for (const auto& transaction : transactions) {
            QString date = transaction->get_date().left(10);
            transactionsByDate[date] = transactionsByDate.value(date, 0) + 1;
        }

        QStringList dates = transactionsByDate.keys();
        std::sort(dates.begin(), dates.end());

        for (const QString& date : dates) {
            QDateTime dt = QDateTime::fromString(date, "yyyy-MM-dd");
            if (dt.isValid()) {
                series->append(dt.toMSecsSinceEpoch(), transactionsByDate[date]);
            } else {
                qDebug() << "Datt not correct" << date;
            }
        }

        chart->addSeries(series);
        chart->createDefaultAxes();

        QDateTimeAxis *axisX = new QDateTimeAxis;
        axisX->setFormat("yyyy-MM-dd");
        axisX->setTitleText("Date");
        chart->setAxisX(axisX, series);

        QValueAxis *axisY = new QValueAxis;
        axisY->setLabelFormat("%i");
        axisY->setTitleText("Count of Transactions");
        chart->setAxisY(axisY, series);

        chart->setTitle("Count of Transactions per Date");
        chart->legend()->hide();

        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        layout->addWidget(chartView);
    }
}

void SnapshotsDiagram::setup_pie_diagram(QVector<Transaction*> transactions) {
    if (diagram == nullptr) {
        diagram = new QDialog(this);
        diagram->setWindowTitle("Типи документів");
        diagram->resize(700, 700);

        QVBoxLayout *layout = new QVBoxLayout(diagram);

        QChart *chart = new QChart();
        QPieSeries *series = new QPieSeries();

        QMap<QString, int> documentsByType;
        if (db_manager) {
            for (const auto& transaction : transactions) {
                const QString& type = db_manager->get_document_by_id(transaction->get_document_id())->get_type();
                documentsByType[type] = documentsByType.value(type, 0) + 1;
            }
        }

        for (auto it = documentsByType.constBegin(); it != documentsByType.constEnd(); ++it) {
            QPieSlice *slice = series->append(it.key(), it.value());
            slice->setLabelVisible(true);
            slice->setLabel(it.key() + "\n(" + QString::number(it.value()) + ")");
        }

        chart->addSeries(series);
        chart->setTitle("Documents by type");
        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);

        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        layout->addWidget(chartView);
    }

}

void SnapshotsDiagram::setup_transaction_by_weekday(QVector<Transaction*> transactions) {
    if (diagram == nullptr) {
        diagram = new QDialog(this);
        diagram->setWindowTitle("Document Distribution by Weekday");
        diagram->resize(700, 700);

        QVBoxLayout *layout = new QVBoxLayout(diagram);

        // Count of transactions for each day of the week (1=Monday, ..., 7=Sunday)
        QMap<int, int> weekdayCount;
        for (int i = 1; i <= 7; ++i) {
            weekdayCount[i] = 0;
        }

        for (const auto& transaction : transactions) {
            QString dateStr = transaction->get_date().left(10);
            QDate date = QDate::fromString(dateStr, "yyyy-MM-dd");

            if (date.isValid()) {
                int dayOfWeek = date.dayOfWeek();
                weekdayCount[dayOfWeek]++;
            }
        }

        QStringList dayNames = {
            "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"
        };

        QBarSet *set = new QBarSet("Number of Documents Taken");

        for (int i = 1; i <= 7; ++i) {
            *set << weekdayCount[i];
        }

        QBarSeries *series = new QBarSeries();
        series->append(set);

        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Distribution of Taken Documents by Day of the Week");
        chart->setAnimationOptions(QChart::SeriesAnimations);

        QBarCategoryAxis *axisX = new QBarCategoryAxis();
        axisX->append(dayNames);
        axisX->setTitleText("Weekday");
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);

        QValueAxis *axisY = new QValueAxis();
        axisY->setTitleText("Number of Documents");
        axisY->setLabelFormat("%i");
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);

        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        layout->addWidget(chartView);
    }

    diagram->show();
}

void SnapshotsDiagram::display_diagram(){
    diagram->show();
}
