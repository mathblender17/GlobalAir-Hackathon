#include "lost_tracker.h"
#include <iostream>

using namespace std;

LostBaggageTracker::LostBaggageTracker() : head(nullptr), tail(nullptr) {}

LostBaggageTracker::~LostBaggageTracker() {
    LostBaggageNode* current = head;
    while (current) {
        LostBaggageNode* next = current->next;
        delete current;
        current = next;
    }
    idMap.clear();
}

void LostBaggageTracker::insert(const Baggage& b) {
    auto* node = new LostBaggageNode(b);
    if (!tail) {
        head = tail = node;
    } else {
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
    idMap[b.id] = node;
}

void LostBaggageTracker::remove(int baggageID) {
    if (idMap.find(baggageID) == idMap.end()) return;

    LostBaggageNode* node = idMap[baggageID];

    if (node->prev) node->prev->next = node->next;
    else head = node->next;

    if (node->next) node->next->prev = node->prev;
    else tail = node->prev;

    delete node;
    idMap.erase(baggageID);
}

Baggage* LostBaggageTracker::getBaggageInfo(int baggageID) {
    if (idMap.find(baggageID) != idMap.end()) {
        return &idMap[baggageID]->data;
    }
    return nullptr;
}

void LostBaggageTracker::printFlow() {
    LostBaggageNode* current = head;
    while (current) {
        cout << "Bag ID: " << current->data.id
             << ", Passenger: " << current->data.passengerType
             << ", Type: " << current->data.baggageType
             << ", Risk: " << current->data.riskLevel
             << ", Weight: " << current->data.weight << endl;
        current = current->next;
    }
}
