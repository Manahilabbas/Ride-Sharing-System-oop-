#ifndef PREMIUMRIDER_H
#define PREMIUMRIDER_H

#include "rider.h"
#include "subscription.h"

class PremiumRider : public Rider {

   
public:
 Subscription plan;
    PremiumRider();
    PremiumRider(string id, string n, string p,string pass,Subscription&plan);
    friend ostream& operator<<(ostream& out, const PremiumRider& premiumRider);
    void incrementRideHistory();
    Subscription getSubscription() const ;

};

#endif
