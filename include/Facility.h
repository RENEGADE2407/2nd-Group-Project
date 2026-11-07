// Facility.h holds the data for one campus facility

#ifndef FACILITY_H
#define FACILITY_H
#include <string>
using namespace std;

class Facility {
public:
    string id; // Uppercase ID
    string name; // Facility name
    string building; // Building name
    string category; // Category

    // Returns ID, name, building, and category for printing
    string toString() const;
};

#endif
