#include "rider.h"
#include <iostream>
using namespace std;

Rider::Rider() {}

Rider::Rider(string id, string n, string p) : User(id, n, p, "Rider"), rideHistory(0) {}

void Rider::displayInfo() {
    User::displayInfo();
    cout << "Total Rides: " << rideHistory << endl;
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
        subscription.displaySubscription();
    }
}
