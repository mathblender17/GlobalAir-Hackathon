#include "delays.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <set>

bool DelayAnalyzer::loadFromCSV(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening delay data CSV.\n";
        return false;
    }

    string line;
    getline(file, line); // skip header

    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        DelayRecord rec;

        getline(ss, token, ','); rec.year = stoi(token);
        getline(ss, token, ','); rec.month = stoi(token);
        getline(ss, rec.origin, ',');
        getline(ss, rec.destination, ',');
        getline(ss, token, ','); rec.avgDelay = stod(token);

        records.push_back(rec);
        monthlyDelays[rec.origin][rec.month].push_back(rec.avgDelay);
    }

    file.close();
    return true;
}

void DelayAnalyzer::computeMonthlyAverages() {
    for (auto airportIt = monthlyDelays.begin(); airportIt != monthlyDelays.end(); ++airportIt) {
        const string& airport = airportIt->first;
        const unordered_map<int, vector<double>>& monthMap = airportIt->second;

        for (auto monthIt = monthMap.begin(); monthIt != monthMap.end(); ++monthIt) {
            int month = monthIt->first;
            const vector<double>& delays = monthIt->second;

            double sum = 0.0;
            for (size_t i = 0; i < delays.size(); ++i)
                sum += delays[i];

            avgDelays[airport][month] = delays.empty() ? 0.0 : sum / delays.size();
        }
    }
}

vector<pair<string, double>> DelayAnalyzer::getTopDelayAirports(int month, int topN) {
    vector<pair<string, double>> result;
    for (auto it = avgDelays.begin(); it != avgDelays.end(); ++it) {
        const string& airport = it->first;
        const unordered_map<int, double>& delayMap = it->second;

        if (delayMap.find(month) != delayMap.end()) {
            result.push_back(make_pair(airport, delayMap.at(month)));
        }
    }

    sort(result.begin(), result.end(),
         [](const pair<string, double>& a, const pair<string, double>& b) {
             return a.second > b.second;
         });

    if (result.size() > static_cast<size_t>(topN)) {
        result.resize(topN);
    }

    return result;
}

// Part 2: Longest delay chain (multi-hop)

void DelayAnalyzer::buildDelayGraph() {
    for (const auto& rec : records) {
        graph[rec.origin].push_back(make_pair(rec.destination, rec.avgDelay));
    }
}

double DelayAnalyzer::longestDelayFrom(const string& src,
                                       unordered_map<string, double>& memo,
                                       unordered_set<string>& visiting) {
    if (memo.find(src) != memo.end()) return memo[src];
    if (visiting.count(src)) return 0.0;  // cycle detected

    visiting.insert(src);
    double maxDelay = 0.0;

    for (size_t i = 0; i < graph[src].size(); ++i) {
        const string& next = graph[src][i].first;
        double edgeDelay = graph[src][i].second;
        double total = edgeDelay + longestDelayFrom(next, memo, visiting);
        if (total > maxDelay) maxDelay = total;
    }

    visiting.erase(src);
    memo[src] = maxDelay;
    return maxDelay;
}

pair<string, double> DelayAnalyzer::findLongestDelayChain() {
    unordered_map<string, double> memo;
    double maxChain = 0.0;
    string startAirport;

    set<string> airports;
    for (size_t i = 0; i < records.size(); ++i) {
        airports.insert(records[i].origin);
    }

    for (const auto& airport : airports) {
        unordered_set<string> visiting;
        double delay = longestDelayFrom(airport, memo, visiting);
        cout << "Checked " << airport << " → longest delay: " << delay << " mins\n";
        if (delay > maxChain) {
            maxChain = delay;
            startAirport = airport;
        }
    }

    return make_pair(startAirport, maxChain);
}
