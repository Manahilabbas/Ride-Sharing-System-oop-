#include "review_manager.h"
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

void ReviewManager::saveReviewToFile(const string& driverName, const DriverReview& review) {
  try{
    ofstream file(driverName + "_reviews.txt", ios::app);
    if (file.is_open()) {
        file << review.getPassengerName() << "|"
             << review.getRating() << "|"
             << review.getReviewMessage() << "|"
             << review.getTimestamp() << "\n";
        
        file.close();
    }
}
    catch (const exception& e) {
        cerr << e.what() << endl;
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
        DriverReview review(name, rating, comment, timestamp);
        reviews.push_back(review);
    }
}
