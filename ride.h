#ifndef RIDE_H
#define RIDE_H

#include <map>
#include <string>
using namespace std;

class Ride {
public:
    static map<string, int> zoneIndices;
    static map<pair<string, string>, double> distances;
    static void displayZones();
    static double calculateFare(string src, string dest, string vehicleType);
};

#endif
