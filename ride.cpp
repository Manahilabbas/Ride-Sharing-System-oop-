#include "ride.h"
#include <iostream>
using namespace std;

map<string, int> Ride::zoneIndices = {
    {"Saddar", 0}, {"DHA", 1}, {"Clifton", 2}, {"Gulshan-e-Iqbal", 3},
    {"PECHS", 4}, {"North Karachi", 5}, {"Nazimabad", 6}, {"Gulberg", 7},
    {"Malir", 8}, {"Korangi", 9}
};

map<pair<string, string>, double> Ride::distances = {
    {{"Saddar", "DHA"}, 10}, {{"Saddar", "Clifton"}, 5}, {{"DHA", "Gulshan-e-Iqbal"}, 18},
    {{"Clifton", "Gulshan-e-Iqbal"}, 15}, {{"PECHS", "North Karachi"}, 14},
    {{"Saddar", "North Karachi"}, 20}, {{"Clifton", "Korangi"}, 16},
    {{"Malir", "Nazimabad"}, 22}, {{"Korangi", "Gulshan-e-Iqbal"}, 13},
    {{"DHA", "North Karachi"}, 25}, {{"Nazimabad", "Gulberg"}, 6},
    {{"PECHS", "Malir"}, 12}, {{"Saddar", "PECHS"}, 4}, {{"Gulberg", "Korangi"}, 17}
};

void Ride::displayZones() {
    cout << "\nAvailable Zones:\n";
    for (const auto& z : zoneIndices) {
        cout << "- " << z.first << endl;
    }
}

double Ride::calculateFare(string src, string dest, string vehicleType) {
    pair<string, string> key1 = {src, dest}, key2 = {dest, src};
    double baseRate = 30.0;
    double distance = distances.count(key1) ? distances[key1] : distances[key2];
    double multiplier = (vehicleType == "Bike") ? 1.0 :
                        (vehicleType == "Rickshaw") ? 1.2 :
                        (vehicleType == "Non-AC Car") ? 1.5 :
                        (vehicleType == "AC Car") ? 2.0 : 1.0;
    return distance * baseRate * multiplier;
}
