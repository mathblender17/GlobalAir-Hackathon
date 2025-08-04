#ifndef GATE_SORT_H
#define GATE_SORT_H

#include <string>
#include <vector>

using namespace std;

struct Flight {
    string flightID;
    string arrivalTime;     // Format: "HH:MM"
    string passengerType;   // "VIP", "Business", "Economy"
    string riskLevel;       // "Low", "Medium", "High"
};

// Converts "HH:MM" to minutes since midnight
int timeToMinutes(const string& timeStr);

// Priority mapping
int getPassengerPriority(const string& type);
int getRiskLevelScore(const string& risk);

// Comparator for sorting
bool compareFlights(const Flight& a, const Flight& b);

// Merge sort
void mergeSort(vector<Flight>& flights, int left, int right);
bool loadFlightsFromCSV(const string& filename, vector<Flight>& flights);


#endif
