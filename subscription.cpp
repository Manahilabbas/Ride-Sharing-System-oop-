#include "subscription.h"
#include <iostream>
using namespace std;

Subscription::Subscription() : discount(0), planType("None"), expiryDate("N/A") {}

void Subscription::setPlan(int plan) {
    if (plan == 1) {
        planType = "Weekly"; discount = 5; expiryDate = "7 days from today";
    } else if (plan == 2) {
        planType = "Monthly"; discount = 10; expiryDate = "30 days from today";
    } else if (plan == 3) {
        planType = "Yearly"; discount = 20; expiryDate = "365 days from today";
    } else {
        cout << "\u274C Invalid plan selected! Subscription Failed.\n";
    }
}

void Subscription::displaySubscription() const {
    cout << "\n\U0001F4CC---------- Subscription Details ----------\n";
    cout << "Plan Type: " << planType << "\nDiscount: " << discount << "%\nExpiry: " << expiryDate << endl;
}
