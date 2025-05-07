#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <ctime>
#include <limits>
using namespace std;

class DriverReview;
class Subscription;

// ====================== Base User =========================
class User {
protected:
    string userID, name, phoneNum, role;
public:
    User() {}
    User(string id, string n, string p, string r) : userID(id), name(n), phoneNum(p), role(r) {}
    virtual void signUp() {
        cout << "Enter your name: ";
        getline(cin, name);
        cout << "Enter your phone number: ";
        getline(cin, phoneNum);
        cout << "\n✅ Signup successful! Welcome, " << name << "!\n";
    }
    virtual void displayInfo() {
        cout << "User ID: " << userID << "\nName: " << name << "\nPhone Number: " << phoneNum << "\nRole: " << role << endl;
    }
    string getName() const { return name; }
    string getID() const { return userID; }
    string getRole() const { return role; }
};

// ====================== Driver Review ===================== 
class DriverReview {
private:
    string passengerName;
    int rideID;
    double rating;
    string reviewMessage;
    string timestamp;

public:
    DriverReview() {}
    DriverReview(string passenger, int ride,  double rate, string review, string time) {
        passengerName = passenger;
        rideID = ride;
        rating = (rate >= 1 && rate <= 5) ? rate : 3;
        reviewMessage = review;
        timestamp = time;
    }
    void displayReview() const {
        cout << "\U0001F464 Passenger: " << passengerName << endl;
        cout << "\u2B50 Rating: " << rating << "/5\n";
        cout << "\U0001F4DD Review: " << reviewMessage << endl;
        cout << "\U0001F4C5 Date: " << timestamp << endl;
    }
    double getRating() const { return rating; }
    string getTimestamp() const { return timestamp; }

    void setTimestamp(string time) {
        timestamp = time;
    }
};

// ====================== Subscription ====================== 
class Subscription {
private:
    string planType, registrationDate, expiryDate;
    double discount;

public:
    Subscription() : discount(0), planType("None"), expiryDate("N/A") {}
    void setPlan(int plan) {
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
    void displaySubscription() const {
        cout << "\n\U0001F4CC---------- Subscription Details ----------\n";
        cout << "Plan Type: " << planType << "\nDiscount: " << discount << "%\nExpiry: " << expiryDate << endl;
    }
};

// ====================== Rider ============================= 
class Rider : public User {
protected:
    int rideHistory;
public:
    Rider() {}
    Rider(string id, string n, string p) : User(id, n, p, "Rider"), rideHistory(0) {}
    void displayInfo() override {
        User::displayInfo();
        cout << "Total Rides: " << rideHistory << endl;
    }
    void incrementRideHistory() { rideHistory++; }
    void signUp() override {
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
            cin.ignore();  // To clear the input buffer after numeric input
            subscription.setPlan(planChoice);
            subscription.displaySubscription();
        }
    }
};

// ====================== Premium Rider ===================== 
class PremiumRider : public Rider {
private:
    Subscription plan;
public:
    PremiumRider() {}
    PremiumRider(string id, string n, string p) : Rider(id, n, p) {}
    void displayInfo() override {
        Rider::displayInfo();
        plan.displaySubscription();
    }
    void incrementRideHistory() {
        Rider::incrementRideHistory();
    }
};

// ====================== Driver ============================ 
class Driver : public User {
private:
    bool available;
    string vehicleType;
    DriverReview review;
    string currentZone;
    vector<DriverReview> driverReviews;

public:
    Driver() : available(true) {}
    Driver(string id, string n, string p) : User(id, n, p, "Driver"), available(true) {}

    string getTimestamp() const {
        if (!driverReviews.empty()) {
            return driverReviews.back().getTimestamp(); // Get the timestamp from the most recent review
        }
        return "";  // Return empty string if no reviews are present
    }

    void setTimestamp() {
        time_t now = time(0);
        string timestamp = ctime(&now);  // Converts current time to a string
        review.setTimestamp(timestamp);  // Set timestamp for the current review
    }

    void signUp() override {
        User::signUp();
        cout << "Enter your vehicle type (e.g., Bike, Rickshaw, AC Car, Non-AC Car): ";
        getline(cin, vehicleType);
    }

    void askAvailability() {
        cout << "Enter your current zone: ";
        getline(cin, currentZone);
        string input;
        cout << "Are you available? (yes/no): ";
        getline(cin, input);
        available = (input == "yes");
    }

    void displayInfo() override {
        User::displayInfo();
        cout << "Vehicle Type: " << vehicleType << endl;
        cout << "Availability: " << (available ? "Yes" : "No") << endl;
    }

    void addReview(const DriverReview& review) {
        driverReviews.push_back(review);
    }

    void displayReviews() const {
        cout << "\n--- Driver Reviews ---\n";
        for (const auto& rev : driverReviews) {
            rev.displayReview();
        }
    }

    string getCurrentZone() const { return currentZone; }
    bool isAvailable() const { return available; }
    string getVehicleType() const { return vehicleType; }
    
};

// ====================== Ride ============================== 
class Ride {
public:
    static map<string, int> zoneIndices;
    static map<pair<string, string>, double> distances;

    static void displayZones() {
        cout << "\nAvailable Zones:\n";
        for (const auto& z : zoneIndices) {
            cout << "- " << z.first << endl;
        }
    }

