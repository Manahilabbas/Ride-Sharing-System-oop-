#ifndef RIDER_H
#define RIDER_H

#include "user.h"
#include "subscription.h"

class Rider : public User {
protected:
    int rideHistory;
public:
    Rider();
    Rider(string id, string n, string p);
    void displayInfo() override;
    void incrementRideHistory();
    void signUp() override;
};

#endif
