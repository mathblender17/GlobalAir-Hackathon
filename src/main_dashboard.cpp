#include "dashboard.h"
#include <iostream>

int main() {
    Dashboard dash;

    // Simulated delay route data
    vector<pair<string, string>> routes = {
        {"DEL", "BOM"}, {"MAA", "BLR"}, {"CCU", "DEL"},
        {"PNQ", "MAA"}, {"BOM", "HYD"}, {"BLR", "SFO"}
    };

    unordered_map<string, vector<double>> delayMap = {
        {"DEL->BOM", {23.5, 24.0, 22.0}},
        {"MAA->BLR", {30.0, 28.5}},
        {"CCU->DEL", {20.0, 21.0}},
        {"PNQ->MAA", {40.0, 42.5}},
        {"BOM->HYD", {18.5, 19.0}},
        {"BLR->SFO", {50.0, 55.0, 52.5}}
    };

    // Simulated baggage jam counts
    unordered_map<string, int> jams = {
        {"T1", 15}, {"T2", 23}, {"GateA", 9}, {"Belt4", 30}, {"Belt7", 12}
    };

    // Simulated flight connections
    vector<FlightConnection> connections = {
        {"AI123", "AI456", "08:30", "09:00"},
        {"BA789", "BA101", "07:45", "08:10"},
        {"QR777", "QR888", "09:00", "09:50"},
        {"LH909", "LH303", "10:30", "11:45"},
        {"EM505", "EM909", "11:20", "11:40"} // risky
    };

    cout << "===== Top Delay-Prone Routes =====\n";
    auto delays = dash.getTopDelayRoutes(routes, delayMap);
    for (const auto& r : delays) {
        cout << r.origin << " -> " << r.destination << ": " << r.avgDelay << " mins\n";
    }

    cout << "\n===== Baggage Jam Hotspots =====\n";
    auto jamList = dash.getTopBaggageJams(jams);
    for (const auto& j : jamList) {
        cout << j.checkpoint << ": " << j.jamCount << " jams\n";
    }

    cout << "\n===== Flights at Risk (Short Connections) =====\n";
    auto atRisk = dash.getAtRiskFlights(connections);
    for (const auto& f : atRisk) {
        cout << f.inboundID << " -> " << f.outboundID
             << " (" << f.inboundArrival << " -> " << f.outboundDeparture << ")\n";
    }

    return 0;
}
