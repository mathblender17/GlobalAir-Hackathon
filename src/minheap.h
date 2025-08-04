// minheap.h
#ifndef MINHEAP_H
#define MINHEAP_H

#include "baggage.h"
#include <queue>
#include <vector>

struct BaggagePriority {
    int urgency;
    Baggage bag;

    bool operator>(const BaggagePriority& other) const {
        return urgency > other.urgency;
    }
};

class BaggageMinHeap {
private:
    priority_queue<BaggagePriority, vector<BaggagePriority>, greater<BaggagePriority>> heap;

public:
    void push(Baggage b);
    Baggage pop();
    bool empty() const;
};

#endif
