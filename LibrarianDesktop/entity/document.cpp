#include "document.h"

Document::Document(int _id,  QString _title, QString _author, QString _type) {
    this->id =_id;
    this->title = _title;
    this->author = _author;
    this->type = _type;
}

int Document::get_id(){
    return this->id;
}

QString Document::get_title(){
    return this->title;
}

QString Document::get_author(){
    return this->author;
}

QString Document::get_type(){
    return this->type;
}

void Document::set_id(const int& _id){
    this->id = _id;
}

void Document::set_title(const QString& _title){
    this->title = _title;
}

void Document::set_author(const QString& _author){
    this->author = _author;
}

void Document::set_type(const QString& _type){
    this->type = _type;
}

QString Document::get_full_data(){
    return QString::number(id) +" - " + title + " - " + author+ " - " + type;
}
