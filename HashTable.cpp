//Gisselle Sagastume 
//335 project 2 

#include "HashTable.h"
#include <functional>  // for std::hash
#include <iostream>

// Constructor: creates table with given size and fills with empty AVL trees
HashTable::HashTable(size_t size) : table(size, nullptr) {
    for (auto& bucket : table)
        bucket = new AVLTree();
}

// Destructor: deletes all AVL trees
HashTable::~HashTable() {
    for (auto bucket : table)
        delete bucket;
}

// Insert a book title and info into the correct bucket (AVL tree)
void HashTable::insert(const std::string& key, const std::string& value) {
    table[hash(key)]->insert(key, value);
}

// Search for a book by title
std::string* HashTable::search(const std::string& key) {
    return table[hash(key)]->search(key);
}

// Display all books in all slots 
void HashTable::display() {
    for (auto bucket : table) {
        bucket->display();
    }
}

// Hash function: turns title into a hash index
size_t HashTable::hash(const std::string& key) {
    return std::hash<std::string>{}(key) % table.size();
}
