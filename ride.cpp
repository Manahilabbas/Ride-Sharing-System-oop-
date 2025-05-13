#include "ride.h"
#include <fstream>
#include <sstream>
#include <cmath>
#include <iostream>

using namespace std;



map<string, int> Ride::zoneIndices;
map<pair<string, string>, int> Ride::zoneMap;


vector<ZonePoint> Ride::loadZonePoints(const string& filename) {
    vector<ZonePoint> points;
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string zonePart, coordPart;
        getline(ss, zonePart, ':');
        getline(ss, coordPart);

        size_t comma = coordPart.find(',');
        if (comma != string::npos) {
            double x = stod(coordPart.substr(0, comma));
            double y = stod(coordPart.substr(comma + 1));
            points.push_back({zonePart, x, y});
        }
    }
    return points;
}

ZonePoint Ride::selectPoint(const vector<ZonePoint>& points, const string& prompt) {
    cout << "\n" << prompt << "\n";
    for (size_t i = 0; i < points.size(); ++i) {
        cout << i + 1 << ". " << points[i].name << " (" << points[i].x << "," << points[i].y << ")\n";
    }
    int choice;
    cout << "Enter choice: ";
    cin >> choice;
    return points[choice - 1];
}

double Ride::calculateFareFromCoords(const ZonePoint& src, const ZonePoint& dest, const string& vehicleType, double discount) {
    // Calculate Euclidean distance
    double distance = sqrt(pow(dest.x - src.x, 2) + pow(dest.y - src.y, 2));

    // Set rate based on vehicle type
    double rate;
    if (vehicleType == "Bike") rate = 10;
    else if (vehicleType == "Rickshaw") rate = 15;
    else if (vehicleType == "Non-AC Car") rate = 20;
    else if (vehicleType == "AC Car") rate = 25;
    else {
        cout << "❌ Invalid vehicle type!\n";
        return -1;
    }

    // Calculate fare
    double fare = distance * rate;

    // Apply discount if any
    if (discount > 0) {
        fare -= fare * (discount / 100.0);
    }

    return fare;
}
