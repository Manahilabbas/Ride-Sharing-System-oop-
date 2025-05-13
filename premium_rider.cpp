#include "premium_rider.h"
#include "subscription.h" // Include the Subscription header
using namespace std;

PremiumRider::PremiumRider() {}

PremiumRider::PremiumRider(string id, string n, string p,string pass,Subscription&  plan) : Rider(id, n, p,pass),plan(plan) {}

void PremiumRider::incrementRideHistory() {
    Rider::incrementRideHistory();
}
Subscription PremiumRider::getSubscription() const {
    return plan;
}

