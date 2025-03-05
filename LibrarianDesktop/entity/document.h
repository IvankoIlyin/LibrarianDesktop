#ifndef DOCUMENT_H
#define DOCUMENT_H
#include<QString>
class Document
{
private:
    int id;
    QString title;
    QString author;
    QString type;
public:
    Document(int _id,  QString _title, QString _author, QString _type);

    int get_id();
    QString get_title();
    QString get_author();
    QString get_type();

    void set_id(const int& _id);
    void set_title(const QString& _title);
    void set_author(const QString& _author);
    void set_type(const QString& _type);

    QString get_full_data();

};

#endif // DOCUMENT_H
