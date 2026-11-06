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

// This makes the ID uppercase, checks for a duplicate and then adds the new node at the end of the bucket's list.
// If there is a node already it is a collision
bool HashTable::insert(const Facility& f) {
    Facility item = f;
    item.id = Utils::toUpper(Utils::trim(f.id));
    int index = hashfunction(item.id);

    // It looks for a duplicate ID in this bucket
    HashNode* current = buckets[index];
    while (current != NULL) {
        if (current->data.id == item.id) {
            return false; // duplicate
        }
        current = current->next;
    }

    HashNode* newNode = new HashNode;
    newNode->data = item;
    newNode->next = NULL;

    if (buckets[index] == NULL) {
        buckets[index] = newNode;
    }
    else {
        collisions++;
        HashNode* last = buckets[index];
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = newNode;
    }
    entries++;
    return true;
}


