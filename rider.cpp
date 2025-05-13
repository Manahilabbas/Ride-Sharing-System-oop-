#include "rider.h"
#include <iostream>
using namespace std;

Rider::Rider() {}

Rider::Rider(string id, string n, string p,string pass) : User(id, n, p, "Rider",pass), rideHistory(0) {}

// void Rider::displayInfo() {
//     User::displayInfo();
//     cout << "Total Rides: " << rideHistory << endl;
// }
ostream& operator<<(ostream& out, const Rider& rider) {
    out << static_cast<const User&>(rider);  // Reuse base class operator<< if defined
    out << "Total Rides: " << rider.rideHistory << endl;
    return out;
}

void Rider::incrementRideHistory() { rideHistory++; }

void Rider::signUp() {
    User::signUp();
    string choice;
    cout << "\nWould you like to sign up for a premium plan? (yes/no): ";
    getline(cin, choice);
    if (choice == "yes") {
        Subscription subscription;
        int planChoice;
        cout << "\nAvailable Plans:\n1. Weekly - 5% Discount\n2. Monthly - 10% Discount\n3. Yearly - 20% Discount\n";
        cout << "Choose a plan (1/2/3): ";
        cin >> planChoice;
        cin.ignore();
        subscription.setPlan(planChoice);
        cout << subscription;  // Display subscription details
        //subscription.displaySubscription();
    }
}
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// Simulated Ride class
class Ride {
public:
    std::string zone;
    bool assigned;

    Ride(const std::string& z) : zone(z), assigned(false) {}

    bool isAssigned() const { return assigned; }
    void assign() { assigned = true; }
    std::string getZone() const { return zone; }
};


