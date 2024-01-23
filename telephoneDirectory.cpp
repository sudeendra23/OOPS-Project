#include <iostream>
#include <fstream>
#include "telephoneDirectory.h"
using namespace std;

bool Login::check_username(){
    int flag = 0;
    string uname, temp;
    fstream data;
    data.open("accounts.txt", ios::in);
    data >> uname >> temp >> temp >> temp;
    while (!data.eof()){
        if (uname == username){
            flag = 1;
            break;
        }
        data >> uname >> temp >> temp >> temp;
    }
    data.close();
    return flag == 1 ? true : false;
}

bool Login::check_password(){
    int flag = 0;
    string uname, pass, temp;
    fstream data;
    data.open("accounts.txt", ios::in);
    data >> uname >> pass >> temp >> temp;
    while (!data.eof()){
        if (uname == username && pass == password){
            flag = 1;
            break;
        }
        data >> uname >> pass >> temp >> temp;
    }
    data.close();
    return flag == 1 ? true : false;
}

bool Role::get_role(){
    return isAdmin;
}

Permission::Permission(bool admin):Role(admin){
    search = true;
    if (admin == true){
        add = true;
        edit = true;
        del = true;
    }
    else{
        add = false;
        edit = false;
        del = false;
    }
}

bool Permission::get_permission(string s){
    switch (s[0]){
        case 's':
            return search;
        case 'a':
            return add;
        case 'e':
            return edit;
        case 'd':
            return del;
    }
    return false;
}

string User::get_name(){
    return name;
}

string PhoneNo::get_areaCode(){
    return areaCode;
}

string PhoneNo::get_number(){
    return number;
}

string Name::get_firstName(){
    return firstName;
}

string Name::get_lastName(){
    return lastName;
}

ostream & operator << (ostream &out, Address &add){
    cout << "Hno " << add.houseNo << ", " << add.street << " street, " << add.area << ", " << add.city << endl;
    return out;
}

string Address::get_houseNo(){
    return houseNo;
}

string Address::get_street(){
    return street;
}

string Address::get_area(){
    return area;
}

string Address::get_city(){
    return city;
}

Directory Directory::search_name(Name name){
    int flag = 0;
    string fname, lname, acode, num, hno, str, area, city;
    fstream data;
    data.open("directory.txt", ios::in);
    data >> fname >> lname >> acode >> num >> hno >> str >> area >> city;
    while (!data.eof()){
        if (fname == name.get_firstName() && lname == name.get_lastName()){
            flag = 1;
            break;
        }
        data >> fname >> lname >> acode >> num >> hno >> str >> area >> city;
    }
    data.close();
    if (flag == 0){
        num = "";
    }
    PhoneNo no(acode, num);
    Address add(hno, str, area, city);
    Directory dir(no, name, add);
    return dir;
}

Directory Directory::search_phoneNo(PhoneNo no){
    int flag = 0;
    string fname, lname, acode, num, hno, str, area, city;
    fstream data;
    data.open("directory.txt", ios::in);
    data >> fname >> lname >> acode >> num >> hno >> str >> area >> city;
    while (!data.eof()){
        if (acode == no.get_areaCode() && num == no.get_number()){
            flag = 1;
            break;
        }
        data >> fname >> lname >> acode >> num >> hno >> str >> area >> city;
    }
    data.close();
    if (flag == 0){
        fname = "";
    }
    Name name(fname, lname);
    Address add(hno, str, area, city);
    Directory dir(no, name, add);
    return dir;
}

int Directory::add_dir(){
    int flag = 1;
    string fname, lname, acode, num, hno, str, area, city;
    fstream data;
    data.open("directory.txt", ios::in);
    data >> fname >> lname >> acode >> num >> hno >> str >> area >> city;
    while (!data.eof()){
        if (fname == name.get_firstName() && lname == name.get_lastName() || acode == no.get_areaCode() && num == no.get_number()){
            flag = 0;
            break;
        }
        data >> fname >> lname >> acode >> num >> hno >> str >> area >> city;
    }
    data.close();
    if (flag == 1){
        data.open("directory.txt", ios::app|ios::out);
        data << name.get_firstName() << " " << name.get_lastName() << " " << no.get_areaCode() << " " << no.get_number() << " " << add.get_houseNo() << " " << add.get_street() << " " << add.get_area() << " " << add.get_city() << "\n";
    }
    return flag;
}

int Directory::edit_dir(){
    int flag = 0;
    string fname, lname, acode, num, hno, str, area, city;
    fstream data, data1;
    data.open("directory.txt", ios::in);
    data1.open("newdirectory.txt", ios::app|ios::out);
    data >> fname >> lname >> acode >> num >> hno >> str >> area >> city;
    while (!data.eof()){
        if (fname == name.get_firstName() && lname == name.get_lastName()){
            string fname1, lname1, acode1, num1, hno1, str1, area1, city1;
            cout << "\nEnter New First Name: ";
            cin >> fname1;
            cout << "Enter New Last Name: ";
            cin >> lname1;
            cout << "Enter New Area Code: ";
            cin >> acode1;
            cout << "Enter New Phone Number: ";
            cin >> num1;
            cout << "Enter New House Number: ";
            cin >> hno1;
            cout << "Enter New Street: ";
            cin >> str1;
            cout << "Enter New Area: ";
            cin >> area1;
            cout << "Enter New City: ";
            cin >> city1;
            data1 << fname1 << " " << lname1 << " " << acode1 << " " << num1 << " " << hno1 << " " <<  str1 << " " << area1 << " " << city1 << "\n";
            flag = 1;
        }
        else{
            data1 << fname << " " << lname << " " << acode << " " << num << " " << hno << " " <<  str << " " << area << " " << city << "\n";
        }
        data >> fname >> lname >> acode >> num >> hno >> str >> area >> city;
    }
    data.close();
    data1.close();
    remove("directory.txt");
    rename("newdirectory.txt", "directory.txt");
    return flag;
}

int Directory::delete_dir(){
    int flag = 0;
    string fname, lname, acode, num, hno, str, area, city;
    fstream data, data1;
    data.open("directory.txt", ios::in);
    data1.open("newdirectory.txt", ios::app|ios::out);
    data >> fname >> lname >> acode >> num >> hno >> str >> area >> city;
    while (!data.eof()){
        if (fname == name.get_firstName() && lname == name.get_lastName()){
            flag = 1;
        }
        else{
            data1 << fname << " " << lname << " " << acode << " " << num << " " << hno << " " <<  str << " " << area << " " << city << "\n";
        }
        data >> fname >> lname >> acode >> num >> hno >> str >> area >> city;
    }
    data.close();
    data1.close();
    remove("directory.txt");
    rename("newdirectory.txt", "directory.txt");
    return flag;
}

ostream & operator << (ostream &out, Directory &dir){
    out << "First Name: " << dir.name.get_firstName() << "\n";
    out << "Last Name: " << dir.name.get_lastName() << "\n";
    out << "Telephone Number: " << dir.no.get_areaCode() << "-" << dir.no.get_number() << "\n";
    out << "Address: " << dir.add << "\n";
    return out;
}