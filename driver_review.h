#ifndef DRIVERREVIEW_H
#define DRIVERREVIEW_H

#include <string>
using namespace std;

class DriverReview {
private:
    string passengerName;
    int rideID;
    double rating;
    string reviewMessage;
    string timestamp;

public:
    DriverReview();
    DriverReview(string passenger, int ride, double rate, string review, string time);
    void displayReview() const;
    double getRating() const;
    string getTimestamp() const;
    void setTimestamp(string time);
    string getPassengerName() const { return passengerName; }
int getRideID() const { return rideID; }
string getReviewMessage() const { return reviewMessage; }



};

#endif
