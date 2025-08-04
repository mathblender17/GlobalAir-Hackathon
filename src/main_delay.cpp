#include <iostream>
#include "delays.h"

using namespace std;

int main() {
    DelayAnalyzer analyzer;
    if (!analyzer.loadFromCSV("../data/forced_chains_delay_data.csv")) {
        return 1;
    }

    analyzer.computeMonthlyAverages();

    int month;
    cout << "Enter month (1-12) to view top delay-prone airports: ";
    cin >> month;

    vector<pair<string, double>> topAirports = analyzer.getTopDelayAirports(month);
    cout << "\n=== Top Delay-Prone Airports in Month " << month << " ===\n";
    for (size_t i = 0; i < topAirports.size(); ++i) {
        cout << topAirports[i].first << " -> " << topAirports[i].second << " mins average delay\n";
    }

    // PART 2: Longest delay chain (multi-hop)
    cout << "\nRun longest delay chain analysis? (y/n): ";
    char ch;
    cin >> ch;

    if (ch == 'y' || ch == 'Y') {
        analyzer.buildDelayGraph();
        pair<string, double> result = analyzer.findLongestDelayChain();
        cout << "\n=== Longest Delay Chain (Cumulative) ===\n";
        cout << "Start at: " << result.first << "\n";
        cout << "Total cumulative delay: " << result.second << " mins\n";
    }

    return 0;
}
