#include "user.h"
#include <iostream>
using namespace std;

User::User() {}

User::User(string id, string n, string p, string r) : userID(id), name(n), phoneNum(p), role(r) {}

void User::signUp() {
    cout << "Enter your name: ";
    getline(cin, name);
    cout << "Enter your phone number: ";
    getline(cin, phoneNum);
    cout << "\n✅ Signup successful! Welcome, " << name << "!\n";
}

void User::displayInfo() {
    cout << "User ID: " << userID << "\nName: " << name << "\nPhone Number: " << phoneNum << "\nRole: " << role << endl;
}

string User::getName() const { return name; }
string User::getID() const { return userID; }
string User::getRole() const { return role; }
