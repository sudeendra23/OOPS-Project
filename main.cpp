#include <iostream>
#include <fstream>
#include "telephoneDirectory.h"
#include "telephoneDirectory.cpp"
using namespace std;

int main(){
    fstream data;
    char choice;
    string username;
    string password;

    start:
    system("cls");
    cout << "\n\n\t\t-----------TELEPHONE DIRECTORY-------------\n\n";
	cout << "Please Sign-In or Sign-Up to Continue\n\n";
    cout << "\t1.  Sign-In to an Existing Account\n";
    cout << "\t2.  Create a New Account\n";
    cout << "\t3.  Exit\n";
	cout << "\nPlease Enter Your Choice: ";
    cin >> choice;
    
    switch (choice){
        case '1':{
            signin:
            system("cls");
            cout << "\n\n\t\t-----------TELEPHONE DIRECTORY-------------\n\n";
            cout << "Please Enter Your Username: ";
            cin >> username;
            cout << "Please Enter Your Password: ";
            cin >> password;
            Login login(username, password);
            if (login.check_username() && login.check_password()){
                cout << "\nLogin Successful\n";
                system("pause");
                break;
            }
            else{
                cout << "\n\nIncorrect Username or Password";
                incorrect:
		        cout << "\nPress   <1> To Sign-Up    OR\n        <2> To Sign-In Again\n";
                cin >> choice;
                if (choice == '1'){
                    goto signup;
                }
                else if (choice == '2'){
                    goto signin;
                }
                else{
                    cout << "\nInvalid Entry\n";
                    cout << "Enter Again\n";
                    goto incorrect;
                }
            }
        }
        case '2':{
            signup:
            system("cls");
	        cout << "\n\n\t\t-----------TELEPHONE DIRECTORY-------------\n\n";
            cout << "Please Enter a Username: ";
            cin >> username;
            cout << "Please Enter a Password: ";
            cin >> password;
            Login login(username, password);
            if (login.check_username()){
                cout << "\nThis Username Already Exists\n";
                cout << "Please Try Again\n";
                system("pause");
                goto signup;
            }
            else{
                string name;
                bool admin = false;
                cout << "Please Enter Your Name: ";
                cin >> name;
                data.open("accounts.txt", ios::app|ios::out);
                data << username << " " << password << " " << name << " " << admin << "\n";
                data.close();
                cout << "\nAccount Created Successfully\n\n";
                system("pause");
                break;
            }
        }
        case '3':{
            exit(0);
        }
        default:{
            cout << "Invalid entry\n";
            cout << "Enter again\n";
            system("pause");
            goto start;
        }
    }

    string uname, pass, name;
    bool admin;

    data.open("accounts.txt", ios::in);
    data >> uname >> pass >> name >> admin;
    while (!data.eof()){
        if (uname == username && pass == password){
            break;
        }
        data >> uname >> pass >> name >> admin;
    }
    data.close();

    Login login(username, password);
    Permission per(admin);
    User user(name, per, login);

    system("cls");
	cout << "\n\n\t\t-----------TELEPHONE DIRECTORY-------------\n\n";
    cout << "Welcome " << user.get_name() << "\n";
    if (user.per.get_role()){
        cout << "You are Signed-In as an Admin User\n";
    }
    else{
        cout << "You are Signed-In as an Normal User\n";
    }
    system("pause");
    
    main:
    Directory dir;
    system("cls");
    cout << "\n\n\t\t-----------TELEPHONE DIRECTORY-------------\n\n";
    cout << "Do you want to \n\n";
    cout << "\t1.  Search an Existing Directory by Name\n";
    cout << "\t2.  Search an Existing Directory by Phone Number\n";
    cout << "\t3.  Enter New Directory\n";
    cout << "\t4.  Delete Existing Directory\n";
    cout << "\t5.  Modify Existing Directory\n";
    cout << "\t6.  Log Out\n";
    cout << "\t7.  Log Out and Exit\n";
	cout <<"\nPlease Enter Your Choice: ";
    cin >> choice;

    switch (choice){
        case '1':{
            if (!user.per.get_permission("search")){
                cout << "Permission Denied\n";
                cout << "Choose Other Option\n";
            }
            else{
                string fname, lname;
                cout << "\nEnter First Name: ";
                cin >> fname;
                cout << "Enter Last Name: ";
                cin >> lname;
                Name name(fname, lname);
                dir = dir.search_name(name);
                if (dir.no.get_number() == ""){
                    cout << "\nRecord Not Found!\n";
                }
                else{
                    cout << "\nRecord Found!\n\n";
                    cout << dir;
                }
            }
            system("pause");
            goto main;
        }
        case '2':{
            if (!user.per.get_permission("search")){
                cout << "Permission Denied\n";
                cout << "Choose Other Option\n";
            }
            else{
                string acode, num;
                cout << "\nEnter Area Code: ";
                cin >> acode;
                cout << "Enter Phone Number: ";
                cin >> num;
                PhoneNo no(acode, num);
                dir = dir.search_phoneNo(no);
                if (dir.name.get_firstName() == ""){
                    cout << "\nRecord Not Found!\n";
                }
                else{
                    cout << "\nRecord Found!\n\n";
                    cout << dir;
                }
            }
            system("pause");
            goto main;
        }
        case '3':{
            if (!user.per.get_permission("add")){
                cout << "Permission Denied\n";
                cout << "Choose Other Option\n";
            }
            else{
                string fname, lname, acode, num, hno, str, area, city;
                cout << "\nEnter First Name: ";
                cin >> fname;
                cout << "Enter Last Name: ";
                cin >> lname;
                cout << "Enter Area Code: ";
                cin >> acode;
                cout << "Enter Phone Number: ";
                cin >> num;
                cout << "Enter House Number: ";
                cin >> hno;
                cout << "Enter Street: ";
                cin >> str;
                cout << "Enter Area: ";
                cin >> area;
                cout << "Enter City: ";
                cin >> city;
                PhoneNo no(acode, num);
                Name name(fname, lname);
                Address add(hno, str, area, city);
                Directory dir(no, name, add);
                int flag = dir.add_dir();
                if (flag == 0){
                    cout << "Record Already Exists!\n";
                    cout << "Please Enter Different Details\n";
                }
                else{
                    cout<<"\nEntry Successful!\n";
                }
            }
            system("pause");
            goto main;
        }
        case '4':{
            if (!user.per.get_permission("del")){
                cout << "Permission Denied\n";
                cout << "Choose Other Option\n";
            }
            else{
                string fname, lname, acode, num, hno, str, area, city;
                cout << "\nEnter the First name of Record You Want to Delete: ";
                cin >> fname;
                cout << "Enter the Last name of Record You Want to Delete: ";
                cin >> lname;
                PhoneNo no(acode, num);
                Name name(fname, lname);
                Address add(hno, str, area, city);
                Directory dir(no, name, add);
                int flag = dir.delete_dir();
                if (flag == 0){
                    cout << "\nRecord Not Found!\n";
                    cout << "Please Enter Different Details\n";
                }
                else{
                    cout << "\nThe Record with the Name " << fname << " " << lname << " has been Deleted\n";
                }
            }
            system("pause");
            goto main;
        }
        case '5':{
            if (!user.per.get_permission("edit")){
                cout << "Permission Denied\n";
                cout << "Choose Other Option\n";
            }
            else{
                string fname, lname, acode, num, hno, str, area, city;
                cout << "\nEnter the First name of Record You Want to Edit: ";
                cin >> fname;
                cout << "Enter the Last name of Record You Want to Edit: ";
                cin >> lname;
                PhoneNo no(acode, num);
                Name name(fname, lname);
                Address add(hno, str, area, city);
                Directory dir(no, name, add);
                int flag = dir.edit_dir();
                if (flag == 0){
                    cout << "\nRecord Not Found!\n";
                    cout << "Please Enter Different Details\n";
                }
                else{
                    cout << "\nThe Record with the Name " << fname << " " << lname << " has been Edited\n" << endl;
                }
            }
            system("pause");
            goto main;
        }
        case '6':{
            cout << "\nLogged out successfully!\n";
			system("pause");
            goto start;
        }
        case '7':{
            exit(0);
        }
        default:{
            cout << "Invalid entry\n";
            cout << "Enter again\n";
            system("pause");
            goto main;
        }
    }
}