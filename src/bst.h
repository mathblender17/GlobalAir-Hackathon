// bst.h
#ifndef BST_H
#define BST_H

#include "baggage.h"
#include <iostream>

struct BSTNode {
    Baggage data;
    BSTNode* left;
    BSTNode* right;
    BSTNode(Baggage b) : data(b), left(nullptr), right(nullptr) {}
};

class BaggageBST {
private:
    BSTNode* root;

    BSTNode* insert(BSTNode* node, Baggage b);
    void inorder(BSTNode* node);
    void printByCategory(BSTNode* node, const string& category);

public:
    BaggageBST() : root(nullptr) {}

    void insert(Baggage b);
    void printInOrder();
    void printCategory(const string& type); // passengerType
};

#endif
