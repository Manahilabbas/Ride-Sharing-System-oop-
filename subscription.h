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
   string getPlanType(){return planType;}
    double getDiscount() {return discount;}
  string getExpiryDate(){return expiryDate;}
    
    //void displaySubscription() const;
    friend ostream& operator<<(ostream& out, const Subscription& sub);
};


#endif
