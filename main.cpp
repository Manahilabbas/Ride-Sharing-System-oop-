#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <io.h>
#include <fcntl.h>
#include "user.h"
#include "driver.h"
#include "rider.h"
#include "premium_rider.h"
#include "ride.h"
#include "auth_manager.h"
#include "review_manager.h"
#include "subscription.h"
#include "driver_review.h"

using namespace std;

#include <string>
#include <cctype>
using namespace std;

bool isValidEmail(const string& email) {
    int atPos = email.find('@');
    int lastAt = email.rfind('@');

    // Must contain exactly one '@' and not at the start or end
    if (atPos <= 0 || atPos != lastAt || atPos == email.length() - 1) {
        return false;
    }

    // Check all alphabetic characters are lowercase
    for (char ch : email) {
        if (isalpha(ch) && !islower(ch)) {
            return false;
        }
    }

    return true;
}

void displayZones(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    int i = 0;
    std::string array[100];

    while (getline(file, line)) {
        size_t colonPos = line.find(':');
        if (colonPos != std::string::npos) {
            std::string zoneName = line.substr(0, colonPos);
            array[i] = zoneName;
            std::cout << i + 1 << ". " << zoneName << std::endl;
            i++;
        }
    }
}


void markDriverAvailable(const string& driverName, const string& zone) {
    ofstream out("available_driver.txt", ios::app);
    out << driverName << "," << zone << "\n";
    out.close();
}
bool assignDriverToRider(const string& selectedZone, string& assignedDriver) {
    ifstream in("available_driver.txt");
    ofstream temp("temp.txt");
    bool found = false;
    string line;

    while (getline(in, line)) {
        stringstream ss(line);
        string name, zone;
        getline(ss, name, ',');
        getline(ss, zone);

        if (!found && zone == selectedZone) {
            assignedDriver = name;
            found = true; // skip writing this driver to temp (remove)
        } else {
            temp << name << "," << zone << "\n";
        }
    }

    in.close();
    temp.close();
    remove("available_driver.txt");
    rename("temp.txt", "available_driver.txt");
    return found;
}


bool emailExists(const string& email) {
    ifstream file("users.txt");
    string existingEmail;
    while (file >> existingEmail) {
     
        if (existingEmail == email) return true;
    }
    return false;
}


struct SimulatedRide {
    std::string zone;
    bool assigned = false;
};


void assignRideToRider(std::vector<SimulatedRide>& rides) {
    std::ifstream in("selected_zone.txt");
    if (!in) {
        std::cout << "⚠️ No selected zone found.\n";
        return;
    }
    std::string selectedZone;
    getline(in, selectedZone);
    in.close();

    for (auto& ride : rides) {
        if (!ride.assigned && ride.zone == selectedZone) {
            ride.assigned = true;
            std::cout << "🚗 Ride assigned in zone: " << selectedZone << "\n";

            std::ofstream clear("selected_zone.txt", std::ofstream::trunc);
            clear.close();
            return;
        }
    }

    std::cout << "⌛ No ride available in " << selectedZone << ". Please wait and try again.\n";
}


void saveUserToFile(User* user) {
    ofstream file("users.txt", ios::app);
    if (file.is_open()) {
        file << user->getID() << " "
             << user->getPassword() << " "
             << user->getName() << " "
             << user->getRole() << "\n";
    }

    // Save PremiumRider's subscription separately
    if (user->getRole() == "PremiumRider") {
        PremiumRider* pr = dynamic_cast<PremiumRider*>(user);
        if (pr) {
            ofstream prem("premium_riders.txt", ios::app);
            prem << pr->getID() << " , "
                 << pr->getName() << " , "
                 << pr->plan.getPlanType() << " , "
                 << pr->plan.getDiscount() << " , "
                 << pr->plan.getExpiryDate() << "\n";
            prem.close();
        }
    }
 }



