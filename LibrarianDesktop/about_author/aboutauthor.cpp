#include "aboutauthor.h"

AboutAuthor::AboutAuthor(QWidget *parent)
    : QWidget{parent}
{

    about_author_form = new QDialog(this);
    about_author_form->setWindowTitle("About author");
    about_author_form->resize(300, 200);

    QVBoxLayout* mainLayout = new QVBoxLayout(about_author_form);

    QLabel* author_name = new QLabel("Author name: Ivan Ilin");
    mainLayout->addWidget(author_name, 0, Qt::AlignHCenter);

    QLabel* author_photo = new QLabel();
    QPixmap pixmap(":/images/author_photo.jpg");

    if(pixmap.isNull()) {
        author_photo->setText("photo not found");
    } else {
        pixmap = pixmap.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        author_photo->setPixmap(pixmap);
    }

    mainLayout->addWidget(author_photo, 0, Qt::AlignHCenter);




}
