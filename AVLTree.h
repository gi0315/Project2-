//Gisselle Sagastume 
//335 project 2 
#ifndef AVLTREE_H
#define AVLTREE_H

#include <string>

struct AVLNode {
    std::string key;
    std::string value;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(const std::string& k, const std::string& v)
        : key(k), value(v), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
public:
    AVLTree();
    ~AVLTree();
    void insert(const std::string& key, const std::string& value);
    std::string* search(const std::string& key);
    void display();

private:
    AVLNode* root;

    AVLNode* insert(AVLNode* node, const std::string& key, const std::string& value);
    AVLNode* search(AVLNode* node, const std::string& key);
    void display(AVLNode* node);
    void destroy(AVLNode* node);
    int getHeight(AVLNode* node);
    int getBalance(AVLNode* node);
    AVLNode* rotateRight(AVLNode* y);
    AVLNode* rotateLeft(AVLNode* x);
};

#endif
