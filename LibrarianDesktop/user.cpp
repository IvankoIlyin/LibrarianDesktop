#include "user.h"

User::User(int _id, QString _name, QString _role) {
    this->id = _id;
    this->name = _name;
    this->role = _role;
}

int User::get_id(){
    return this->id;
}

QString User::get_name(){
    return this->name;
}

QString User::get_role(){
    return this->role;
}

void User::set_id(const int& _id){
    this->id = _id;
}

void User::set_name(const QString& _name){
    this->name = _name;
}

void User::set_role(const QString& _role){
    this->role = _role;
}
