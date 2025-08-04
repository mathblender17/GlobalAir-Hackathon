#include "minheap.h"
#include <iostream>

void BaggageMinHeap::push(Baggage b) {
    int urgency = computeUrgency(b);
    BaggagePriority bp = {urgency, b};
    heap.push(bp);
}

Baggage BaggageMinHeap::pop() {
    if (heap.empty()) {
        cerr << "Heap is empty!\n";
        return Baggage();
    }
    Baggage b = heap.top().bag;
    heap.pop();
    return b;
}

bool BaggageMinHeap::empty() const {
    return heap.empty();
}
