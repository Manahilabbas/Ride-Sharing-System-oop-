#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User {
protected:
    string userID, name, phoneNum, role,password,Email;
public:
    User();
    User(string id, string n, string p, string r,string passs);
    virtual void signUp();
    //virtual void displayInfo();
    string getName() const;
    string getID() const;
    string getRole() const;
    string getPassword()const;
    // Add these setters to your User class
void setPhoneNum(const string& e) { phoneNum = e; }
void setEmail(const string& e) { Email= e; }
void setPassword(const string& p) { password = p; }
void setRole(const string& r) { role = r; } // optional if role is already known

    friend ostream& operator<<(ostream& out, const User& user);
};

#endif
