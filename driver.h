#ifndef DRIVER_H
#define DRIVER_H

#include "User.h"
#include "driver_review.h"
#include <vector>

class Driver : public User {
private:
    bool available;
    string vehicleType;
    DriverReview review;
    string currentZone;
    vector<DriverReview> driverReviews;

public:
    Driver();
    Driver(string id, string n, string p,string pass);
    void signUp() override;
    void askAvailability();
    //void displayInfo() override;
    void addReview(const DriverReview& review);
    friend ostream& operator<<(ostream& out, const Driver& driver);
    
    string getCurrentZone() const;
    bool isAvailable() const;
    string getVehicleType() const;
    string getTimestamp() const;
   
    void displayReviews()const;
    string setTimestamp();
};

#endif
