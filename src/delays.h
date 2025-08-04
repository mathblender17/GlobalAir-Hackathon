#ifndef DELAYS_H
#define DELAYS_H

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

struct DelayRecord {
    int year;
    int month;
    string origin;
    string destination;
    double avgDelay;
};

class DelayAnalyzer {
private:
    vector<DelayRecord> records;

    // Part 1 – Monthly delay tabulation
    unordered_map<string, unordered_map<int, vector<double>>> monthlyDelays;
    unordered_map<string, unordered_map<int, double>> avgDelays;

    // Part 2 – Graph for delay chains
    unordered_map<string, vector<pair<string, double>>> graph;

public:
    bool loadFromCSV(const string& filename);

    // Part 1: Delay Trend Analysis
    void computeMonthlyAverages();
    vector<pair<string, double>> getTopDelayAirports(int month, int topN = 5);

    // Part 2: Longest Delay Chain
    void buildDelayGraph();
    double longestDelayFrom(const string& src, unordered_map<string, double>& memo, unordered_set<string>& visiting);
    pair<string, double> findLongestDelayChain();
};

#endif
