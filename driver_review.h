#ifndef DRIVER_REVIEW_H
#define DRIVER_REVIEW_H

#include <string>
#include <iostream>

class DriverReview {
private:
    std::string passengerName;
    int rating;
    std::string reviewMessage;
    std::string timestamp;

public:
    DriverReview();
    DriverReview(const std::string& name, int rate, const std::string& message, const std::string& time);


    static DriverReview fromString(const std::string& line);  // Static method to create from string

    // Getter methods
    std::string getPassengerName() const { return passengerName; }
    int getRating() const { return rating; }
    std::string getReviewMessage() const { return reviewMessage; }
    std::string getTimestamp() const { return timestamp; }

    friend std::ostream& operator<<(std::ostream& out, const DriverReview& r);
};

void displayReviewsFromFile(const std::string& filename);

#endif // DRIVER_REVIEW_H