using namespace std;
#include <windows.h>
#include <fcntl.h>
#include <io.h>
int main() {
SetConsoleOutputCP(CP_UTF8);
_setmode(_fileno(stdout), _O_TEXT); // Use _O_TEXT if _O_U8TEXT isn't available


    vector<User*> users;
    map<string, string> credentials;
    User* currentUser = nullptr;

    int choice;
    while (true) {
        cout << "\n====================================\n";
        cout << "🚖 Welcome to Ride Booking System 🚖\n";
        cout << "====================================\n";
        cout << "1. Sign Up as Driver\n2. Sign Up as Rider\n3. Login\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1 || choice == 2) {
            string name, password, phone, email;

            cout << "Enter email: ";
            // cin.ignore();
            getline(cin, email);
            if(!isValidEmail(email)){
                cout<<"INVALID EMAIL ENTERED:)"<<endl;
                continue;
            }

            if (emailExists(email)) {
                cout << "❌ Email already registered. Try logging in.\n";
                continue;
            }

            while (true) {
                cout << "Enter password (must include 1 uppercase, 1 digit, and be 11 characters): ";
                getline(cin, password);
                bool hasDigit = false, hasUpper = false;
                for (char ch : password) {
                    if (isdigit(ch)) hasDigit = true;
                    if (isupper(ch)) hasUpper = true;
                }
                if (password.length() != 11 || !hasDigit || !hasUpper) {
                    cout << "❌ Invalid password. Try again.\n";
                } else break;
            }

            User* newUser = nullptr;

            if (choice == 1) {
                newUser = new Driver(email, name, phone, password);
                newUser->setRole("Driver");
            } else {
                int riderType;
                cout << "1. Normal Rider\n2. Premium Rider\nChoose: ";
                cin >> riderType;
                // cin.ignore();

                if (riderType == 1) {
                    newUser = new Rider(email, name, phone, password);
                    newUser->setRole("Rider");
                } else {
                    int planType;
                    cout << "Choose Plan:\n1. Weekly\n2. Monthly\n3. Yearly\n";
                    cin >> planType;
                    cin.ignore();

                    Subscription sub;
                    sub.setPlan(planType);

                    PremiumRider* pr = new PremiumRider(email, name, phone, password, sub);
                    pr->setRole("PremiumRider");
                    newUser = pr;
                }
            }

            newUser->setEmail(email);
            newUser->setPassword(password);
            newUser->signUp(); // ask name and phone

            saveUserToFile(newUser);
            users.push_back(newUser);

            cout << "✅ Account created successfully!\n";
        }

        else if (choice == 3) {
            AuthManager auth;
            currentUser = auth.login(credentials, users);
            if (!currentUser) continue;

            cout << "\n✅ Logged in as " << currentUser->getName() << " (" << currentUser->getRole() << ")\n";
            displayZones("zones.txt");
            string selectedZone;
            
     

            if (currentUser->getRole() == "Driver") {
                string driverLoc, rideType;

                cout << "Enter your current location: ";
                getline(cin, driverLoc);

                cout << "Enter your ride type (Bike, Rickshaw, Non-AC Car, AC Car): ";
                getline(cin, rideType);

                ofstream outDriver("available_driver.txt", ios::app);
                outDriver << currentUser->getName() << "," << selectedZone << "," << rideType << "\n";
                outDriver.close();

                cout << "📍 Driver is now available in zone: " << selectedZone
                     << " with ride type: " << rideType << "\n";
            }

            else if (currentUser->getRole() == "Rider" || currentUser->getRole() == "PremiumRider") {
                string riderLoc, desLoc, rideType;

                cout << "Enter your current location: ";
                getline(cin, riderLoc);

                cout << "Enter your destination location: ";
                getline(cin, desLoc);

                cout << "Enter your ride type (Bike, Rickshaw, Non-AC Car, AC Car): ";
                getline(cin, rideType);

                // Searching for an available driver
                ifstream in("available_driver.txt");
                ofstream temp("temp.txt");
                string line, assignedDriver;
                bool found = false;

                while (getline(in, line)) {
                    stringstream ss(line);
                    string driverName, driverZone, driverRide;
                    getline(ss, driverName, ',');
                    getline(ss, driverZone, ',');
                    getline(ss, driverRide);

                    if (!found && driverZone == selectedZone && driverRide == rideType) {
                        assignedDriver = driverName;
                        found = true;
                    } else {
                        temp << driverName << "," << driverZone << "," << driverRide << "\n";
                    }
                }

                in.close();
                temp.close();
                remove("available_driver.txt");
                rename("temp.txt", "available_driver.txt");

                if (found) {
                    cout << "🚗 Driver '" << assignedDriver << "' assigned in zone: " << selectedZone
                         << " for ride type: " << rideType << "\n";

                    // Display reviews for the assigned driver
                    cout << "\n💬 Driver Reviews: \n";
                    displayReviewsFromFile(assignedDriver + "_reviews.txt");

                    // Ride completion, ask for a review
                    char reviewChoice;
                    cout << "\nDo you want to leave a review for driver '" << assignedDriver << "'? (Y/N): ";
                    cin >> reviewChoice;
                    cin.ignore();

                    if (reviewChoice == 'Y' || reviewChoice == 'y') {
                        string passengerName, reviewMessage, timestamp;
                        int rating;

                        // Collect review details
                        cout << "Enter your name: ";
                        getline(cin, passengerName);

                        cout << "Enter your rating (1-5): ";
                        cin >> rating;
                        cin.ignore();

                        cout << "Enter your review message: ";
                        getline(cin, reviewMessage);

                        cout << "Enter the timestamp (e.g., 2025-05-12 14:30): ";
                        getline(cin, timestamp);

                        DriverReview newReview(passengerName, rating, reviewMessage, timestamp);
                        ReviewManager reviewManager;
                        reviewManager.saveReviewToFile(assignedDriver, newReview);

                        cout << "✅ Review successfully saved for " << assignedDriver << ".\n";
                    }
                } else {
                    cout << "❌ No driver found for the selected zone and ride type.\n";
                }
            }
        }

        else if (choice == 4) {
            cout << "👋 Goodbye!\n";
            break;
        }

        else {
            cout << "❌ Invalid choice!\n";
        }
    }
    fstream file("available_driver.txt",ios::trunc);
    file.close();

    return 0;
}
















