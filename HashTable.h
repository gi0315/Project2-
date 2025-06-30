//Gisselle Sagastume 
//335 project 2 
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "AVLTree.h"
#include <string>
#include <vector>

class HashTable {
public:
    HashTable(size_t size);
    ~HashTable();
    void insert(const std::string& key, const std::string& value);
    std::string* search(const std::string& key);
    void display();

private:
    std::vector<AVLTree*> table;
    size_t hash(const std::string& key);
};

#endif