    static double calculateFare(string src, string dest, string vehicleType) {
        pair<string, string> key1 = {src, dest}, key2 = {dest, src};
        double baseRate = 30.0;
        double distance = distances.count(key1) ? distances[key1] : distances[key2];
        double multiplier = (vehicleType == "Bike") ? 1.0 :
                            (vehicleType == "Rickshaw") ? 1.2 :
                            (vehicleType == "Non-AC Car") ? 1.5 :
                            (vehicleType == "AC Car") ? 2.0 : 1.0;
        return distance * baseRate * multiplier;
    }
};

map<string, int> Ride::zoneIndices = {
    {"Saddar", 0}, {"DHA", 1}, {"Clifton", 2}, {"Gulshan-e-Iqbal", 3},
    {"PECHS", 4}, {"North Karachi", 5}, {"Nazimabad", 6}, {"Gulberg", 7},
    {"Malir", 8}, {"Korangi", 9}
};

map<pair<string, string>, double> Ride::distances = {
    {{"Saddar", "DHA"}, 10}, {{"Saddar", "Clifton"}, 5}, {{"DHA", "Gulshan-e-Iqbal"}, 18},
    {{"Clifton", "Gulshan-e-Iqbal"}, 15}, {{"PECHS", "North Karachi"}, 14},
    {{"Saddar", "North Karachi"}, 20}, {{"Clifton", "Korangi"}, 16},
    {{"Malir", "Nazimabad"}, 22}, {{"Korangi", "Gulshan-e-Iqbal"}, 13},
    {{"DHA", "North Karachi"}, 25}, {{"Nazimabad", "Gulberg"}, 6},
    {{"PECHS", "Malir"}, 12}, {{"Saddar", "PECHS"}, 4}, {{"Gulberg", "Korangi"}, 17}
};

/// ====================== Main ============================== 
int main() {
    vector<User*> users;
    map<string, string> credentials;
    User* currentUser = nullptr;
    int choice;

    while (true) {
        cout << "\n============================\n";
        cout << "🚖 Welcome to Ride Booking System 🚖\n";
        cout << "============================\n";
        cout << "1. Sign Up as Driver\n2. Sign Up as Rider\n3. Login\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1 || choice == 2) {
            string id, pwd;
            cout << "\nEnter ID: "; getline(cin, id);
            cout << "Enter Password: "; getline(cin, pwd);
            if (credentials.count(id)) {
                cout << "\n⚠️ ID already registered. Please login.\n";
                continue;
            }
            credentials[id] = pwd;
            if (choice == 1) {
                currentUser = new Driver(id, "", "");
            } else {
                currentUser = new PremiumRider(id, "", "");
            }
            currentUser->signUp();
            users.push_back(currentUser);
        }
        else if (choice == 3) {
            string id, pwd;
            cout << "\nEnter ID: "; getline(cin, id);
            cout << "Enter Password: "; getline(cin, pwd);
            if (!credentials.count(id) || credentials[id] != pwd) {
                cout << "\n❌ Invalid credentials!\n";
                continue;
            }
            for (auto u : users) {
                if (u->getID() == id) {
                    currentUser = u;
                    break;
                }
            }
            cout << "\n✅ Login successful! Welcome back, " << currentUser->getName() << "!\n";

            if (currentUser->getRole() == "Driver") {
                Driver* d = dynamic_cast<Driver*>(currentUser);
                if (d) {
                    d->askAvailability();
                    d->displayReviews();  // Display existing reviews
                }
            } else {
                Ride::displayZones();
                string src, dest, vType;
                cout << "\nEnter source zone: "; getline(cin, src);
                cout << "Enter destination zone: "; getline(cin, dest);
                cout << "Enter vehicle type (Bike/Rickshaw/Non-AC Car/AC Car): "; getline(cin, vType);
                double fare = Ride::calculateFare(src, dest, vType);
                cout << "\n💰 Estimated Fare: Rs. " << fare << "\n";

                bool matched = false;
                for (auto u : users) {
                    if (u->getRole() == "Driver") {
                        Driver* d = dynamic_cast<Driver*>(u);
                        if (d && d->isAvailable() && d->getCurrentZone() == src && d->getVehicleType() == vType) {
                            cout << "\n🎉 Matched with Driver: " << d->getName() << " (Vehicle: " << d->getVehicleType() << ")\n";
                            matched = true;
                            string rideComplete;
                            cout << "\nIs your ride completed? (yes/no): ";
                            getline(cin, rideComplete);
                            if (rideComplete == "yes") {
                                double rating;
                                string reviewMessage;
                                cout << "\nPlease rate your driver (1-5): "; cin >> rating;
                                cin.ignore();  // To clear the buffer after rating
                                cout << "Leave a review for the driver: ";
                                getline(cin, reviewMessage);

                                // Set the timestamp for the review before creating the DriverReview
                                d->setTimestamp();

                                // Now create the DriverReview with the updated timestamp
                                DriverReview review(currentUser->getName(), 1, rating, reviewMessage, d->getTimestamp());
                                d->addReview(review);

                                PremiumRider* pr = dynamic_cast<PremiumRider*>(currentUser);
                                if (pr) pr->incrementRideHistory();

                                cout << "\n✅ Ride completed! Thank you for your feedback.\n";
                            }
                            break;

                        }
                    }
                }
                if (!matched) {
                    cout << "\n🚫 No available driver found for your request.\n";
                }
            }
        }
        else if (choice == 4) break;
    }
    
    return 0;
}
