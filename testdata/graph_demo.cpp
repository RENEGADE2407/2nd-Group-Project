// Purpose: Standalone file to test the graph without main.cpp.
// Author: Drake Thompson
#include "CampusGraph.h"
#include "Utils.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    string dir = (argc > 1) ? argv[1] : "data";
    CampusGraph g;
    g.loadBuildings(dir);
    g.loadConnections(dir);
    g.displayGraph();
    g.displayCountsAndDegrees();
    string name;
    while (cout << "BFS start (blank to quit): ", getline(cin, name)) {
        name = Utils::trim(name);
        if (name.empty()) break;
        g.bfsReachable(name);
    }
    return 0;
}
