// HashTable.cpp is a hash table with seperate chaining for facility ID's

#include "HashTable.h"
#include "Utils.h"
#include <iostream>
using namespace std;

// Creates capacity empty buckets
HashTable::HashTable(int cap) {
    if (cap < 1) {
        cap = 1;
    }
    capacity = cap;
    entries = 0;
    collisions = 0;
    for (int i = 0; i < capacity; i++) {
        buckets.push_back(NULL);
    }
}

// This deletes every node in every bucket
HashTable::~HashTable() {
    for (int i = 0; i < capacity; i++) {
        HashNode* current = buckets[i];
        while (current != NULL) {
            HashNode* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }
}

// Hash function
int HashTable::hashFunction(string id) const {
    long h = 0;
    for (int i = 0; i < (int)id.size(); i++) {
        h = (h * 31 + (unsigned char)id[i]) % capacity;
    }
    return (int)h;
}

