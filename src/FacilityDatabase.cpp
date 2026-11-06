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

// this reads faciliteis.txt one line at a time. Field count, empty fields, ID format, unknown building and duplicate ID is the order they are checked in
void FacilityDatabase::loadFromFile(string path, string fileLabel, const vector<string>& buildingNames) {
    ifstream file(path.c_str());
    if (!file) {
        cout << "Error: can not open file " << fileLabel << " (" << path << "). Treating it as empty." << endl;
    }
    else {
        string rawLine;
        int lineNumber = 0;
        while (getline(file, rawLine)) {
            lineNumber++;
            string line = Utils::trim(rawLine);   // also removes a Windows \r
            if (Utils::isBlankOrComment(line)) {
                continue;
            }

            vector<string> fields = Utils::splitFields(line);
            if (fields.size() != 4) {
                printWarning(fileLabel, lineNumber,
                    "wrong number of fields (need FacilityID|FacilityName|BuildingName|Category)");
                rejected++;
                continue;
            }
            if (fields[0] == "" || fields[1] == "" || fields[2] == "" || fields[3] == "") {
                printWarning(fileLabel, lineNumber, "a required field is empty");
                rejected++;
                continue;
            }

            string id = Utils::toUpper(fields[0]);   // uppercase BEFORE checking or hashing
            if (!isValidFacilityId(id)) {
                printWarning(fileLabel, lineNumber, "invalid ID '" + id +
                    "' (must be F followed by exactly three digits)");
                rejected++;
                continue;
            }
