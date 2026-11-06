// This file implements the facility class

#include "Facility.h"
using namespace std;

// This allows all fours fields to be on one line for printing
string Facility::toString() const { return id + " | " + name + " | " + building + " | " + category;
