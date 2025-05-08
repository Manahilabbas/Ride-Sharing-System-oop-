#include "auth_manager.h"
#include "driver.h"
#include "premium_rider.h"
#include <iostream>

using namespace std;

bool AuthManager::isRegistered(const string& id) {
    return false;  // Placeholder
}

User* AuthManager::signUp(map<string, string>& credentials, vector<User*>& users, bool isDriver) {
    string id, pwd;
    cout << "\nEnter ID: "; getline(cin, id);
    cout << "Enter Password: "; getline(cin, pwd);
    if (credentials.count(id)) {
        cout << "\n⚠️ ID already registered. Please login.\n";
        return nullptr;
    }

    credentials[id] = pwd;
    User* user = isDriver ? static_cast<User*>(new Driver(id, "", "")) : static_cast<User*>(new PremiumRider(id, "", ""));
    user->signUp();
    users.push_back(user);
    return user;
}

User* AuthManager::login(map<string, string>& credentials, const vector<User*>& users) {
    string id, pwd;
    cout << "\nEnter ID: "; getline(cin, id);
    cout << "Enter Password: "; getline(cin, pwd);

    if (!credentials.count(id) || credentials[id] != pwd) {
        cout << "\n❌ Invalid credentials!\n";
        return nullptr;
    }

    for (auto u : users) {
        if (u->getID() == id) return u;
    }

    return nullptr;
}
