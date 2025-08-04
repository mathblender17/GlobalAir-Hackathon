// baggage.h
#ifndef BAGGAGE_MANAGER_H
#define BAGGAGE_MANAGER_H

#include <string>
using namespace std;

struct Baggage {
    int id;
    string passengerType; // "VIP", "Business", "Economy"
    string baggageType;   // "Fragile", "Regular"
    int riskLevel;        // 0 = Low, 1 = Medium, 2 = High
     int weight;
};

int computeUrgency(const Baggage& b); // Defined in baggage.h

#endif
