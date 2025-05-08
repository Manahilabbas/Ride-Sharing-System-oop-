#ifndef AUTH_MANAGER_H
#define AUTH_MANAGER_H

#include <map>
#include <vector>
#include <string>
#include "user.h"

class AuthManager {
public:
    static bool isRegistered(const std::string& id);
    static User* signUp(std::map<std::string, std::string>& credentials, std::vector<User*>& users, bool isDriver);
    static User* login(std::map<std::string, std::string>& credentials, const std::vector<User*>& users);
};

#endif
