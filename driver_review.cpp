#include "driver_review.h"
#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;

DriverReview::DriverReview() {}

DriverReview::DriverReview(const string& name, int rate, const string& message, const string& time)
    : passengerName(name), rating(rate), reviewMessage(message), timestamp(time) {}

DriverReview DriverReview::fromString(const string& line) {  // Removed the '&' symbol
    stringstream ss(line);
    string name, ratingStr, message, time;

    getline(ss, name, '|');
    getline(ss, ratingStr, '|');
    getline(ss, message, '|');
    getline(ss, time);

    return DriverReview(name, stoi(ratingStr), message, time);
}

ostream& operator<<(ostream& out, const DriverReview& r) {
    out << r.timestamp << " - " << r.passengerName
        << " rated " << r.rating << " stars\n"
        << "\"" << r.reviewMessage << "\"\n";
    return out;
}

void displayReviewsFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        DriverReview r = DriverReview::fromString(line);
        cout << r << endl;
    }

    file.close();
}
