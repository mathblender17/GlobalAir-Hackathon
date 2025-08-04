#include <iostream>
#include "baggage.h"
#include "lost_tracker.h"
#include <vector>

using namespace std;

int main() {
    LostBaggageTracker tracker;

    // Sample bags
    vector<Baggage> bags = {
        {101, "VIP", "Fragile", 2, 32},
        {102, "Economy", "Regular", 0, 20},
        {103, "Business", "Fragile", 1, 28},
        {104, "VIP", "Regular", 0, 24},
        {105, "Economy", "Fragile", 2, 18}
    };

    // Insert bags into tracker
    for (const auto& b : bags) {
        tracker.insert(b);
    }

    cout << "\n=== Baggage Flow ===\n";
    tracker.printFlow();

    cout << "\nRemoving Bag ID 103...\n";
    tracker.remove(103);

    cout << "\n=== Updated Baggage Flow ===\n";
    tracker.printFlow();

    int id = 102;
    Baggage* b = tracker.getBaggageInfo(id);
    if (b) {
        cout << "\nInfo for Bag ID " << id << ": Passenger = " << b->passengerType
             << ", Type = " << b->baggageType << ", Risk = " << b->riskLevel
             << ", Weight = " << b->weight << endl;
    } else {
        cout << "\nBag ID " << id << " not found!\n";
    }

    return 0;
}
