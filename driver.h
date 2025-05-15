#ifndef DRIVER_H
#define DRIVER_H

#include "User.h"
#include "driver_review.h"
#include <vector>

class Driver : public User {
private:
    bool available;
    string vehicleType;
    string currentZone;
    DriverReview review;
    std::vector<DriverReview> driverReviews;

public:
    Driver();
    Driver(string id, string n, string p, string pass);

    void signUp() override;
    void askAvailability();
    void addReview(const DriverReview& review);
    void displayReviews() const;

    string getCurrentZone() const;
    bool isAvailable() const;
    string getVehicleType() const;
    string getTimestamp() const;
    string setTimestamp();

    friend std::ostream& operator<<(std::ostream& out, const Driver& driver);
};

#endif // DRIVER_H
