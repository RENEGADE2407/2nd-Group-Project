// FacilityDatabase.cpp loads and checks Facilities.txt, displaying facilities, and searching by ID

#include "FacilityDatabase.h"
#include "Utils.h"
#include <fstream>
#include <iostream>
using namespace std;

// Facility ID validation function
static bool isValidFacilityId(string id) {
    if (id.size() != 4 || id[0] != 'F') {
        return false;
    }
    for (int i = 1; i < 4; i++) {
        if (id[i] < '0' || id[i] > '9') {
            return false;
        }
    }
    return true;
}

// This prints a warning with the file name, line number and reason
static void printWarning(string file, int lineNumber, string reason) {
    cout << "Warning: " << file << " line " << lineNumber
         << ": rejected - " << reason << endl;
}

// this looks for the name in the building list without capitalization and returns the spelling from the list
static string findBuilding(const vector<string>& buildingNames, string name) {
    for (int i = 0; i < (int)buildingNames.size(); i++) {
        if (Utils::equalsIgnoreCase(buildingNames[i], name)) {
            return buildingNames[i];
        }
    }
    return "";
}

FacilityDatabase::FacilityDatabase() {
    accepted = 0;
    rejected = 0;
}
