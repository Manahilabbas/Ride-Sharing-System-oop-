#include "auth_manager.h"
string AuthManager::validatePassword() {
    string pwd;
    while (true) {
        try {
            cout << "\nEnter Password: ";
            cout << "\nPassword must be exactly 11 characters long, contain at least one digit and one uppercase letter.\n";

            char ch;
            bool hasDigit = false, hasUpper = false;
            pwd = "";

            while (true) {
                ch = _getch();

                if (ch == 13) break; // Enter
                else if (ch == 8) {
                    if (!pwd.empty()) {
                        pwd.pop_back();
                        cout << "\b \b";
                    }
                } else {
                    pwd += ch;
                    cout << "*";
                    if (isdigit(ch)) hasDigit = true;
                    if (isupper(ch)) hasUpper = true;
                }
            }

            if (pwd.length() != 11)
                throw invalid_argument("Password must be exactly 11 characters.");
            if (!hasDigit)
                throw invalid_argument("Password must contain at least one digit.");
            if (!hasUpper)
                throw invalid_argument("Password must contain at least one uppercase letter.");

            cout << "\n✅ Password accepted!\n";
            return pwd;
        } catch (const invalid_argument& e) {
            cout << "\n❌ " << e.what() << "\nPlease try again.\n";
        }
    }
}
bool isPhoneRegistered(const string& phone) {
    ifstream file("users.txt");
    string line;
    while (file>>line) {
        size_t pos = line.rfind('|');
        if (pos != string::npos && line.substr(pos + 1) == phone) {
            return true;
        }
    }
    return false;
}





User* AuthManager::login(map<string, string>& credentials, vector<User*>& users) {
    string id, pwd;
    cout << "\nEnter ID: "; getline(cin, id);
    pwd = validatePassword();

    ifstream infile("users.txt");
    string line;
    while (getline(infile, line)) {
        stringstream ss(line);
        string fileID, filePwd, name, role;

        getline(ss, fileID, ' ');
        getline(ss, filePwd, ' ');
        getline(ss, name, ' ');
        getline(ss, role, ' ');
         Subscription plan;
        if (fileID == id && filePwd == pwd) {
            User* user = nullptr;
            if (role == "Driver") user = new Driver(id, name, "",pwd);
            else if (role == "Rider") user = new Rider(id, name, "",pwd);
            else if (role == "PremiumRider") user = new PremiumRider(id, name, "",pwd,plan);

            if (user) {
                users.push_back(user);
                return user;
            }
        }
    }

    cout << "\n❌ Invalid credentials or user not found.\n";
    return nullptr;
}



