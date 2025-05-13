#include "user.h"
#include <iostream>
using namespace std;

User::User() {}

User::User(string id, string n, string p, string r,string passs) : userID(id), name(n), phoneNum(p), role(r),password(passs) {}



void User::signUp() {
    cout << "Enter your name: ";
    getline(cin, name);

    while (true) {
        try {
            cout << "Enter your phone number: ";
            getline(cin, phoneNum);
            if (phoneNum.length() != 10) {
                throw invalid_argument("Phone number must be exactly 10 digits.");
            }
            break;
        } catch (const invalid_argument& e) {
            cout << "\n❌ " << e.what() << "\nPlease try again.\n";
        }
    }
    

    cout << "\n✅ Signup successful! Welcome, " << name << "!\n";
}


string User::getName() const { return name; }
string User::getID() const { return userID; }
string User::getRole() const { return role; }
string User::getPassword()const{return password;}

ostream& operator<<(ostream& out, const User& user) {
    out << "Name: " << user.name << "\n";
    out << "User ID: " << user.userID << "\n";
    out << "Phone: " << user.phoneNum << "\n";
    return out;
}
