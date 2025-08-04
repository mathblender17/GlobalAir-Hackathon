#include "bst.h"
#include <iostream>

using namespace std;

BSTNode* BaggageBST::insert(BSTNode* node, Baggage b) {
    if (!node) return new BSTNode(b);
    if (b.id < node->data.id)
        node->left = insert(node->left, b);
    else
        node->right = insert(node->right, b);
    return node;
}

void BaggageBST::insert(Baggage b) {
    root = insert(root, b);
}

void BaggageBST::inorder(BSTNode* node) {
    if (!node) return;
    inorder(node->left);
    cout << "Baggage ID: " << node->data.id << ", Passenger Type: " << node->data.passengerType << endl;
    inorder(node->right);
}

void BaggageBST::printInOrder() {
    inorder(root);
}

void BaggageBST::printByCategory(BSTNode* node, const string& type) {
    if (!node) return;
    printByCategory(node->left, type);
    if (node->data.passengerType == type) {
        cout << "Baggage ID: " << node->data.id << ", Type: " << node->data.baggageType << ", Risk: " << node->data.riskLevel << endl;
    }
    printByCategory(node->right, type);
}

void BaggageBST::printCategory(const string& type) {
    printByCategory(root, type);
}
