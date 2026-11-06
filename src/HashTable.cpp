// HashTable.cpp is a hash table with seperate chaining for facility ID's

#include "HashTable.h"
#include "Utils.h"
#include <iostream>
using namespace std;

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
