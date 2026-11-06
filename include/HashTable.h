// HashTable.h is a custom hash table that stores facilities by ID

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <vector>
#include "Facility.h"
using namespace std;

// This is the starting number of buckets. 
const int DEFAULT_CAPACITY = 13;

struct HashNode {
    Facility data;
    HashNode* next;
};

class HashTable {
public:
    HashTable(int capacity = DEFAULT_CAPACITY);
    ~HashTable();

    // This adds a facility and resturns falseif the ID is already used
    bool insert(const Facility& f);

    // This finds a facility by ID and returns a pointer to it or null if not found
    const Facility* find(string id) const;

    // This turns an uppercase ID into a bucket number from 0 to capacity-1
    int hashFunction(string id) const;

    int getCapacity() const { return capacity; }
    int getEntries() const { return entries; }
    int getCollisions() const { return collisions; }

    // this prints what is stored in every bucket
    void printBucket() const;

private:
    HashTable(const HashTable& other);
    HashTable& operator= (const HashTable& other);

    vector<HashNode*> buckets; // first node of each bucket
    int capacity; // number of buckets
    int entries; // number of facilities stored
    int collisions; // goes into a bucket that was not empty
};

#endif
