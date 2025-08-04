#include "dashboard.h"
#include <algorithm>
#include <sstream>
#include <iostream>

int timeToMinutes(const string& timeStr) {
    int hours, minutes;
    char colon;
    stringstream ss(timeStr);
    ss >> hours >> colon >> minutes;
    return hours * 60 + minutes;
}

vector<DelayRoute> Dashboard::getTopDelayRoutes(
    const vector<pair<string, string>>& routes,
    const unordered_map<string, vector<double>>& delayMap,
    int topN) {

    vector<DelayRoute> result;

    for (const auto& r : routes) {
        string key = r.first + "->" + r.second;
        if (delayMap.count(key)) {
            const vector<double>& delays = delayMap.at(key);
            if (!delays.empty()) {
                double sum = 0;
                for (double d : delays) sum += d;
                result.push_back({r.first, r.second, sum / delays.size()});
            }
        }
    }

    sort(result.begin(), result.end(), [](const DelayRoute& a, const DelayRoute& b) {
        return a.avgDelay > b.avgDelay;
    });

    if (result.size() > static_cast<size_t>(topN)) result.resize(topN);
    return result;
}

vector<BaggageJam> Dashboard::getTopBaggageJams(
    const unordered_map<string, int>& jams, int topN) {

    vector<BaggageJam> result;
    for (const auto& pair : jams)
        result.push_back({pair.first, pair.second});

    sort(result.begin(), result.end(), [](const BaggageJam& a, const BaggageJam& b) {
        return a.jamCount > b.jamCount;
    });

    if (result.size() > static_cast<size_t>(topN)) result.resize(topN);
    return result;
}

vector<FlightConnection> Dashboard::getAtRiskFlights(
    const vector<FlightConnection>& connections, int thresholdMinutes) {

    vector<FlightConnection> result;
    for (const auto& conn : connections) {
        int arrival = timeToMinutes(conn.inboundArrival);
        int depart = timeToMinutes(conn.outboundDeparture);
        if ((depart - arrival) < thresholdMinutes)
            result.push_back(conn);
    }
    return result;
}
