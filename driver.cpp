#include "driver.h"
#include <iostream>
#include <ctime>
#include "review_manager.h"
using namespace std;

Driver::Driver() : available(true) {}

Driver::Driver(string id, string n, string p, string pass)
    : User(id, n, p, "Driver", pass), available(true) {}

void Driver::signUp() {
    User::signUp();
    cout << "Enter your vehicle type (e.g., Bike, Rickshaw, AC Car, Non-AC Car): ";
    getline(cin, vehicleType);
}

void Driver::askAvailability() {
    cout << "Enter your current zone: ";
    getline(cin, currentZone);

    string input;
    cout << "Are you available? (yes/no): ";
    getline(cin, input);
    available = (input == "yes");
}

ostream& operator<<(ostream& out, const Driver& driver) {
    out << static_cast<const User&>(driver);  // Reuse User's operator<<
    out << "Vehicle Type: " << driver.vehicleType << "\n";
    out << "Availability: " << (driver.available ? "Yes" : "No") << "\n";
    return out;
}

void Driver::addReview(const DriverReview& review) {
    driverReviews.push_back(review);
}

string Driver::getCurrentZone() const {
    return currentZone;
}

bool Driver::isAvailable() const {
    return available;
}

string Driver::getVehicleType() const {
    return vehicleType;
}

string Driver::getTimestamp() const {
    if (!driverReviews.empty()) {
        return driverReviews.back().getTimestamp();
    }
    return "";
}

void Driver::displayReviews() const {
    vector<DriverReview> reviews;
    ReviewManager::loadReviews(name, reviews);
    
    cout << "\n⭐ Reviews for " << name << ":\n";
    for (const auto& r : reviews) {
        cout << r.getTimestamp() << " - " << r.getPassengerName()
             << " rated " << r.getRating() << " stars\n"
             << "\"" << r.getReviewMessage() << "\"\n\n";
    }
}

string Driver::setTimestamp() {
    time_t now = time(0);               // Get current time as time_t
    char* dt = ctime(&now);             // Convert to string format
    string timestamp(dt);
    timestamp.pop_back();               // Remove trailing newline
    return timestamp;
}
