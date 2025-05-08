#ifndef PREMIUMRIDER_H
#define PREMIUMRIDER_H

#include "rider.h"
#include "subscription.h"

class PremiumRider : public Rider {
private:
    Subscription plan;
public:
    PremiumRider();
    PremiumRider(string id, string n, string p);
    void displayInfo() override;
    void incrementRideHistory();
};

#endif
