#ifndef ABOUTAUTHOR_H
#define ABOUTAUTHOR_H

#include <QWidget>
#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include<QMessageBox>
#include <QComboBox>
#include<QPixmap>
#include<QFile>
class AboutAuthor : public QWidget
{
    Q_OBJECT
public:
    explicit AboutAuthor(QWidget *parent = nullptr);
     QDialog* about_author_form;

signals:
};

#endif // ABOUTAUTHOR_H
