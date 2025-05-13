#ifndef RIDER_H
#define RIDER_H

#include "user.h"
#include "subscription.h"

class Rider : public User {
protected:
    int rideHistory;
public:
    Rider();
    Rider(string id, string n, string p,string pass);
    //void displayInfo() override;
    friend ostream& operator<<(ostream& out, const Rider& rider);
    void incrementRideHistory();
    void signUp() override;
};

#endif
