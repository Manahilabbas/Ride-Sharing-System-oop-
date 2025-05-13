#ifndef RIDE_H
#define RIDE_H

#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

struct ZonePoint {
    string name;
    double x, y;
};

class Ride {
public:
 

    static double calculateFareFromCoords(const ZonePoint& src, const ZonePoint& dest, const string& vehicleType, double discount = 0.0);
    static vector<ZonePoint> loadZonePoints(const string& filename);
    static ZonePoint selectPoint(const vector<ZonePoint>& points, const string& prompt);
    friend ostream& operator<<(ostream& out, const Ride& ride);
};

#endif
