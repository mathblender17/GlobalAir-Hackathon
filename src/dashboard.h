#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

using namespace std;

struct DelayRoute {
    string origin;
    string destination;
    double avgDelay;
};

struct BaggageJam {
    string checkpoint;
    int jamCount;
};

struct FlightConnection {
    string inboundID;
    string outboundID;
    string inboundArrival;     // "HH:MM"
    string outboundDeparture;  // "HH:MM"
};

class Dashboard {
public:
    // Core functions
    vector<DelayRoute> getTopDelayRoutes(const vector<pair<string, string>>& routes,
                                         const unordered_map<string, vector<double>>& delayMap,
                                         int topN = 5);

    vector<BaggageJam> getTopBaggageJams(const unordered_map<string, int>& jams,
                                         int topN = 5);

    vector<FlightConnection> getAtRiskFlights(const vector<FlightConnection>& connections,
                                              int thresholdMinutes = 30);
};

int timeToMinutes(const string& timeStr);

#endif
