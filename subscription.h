#ifndef SUBSCRIPTION_H
#define SUBSCRIPTION_H

#include <string>
using namespace std;

class Subscription {
private:
    string planType, registrationDate, expiryDate;
    double discount;

public:
    Subscription();
    void setPlan(int plan);
    void displaySubscription() const;
};

#endif
