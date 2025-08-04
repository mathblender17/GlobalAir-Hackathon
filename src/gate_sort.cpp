#include "gate_sort.h"
#include <sstream>
#include <fstream>
#include <sstream>
#include <iostream>
int timeToMinutes(const string& timeStr) {
    int hours, minutes;
    char colon;
    stringstream ss(timeStr);
    ss >> hours >> colon >> minutes;
    return hours * 60 + minutes;
}

int getPassengerPriority(const string& type) {
    if (type == "VIP") return 3;
    if (type == "Business") return 2;
    return 1; // Economy
}

int getRiskLevelScore(const string& risk) {
    if (risk == "Low") return 1;
    if (risk == "Medium") return 2;
    return 3; // High
}

bool compareFlights(const Flight& a, const Flight& b) {
    int timeA = timeToMinutes(a.arrivalTime);
    int timeB = timeToMinutes(b.arrivalTime);
    if (timeA != timeB) return timeA < timeB;

    int priorityA = getPassengerPriority(a.passengerType);
    int priorityB = getPassengerPriority(b.passengerType);
    if (priorityA != priorityB) return priorityA > priorityB;

    int riskA = getRiskLevelScore(a.riskLevel);
    int riskB = getRiskLevelScore(b.riskLevel);
    return riskA < riskB;  // Lower risk first
}

void merge(vector<Flight>& flights, int left, int mid, int right) {
    vector<Flight> leftArr(flights.begin() + left, flights.begin() + mid + 1);
    vector<Flight> rightArr(flights.begin() + mid + 1, flights.begin() + right + 1);

    int i = 0, j = 0, k = left;

    while (i < leftArr.size() && j < rightArr.size()) {
        if (compareFlights(leftArr[i], rightArr[j])) {
            flights[k++] = leftArr[i++];
        } else {
            flights[k++] = rightArr[j++];
        }
    }

    while (i < leftArr.size()) flights[k++] = leftArr[i++];
    while (j < rightArr.size()) flights[k++] = rightArr[j++];
}

void mergeSort(vector<Flight>& flights, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort(flights, left, mid);
        mergeSort(flights, mid + 1, right);
        merge(flights, left, mid, right);
    }
}

bool loadFlightsFromCSV(const string& filename, vector<Flight>& flights) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening CSV file.\n";
        return false;
    }

    string line;
    getline(file, line);  // skip header

    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        Flight f;

        getline(ss, f.flightID, ',');
        getline(ss, f.arrivalTime, ',');
        getline(ss, f.passengerType, ',');
        getline(ss, f.riskLevel, ',');

        flights.push_back(f);
    }

    file.close();
    return true;
}