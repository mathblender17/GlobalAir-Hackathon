// lost_tracker.h
#ifndef LOST_TRACKER_H
#define LOST_TRACKER_H

#include "baggage.h"
#include <unordered_map>

struct LostBaggageNode {
    Baggage data;
    LostBaggageNode* prev;
    LostBaggageNode* next;

    LostBaggageNode(Baggage b) : data(b), prev(nullptr), next(nullptr) {}
};

class LostBaggageTracker {
private:
    LostBaggageNode* head;
    LostBaggageNode* tail;
    std::unordered_map<int, LostBaggageNode*> idMap;

public:
    LostBaggageTracker();
    ~LostBaggageTracker();

    void insert(const Baggage& b);        // Add baggage to the flow
    void remove(int baggageID);           // Remove from flow
    Baggage* getBaggageInfo(int baggageID); // O(1) metadata fetch
    void printFlow();                     // Print baggage flow in order
};

#endif
