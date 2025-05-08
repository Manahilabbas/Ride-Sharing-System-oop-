#include "premium_rider.h"
using namespace std;

PremiumRider::PremiumRider() {}

PremiumRider::PremiumRider(string id, string n, string p) : Rider(id, n, p) {}

void PremiumRider::displayInfo() {
    Rider::displayInfo();
    plan.displaySubscription();
}

void PremiumRider::incrementRideHistory() {
    Rider::incrementRideHistory();
}
