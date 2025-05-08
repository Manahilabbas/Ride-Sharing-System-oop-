#include "review_manager.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

void ReviewManager::saveReviewToFile(const string& driverName, const DriverReview& review) {
    ofstream file(driverName + "_reviews.txt", ios::app);
    if (file.is_open()) {
        file << review.getPassengerName() << "|"
             << review.getRating() << "|"
             << review.getReviewMessage() << "|"
             << review.getTimestamp() << "\n";
        file.close();
    }
}

void ReviewManager::loadReviews(const string& driverName, vector<DriverReview>& reviews) {
    ifstream file(driverName + "_reviews.txt");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name, ratingStr, comment, timestamp;

        getline(ss, name, '|');
        getline(ss, ratingStr, '|');
        getline(ss, comment, '|');
        getline(ss, timestamp);

        double rating = stod(ratingStr);
        DriverReview review(name, 1, rating, comment, timestamp);
        reviews.push_back(review);
    }
}
