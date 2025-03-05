#ifndef USER_H
#define USER_H
#include<QString>
class User
{
private:
    int id;
    QString name;
    QString role;

public:
    User(int _id, QString _name, QString _role);

    int get_id();
    QString get_name();
    QString get_role();

    void set_id(const int& _id);
    void set_name(const QString& _name);
    void set_role(const QString& _role);

    QString get_full_data();

};

#endif // USER_H
