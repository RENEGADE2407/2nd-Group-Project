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

    
