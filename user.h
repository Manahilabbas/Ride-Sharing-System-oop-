#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User {
protected:
    string userID, name, phoneNum, role;
public:
    User();
    User(string id, string n, string p, string r);
    virtual void signUp();
    virtual void displayInfo();
    string getName() const;
    string getID() const;
    string getRole() const;
};

#endif
