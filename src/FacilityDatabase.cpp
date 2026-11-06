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
