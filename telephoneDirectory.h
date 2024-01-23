#include <string>
using namespace std;

#ifndef TELEDIR_H
#define TELEDIR_H

class Login{
    private:
        string username;
        string password;

    public:
        Login(string name, string pass):username(name), password(pass){}
        bool check_username();
        bool check_password();
};

class Role{
    protected:
        bool isAdmin;

    public:
        Role(bool admin):isAdmin(admin){};
        bool get_role();
};

class Permission : public Role{
    private:
        bool search;
        bool add;
        bool edit;
        bool del;

    public:
        Permission(bool);
        bool get_permission(string);
};

class User{
    private:
        string name;

    public:
        Permission per;
        Login login;
        User(string name, Permission per, Login login):name(name), per(per), login(login){}
        string get_name();
};

class PhoneNo{
    private:
        string areaCode;
        string number;

    public:
        PhoneNo(string ac = "", string num = ""):areaCode(ac), number(num){}
        string get_areaCode();
        string get_number();
};

class Name{
    private:
        string firstName;
        string lastName;

    public:
        Name(string fname = "", string lname = ""):firstName(fname), lastName(lname){}
        string get_firstName();
        string get_lastName();
};

class Address{
    private:
        string houseNo;
        string street;
        string area;
        string city;

    public:
        Address(string hno = "", string str = "", string area = "", string city = ""):houseNo(hno), street(str), area(area), city(city){}
        friend ostream & operator << (ostream &out, Address &add);
        string get_houseNo();
        string get_street();
        string get_area();
        string get_city();
};

class Directory{
    public:
        PhoneNo no;
        Name name;
        Address add;
        Directory(){}
        Directory(PhoneNo no, Name name, Address add):no(no), name(name), add(add){}
        Directory search_name(Name);
        Directory search_phoneNo(PhoneNo);
        int add_dir();
        int edit_dir();
        int delete_dir();
        friend ostream & operator << (ostream &out, Directory &dir);
};

#endif