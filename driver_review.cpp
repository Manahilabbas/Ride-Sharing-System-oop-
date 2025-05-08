#include "driver_review.h"
#include <iostream>
using namespace std;

DriverReview::DriverReview() {}

DriverReview::DriverReview(string passenger, int ride, double rate, string review, string time) {
    passengerName = passenger;
    rideID = ride;
    rating = (rate >= 1 && rate <= 5) ? rate : 3;
    reviewMessage = review;
    timestamp = time;
}

void DriverReview::displayReview() const {
    cout << "\U0001F464 Passenger: " << passengerName << endl;
    cout << "\u2B50 Rating: " << rating << "/5\n";
    cout << "\U0001F4DD Review: " << reviewMessage << endl;
    cout << "\U0001F4C5 Date: " << timestamp << endl;
}

double DriverReview::getRating() const { return rating; }

string DriverReview::getTimestamp() const { return timestamp; }

void DriverReview::setTimestamp(string time) {
    timestamp = time;
}
