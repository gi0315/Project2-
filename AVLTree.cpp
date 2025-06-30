#include "AVLTree.h"
#include <iostream>
#include <algorithm>

// sets root to null
AVLTree::AVLTree() : root(nullptr) {}

// this will delete the whole tree
AVLTree::~AVLTree() { destroy(root); }

// Insert a key-value pair 
void AVLTree::insert(const std::string& key, const std::string& value) {
    root = insert(root, key, value);
}

// Search for a key in the AVL tree
std::string* AVLTree::search(const std::string& key) {
    AVLNode* result = search(root, key);
    return result ? &result->value : nullptr;
}

// Display the whole tree in order with sepertation lines. 
void AVLTree::display() {
    if (root) {
        std::cout << "========================\n";
        display(root);
        std::cout << "========================\n\n";
    }
}

// Recursive insert helper for balancing and placement
AVLNode* AVLTree::insert(AVLNode* node, const std::string& key, const std::string& value) {
    if (!node) return new AVLNode(key, value);

    if (key < node->key)
        node->left = insert(node->left, key, value);
    else if (key > node->key)
        node->right = insert(node->right, key, value);
    else
        node->value = value;  // Update if key already exists

    // this basically updates the height 
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

    // this will keep the balance in check 
    int balance = getBalance(node);

    // Rotate if needed and when needed 
    if (balance > 1 && key < node->left->key)  // Left Left
        return rotateRight(node);

    if (balance < -1 && key > node->right->key)  // Right Right
        return rotateLeft(node);

    if (balance > 1 && key > node->left->key) {  // Left Right
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && key < node->right->key) {  // Right Left
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Recursive search helper
AVLNode* AVLTree::search(AVLNode* node, const std::string& key) {
    if (!node) return nullptr;
    if (key == node->key) return node;
    if (key < node->key) return search(node->left, key);
    return search(node->right, key);
}

// Recursive display helper
void AVLTree::display(AVLNode* node) {
    if (node) {
        display(node->left);
        std::cout << node->key << " -> " << node->value << "\n";
        std::cout << "------------------------\n";  // separator for each book
        display(node->right);
    }
}

// Deletes all nodes in the tree
void AVLTree::destroy(AVLNode* node) {
    if (node) {
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
}

// Get height of a node
int AVLTree::getHeight(AVLNode* node) {
    return node ? node->height : 0;
}

// Get balance factor for a node
int AVLTree::getBalance(AVLNode* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

// Right rotation to balance
AVLNode* AVLTree::rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + std::max(getHeight(y->left), getHeight(y->right));
    x->height = 1 + std::max(getHeight(x->left), getHeight(x->right));

    return x;
}

// Left rotation to balance
AVLNode* AVLTree::rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + std::max(getHeight(x->left), getHeight(x->right));
    y->height = 1 + std::max(getHeight(y->left), getHeight(y->right));

    return y;
}