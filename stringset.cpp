/*
 * Name: Charlie Hartsell
 * Date Submitted: 3/2/21
 * Lab Section: 004
 * Assignment Name: Lab 5
 */

#include "stringset.h"

Stringset::Stringset() : table(4), num_elems(0), size(4) {}

//Used in test cases and testStringset() in main.cpp, do not modify
vector<list<string>> Stringset::getTable() const
{
    return table;
}

//Used in test cases and testStringset() in main.cpp, do not modify
int Stringset::getNumElems() const
{
    return num_elems;
}

//Used in test cases and testStringset() in main.cpp, do not modify
int Stringset::getSize() const
{
    return size;
}

/**
 * Inserts a string into the stringset. Steps:
 * 0. Resize if needed
 * 1. Hash  2. Go to location  3. Does it exist?
 * 4. If yes, nothing. If no, insert at end of linked list
 */
void Stringset::insert(string word)
{
    // Resizing code
    if(num_elems==size) {
        // Calculate the new size
        int newSize = 2 * size;

        // Create a vector lists of strings of the correct size
        vector<list<string>> newTable(newSize);

        // Loop through the old vector
        for(int i = 0; i < size; i++) {
            // Loop through the list and rehash it
            for(list<string>::const_iterator iterator = table[i].begin(); iterator != table[i].end(); iterator++) {
                // Hash the string and obtain the key
                hash<string> stringHash;
                size_t key = stringHash(*iterator) % newTable.size();

                // New vector is empty so we can guarantee the word doesn't exist in the vector yet
                // No need to check for existence
                newTable[key].push_back(*iterator);
            }
        }

        // Old table has been rehashed to newTable, assign newTable to table
        table = newTable;
        size = newSize;
    }

    // Hash the string and obtain the key
    hash<string> stringHash;
    size_t key = stringHash(word) % table.size();

    // If word is not in the list, insert at end of list
    if(!find(word)) {
        table[key].push_back(word);
        num_elems++;
    }
}

/**
 * Determines whether an element exists in the stringset. Steps:
 * 1. Hash  2. Go to location  3. Does it exist?
 * 4. If Y return else return false
 */
bool Stringset::find(string word) const
{
    // Hash the string and obtain the key
    hash<string> stringHash;
    size_t key = stringHash(word) % table.size();

    // Search the linked list at key location
    for(list<string>::const_iterator iterator = table[key].begin(); iterator != table[key].end(); iterator++) {
        // If the word is found, return true
        if(*iterator==word) {return true;}
    }
    
    // Word not found, return false
    return false;
}

/**
 * Removes a word from the stringset. Steps:
 * 1. Determine if it exists
 * 2. If Y erase at position, if N don't do anything
 */
void Stringset::remove(string word)
{
    // If word is found, continue
    if(find(word)) {
        // Hash to find the key
        hash<string> stringHash;
        size_t key = stringHash(word) % table.size();

        // Go to key location, find word, erase it
        for(list<string>::const_iterator iterator = table[key].begin(); iterator != table[key].end(); ++iterator) {
            // If the word is found, erase it
            if(*iterator==word) {
                table[key].erase(iterator);
                num_elems--;
                return;
            }
        }
    }
}