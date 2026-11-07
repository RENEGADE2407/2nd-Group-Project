// FacilityDatabase.h loads facilities.txt and keeps facilities in file order and in the hash table. It also lets the user view them and search by ID

#ifndef FACILITYDATABASE_H
#define FACILITYDATABASE_H

#include <string>
#include <vector>
#include "Facility.h"
#include "HashTable.h"
using namespace std;

class FacilityDatabase {
public:
    FacilityDatabase();
    // This loads the facilities file and buildingnames is the list of accepted building names from buildings.txt
    void loadFromFile(string path, string fileLabel, const vector<string>& buldingNames);

    // This prints all facilities in file order and the total
    void displayAll() const;

    // This searches by ID using the hash table and prints the result
    void searchById(string id) const;

    int getAccepted() const { return accepted; }
    int getRejected() const { return rejected; }
    const HashTable& getTable() const { return table; }

private:
    vector<Facility> facilities; // this accepts facilities in file order
    HashTable table;
    int accepted;
    int rejected;
};

#endif

    
