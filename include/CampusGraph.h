// Purpose: Undirected, unweighted campus graph (buildings = vertices,
//          walkways = edges) stored as an adjacency list, plus BFS reachability.
// Author: Drake Thompson
#ifndef CAMPUS_GRAPH_H
#define CAMPUS_GRAPH_H

#include <string>
#include <vector>

using namespace std;

class CampusGraph {
public:
    CampusGraph();

    // Loads buildings.txt | prints warnings and one load summary line.
    void loadBuildings(const string& dataDir);
    // Loads connections.txt | prints warnings and one load summary line.
    void loadConnections(const string& dataDir);

    // Adds a building.
    bool addBuilding(const string& name, string& reason);
    // Adds an undirected edge by building names.
    bool addConnection(const string& a, const string& b, string& reason);
    // Index of building
    int findBuilding(const string& name) const;

    // Getters
    int buildingCount() const;
    int connectionCount() const; 
    int degree(int index) const;

    // Display
    void displayGraph() const;            
    void displayCountsAndDegrees() const; 
    // BFS from the named building
    bool bfsReachable(const string& startName) const; // BFS-1..3

private:
    vector<string> names_;
    vector<vector<int> > adjacency_;
    int edgeCount_;

    // Result of one BFS run
    struct BfsResult {
        vector<int> order;
        vector<int> distance;
    };
    BfsResult runBfs(int start) const;
    static string joinPath(const string& dir, const string& file);
};

#endif
