#include "gate_sort.h"
#include <iostream>
#include <vector>

int main() {
    vector<Flight> flights;

    if (!loadFlightsFromCSV("../data/gate_flights.csv", flights)) {
        return 1;
    }

    cout << "=== Flights Loaded ===\n";
    for (const auto& f : flights) {
        cout << f.flightID << " | " << f.arrivalTime << " | "
             << f.passengerType << " | " << f.riskLevel << "\n";
    }

    mergeSort(flights, 0, flights.size() - 1);

    cout << "\n=== Gate Allocation (Sorted) ===\n";
    int gate = 1;
    for (const auto& f : flights) {
        cout << "Gate " << gate++ << " -> " << f.flightID << " | "
             << f.arrivalTime << " | " << f.passengerType << " | "
             << f.riskLevel << "\n";
    }

    return 0;
}
