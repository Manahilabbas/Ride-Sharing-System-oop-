#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

// Custom classes
#include "user.h"
#include "driver.h"
#include "rider.h"
#include "premium_rider.h"
#include "ride.h"
#include "auth_manager.h"
#include "review_manager.h"

int main() {
    vector<User*> users;
    map<string, string> credentials;
    User* currentUser = nullptr;
    ReviewManager reviewManager;
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
            currentUser = AuthManager::signUp(credentials, users, choice == 1);
        }
        else if (choice == 3) {
            currentUser = AuthManager::login(credentials, users);
            if (!currentUser) continue;

            cout << "\n✅ Login successful! Welcome back, " << currentUser->getName() << "!\n";

            if (currentUser->getRole() == "Driver") {
                Driver* d = dynamic_cast<Driver*>(currentUser);
                if (d) {
                    d->askAvailability();
                    d->displayReviews();  // load from file
                }
            }
            else {
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
                                string comment;
                                cout << "\nPlease rate your driver (1-5): ";
                                cin >> rating;
                                cin.ignore();
                                cout << "Leave a review for the driver: ";
                                getline(cin, comment);

                                d->setTimestamp();  // updates time
                                DriverReview review(currentUser->getName(), 1, rating, comment, d->getTimestamp());
                                d->addReview(review);

                                // Save to file via ReviewManager
                                reviewManager.saveReviewToFile(d->getName(), review);

                                PremiumRider* pr = dynamic_cast<PremiumRider*>(currentUser);
                                if (pr) pr->incrementRideHistory();

                                cout << "\n✅ Ride completed! Thank you for your feedback.\n";
                            }
                            break;
                        }
                    }
                }
                if (!matched) cout << "\n🚫 No available driver found for your request.\n";
            }
        }
        else if (choice == 4) break;
    }

    return 0;
}
