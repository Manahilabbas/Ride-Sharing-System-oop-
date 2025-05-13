
#include "subscription.h"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>


using namespace std;
using namespace chrono;

Subscription::Subscription() : discount(0), planType("None"), expiryDate("N/A") {}



// void Subscription::displaysubscriptionSubscription() const {
//     cout << "\n\U0001F4CC---------- Subscription Details ----------\n";
//     cout << "Plan Type: " << planType << "\nDiscount: " << discount << "%\nExpiry: " << expiryDate << endl;
// }
ostream& operator<<(ostream& out, const Subscription& sub) {
    out << "\n\U0001F4CC---------- Subscription Details ----------\n";
    out << "Plan Type: " << sub.planType << "\n";
    out << "Discount: " << sub.discount << "%\n";
    out << "Expiry: " << sub.expiryDate << endl;
    return out;
}





void Subscription::setPlan(int plan) {
    int daysToAdd = 0;

    if (plan == 1) {
        planType = "Weekly"; discount = 5; daysToAdd = 7;
    } else if (plan == 2) {
        planType = "Monthly"; discount = 10; daysToAdd = 30;
    } else if (plan == 3) {
        planType = "Yearly"; discount = 20; daysToAdd = 365;
    } else {
        cout << "\u274C Invalid plan selected! Subscription Failed.\n";
        return;
    }

    // Get current date
    auto now = system_clock::now();
    time_t now_c = system_clock::to_time_t(now);
    tm now_tm = *localtime(&now_c);

    // Save registration date
    stringstream regDateStream;
    regDateStream << put_time(&now_tm, "%Y-%m-%d");
    registrationDate = regDateStream.str();

    // Calculate expiry date
    auto expiry_time = now + hours(24 * daysToAdd);
    time_t expiry_c = system_clock::to_time_t(expiry_time);
    tm expiry_tm = *localtime(&expiry_c);

    stringstream expiryDateStream;
    expiryDateStream << put_time(&expiry_tm, "%Y-%m-%d");
    expiryDate = expiryDateStream.str();
}
