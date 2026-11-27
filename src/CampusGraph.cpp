// Purpose: Implementation of the undirected campus graph (adjacency list),
//          its file loaders, display functions, and BFS reachability.
// Author: Drake Thompson
#include "CampusGraph.h"
#include "Utils.h"

#include <fstream>
#include <iostream>
#include <queue>

using namespace std;

// Creates an empty graph.
CampusGraph::CampusGraph() : edgeCount_(0) {}

// Builds directory and file path
string CampusGraph::joinPath(const string& dir, const string& file) {
    if (dir.empty()) return file;
    char last = dir[dir.size() - 1];
    if (last == '/' || last == '\\') return dir + file;
    return dir + "/" + file;
}

// Finds a building by name
int CampusGraph::findBuilding(const string& name) const {
    string wanted = Utils::trim(name);
    for (size_t i = 0; i < names_.size(); ++i)
        if (Utils::equalsIgnoreCase(names_[i], wanted)) return static_cast<int>(i);
    return -1;
}

// Adds a vertex
bool CampusGraph::addBuilding(const string& name, string& reason) {
    string clean = Utils::trim(name);
    if (clean.empty()) {
        reason = "empty building name";
        return false;
    }
    if (findBuilding(clean) != -1) {
        reason = "duplicate building name '" + clean + "'";
        return false;
    }
    names_.push_back(clean);
    adjacency_.push_back(vector<int>());
    return true;
}

// Adds an undirected edge
bool CampusGraph::addConnection(const string& a, const string& b,
                                string& reason) {
    int ia = findBuilding(a);
    if (ia == -1) {
        reason = "unknown building '" + Utils::trim(a) + "'";
        return false;
    }
    int ib = findBuilding(b);
    if (ib == -1) {
        reason = "unknown building '" + Utils::trim(b) + "'";
        return false;
    }
    if (ia == ib) {
        reason = "self-connection on '" + names_[ia] + "'";
        return false;
    }
    // Check edges stored at both endpoints
    for (size_t i = 0; i < adjacency_[ia].size(); ++i) {
        if (adjacency_[ia][i] == ib) {
            reason = "duplicate connection between '" + names_[ia] + "' and '" +
                     names_[ib] + "'";
            return false;
        }
    }
    adjacency_[ia].push_back(ib);
    adjacency_[ib].push_back(ia);
    ++edgeCount_;
    return true;
}

// Loads buildings.txt
void CampusGraph::loadBuildings(const string& dataDir) {
    const string fileName = "buildings.txt";
    int accepted = 0, rejected = 0;
    ifstream in(joinPath(dataDir, fileName).c_str());
    if (!in) {
        cout << "Error: cannot open " << fileName
                  << " (treating it as empty)\n";
    } else {
        string line;
        int lineNo = 0;
        while (getline(in, line)) {
            ++lineNo;
            if (Utils::isBlankOrComment(line)) continue;
            vector<string> fields = Utils::splitFields(line);
            string reason;
            bool ok = false;
            if (fields.size() != 1) {
                reason = "wrong field count (expected 1, found " +
                         to_string(fields.size()) + ")";
            } else {
                ok = addBuilding(fields[0], reason);
            }
            if (ok) {
                ++accepted;
            } else {
                ++rejected;
                cout << "Warning: " << fileName << " line " << lineNo << ": "
                          << reason << "\n";
            }
        }
    }
    cout << fileName << ": " << accepted << " accepted, " << rejected
              << " rejected\n";
}

// Loads connections.txt
void CampusGraph::loadConnections(const string& dataDir) {
    const string fileName = "connections.txt";
    int accepted = 0, rejected = 0;
    ifstream in(joinPath(dataDir, fileName).c_str());
    if (!in) {
        cout << "Error: cannot open " << fileName
                  << " (treating it as empty)\n";
    } else {
        string line;
        int lineNo = 0;
        while (getline(in, line)) {
            ++lineNo;
            if (Utils::isBlankOrComment(line)) continue;
            vector<string> fields = Utils::splitFields(line);
            string reason;
            bool ok = false;
            if (fields.size() != 2) {
                reason = "wrong field count (expected 2, found " +
                         to_string(fields.size()) + ")";
            } else if (fields[0].empty() || fields[1].empty()) {
                reason = "empty building name";
            } else {
                ok = addConnection(fields[0], fields[1], reason);
            }
            if (ok) {
                ++accepted;
            } else {
                ++rejected;
                cout << "Warning: " << fileName << " line " << lineNo << ": "
                          << reason << "\n";
            }
        }
    }
    cout << fileName << ": " << accepted << " accepted, " << rejected
              << " rejected\n";
}

int CampusGraph::buildingCount() const { return static_cast<int>(names_.size()); }
int CampusGraph::connectionCount() const { return edgeCount_; }
int CampusGraph::degree(int index) const {
    return static_cast<int>(adjacency_[index].size());
}

//Returns the name of a building using its index or returns an empty string if the index is invalid
string CampusGraph::buildingName(int index) const
{
    if (index < 0 || index >= buildingCount())
    {
        return "";
    }

    return names_[index];
}

// Prints each building
void CampusGraph::displayGraph() const {
    if (names_.empty()) {
        cout << "No buildings are loaded.\n";
        return;
    }
    cout << "Campus graph:\n";
    for (size_t i = 0; i < names_.size(); ++i) {
        cout << "  " << names_[i] << " -> ";
        if (adjacency_[i].empty()) {
            cout << "(no connections)";
        } else {
            for (size_t j = 0; j < adjacency_[i].size(); ++j) {
                if (j > 0) cout << ", ";
                cout << names_[adjacency_[i][j]];
            }
        }
        cout << "\n";
    }
}

// Prints totals and every building's degree.
void CampusGraph::displayCountsAndDegrees() const {
    if (names_.empty()) {
        cout << "No buildings are loaded.\n";
        cout << "Total buildings: 0\nTotal connections: 0\n";
        return;
    }
    cout << "Total buildings: " << names_.size() << "\n";
    cout << "Total connections: " << edgeCount_ << "\n";
    cout << "Degrees:\n";
    for (size_t i = 0; i < names_.size(); ++i)
        cout << "  " << names_[i] << ": " << adjacency_[i].size() << "\n";
}

// Breadth-first search
CampusGraph::BfsResult CampusGraph::runBfs(int start) const {
    BfsResult result;
    result.distance.assign(names_.size(), -1);
    queue<int> q;
    result.distance[start] = 0;     
    q.push(start);
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        result.order.push_back(current);
        for (size_t i = 0; i < adjacency_[current].size(); ++i) {
            int next = adjacency_[current][i];
            if (result.distance[next] == -1) {
                result.distance[next] = result.distance[current] + 1;
                q.push(next);
            }
        }
    }
    return result;
}

// Prompts are handled by main
bool CampusGraph::bfsReachable(const string& startName) const {
    int start = findBuilding(startName);
    if (start == -1) {
        cout << "Error: unknown building '" << Utils::trim(startName) << "'.\n";
        return false;
    }
    BfsResult r = runBfs(start);
    cout << "Reachable buildings from " << names_[start] << ":\n";
    for (size_t i = 0; i < r.order.size(); ++i)
        cout << "  " << names_[r.order[i]] << " (distance "
                  << r.distance[r.order[i]] << ")\n";
    cout << "Reachable: " << r.order.size() << " of " << names_.size()
              << " buildings\n";
    return true;
}
