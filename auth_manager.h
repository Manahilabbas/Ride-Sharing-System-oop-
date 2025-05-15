#ifndef AUTH_MANAGER_H
#define AUTH_MANAGER_H
#include "driver.h"
#include "premium_rider.h"
#include "user.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <conio.h>
#include <map>
#include <vector>
#include <string>


class AuthManager {
public:
    
    static string validatePassword();
    static bool isRegistered(const std::string& id);
    static User* login(std::map<std::string, std::string>& credentials, const std::vector<User*>& users);
    User* login(map<string, string>& credentials, vector<User*>& users);
};
bool isPhoneRegistered(const string& phone) ;

#endif
