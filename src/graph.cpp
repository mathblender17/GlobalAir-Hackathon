#include "graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <queue>
#include <set>
#include <limits>
#include <stack>
#include <algorithm>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
const double EARTH_RADIUS_KM = 6371.0;

double FlightGraph::haversine(double lat1, double lon1, double lat2, double lon2) {
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;

    lat1 = lat1 * M_PI / 180.0;
    lat2 = lat2 * M_PI / 180.0;

    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);
    double c = 2 * asin(sqrt(a));
    return EARTH_RADIUS_KM * c;
}

///v3 load airports
void FlightGraph::loadAirports(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening airport file\n";
        return;
    }

    string line;
    int lineNumber = 0, success = 0, fail = 0;

    while (getline(file, line)) {
        ++lineNumber;
        vector<string> tokens;
        string token;
        bool inQuotes = false;
        stringstream field;

        for (char c : line) {
            if (c == '"') inQuotes = !inQuotes;
            else if (c == ',' && !inQuotes) {
                tokens.push_back(field.str());
                field.str(""); field.clear();
            } else {
                field << c;
            }
        }
        tokens.push_back(field.str()); // last field

        if (tokens.size() < 8) {
            ++fail;
            continue;
        }

        string code = tokens[4];
        if (code == "\\N" || code.empty()) {
            ++fail;
            continue;
        }

        Airport ap;
        ap.code = code;
        ap.city = tokens[2];
        ap.country = tokens[3];

        try {
            ap.latitude = stod(tokens[6]);
            ap.longitude = stod(tokens[7]);
            ap.validCoords = true;
        } catch (...) {
            ap.latitude = 0;
            ap.longitude = 0;
            ap.validCoords = false;
        }

        airports[code] = ap;
        ++success;
    }

    cout << " Airports loaded: " << success << ", Skipped: " << fail << "\n";
    file.close();
}



////

void FlightGraph::loadRoutes(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening routes file\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        vector<string> tokens;

        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() < 6) continue;

        string srcCode = tokens[2];
        string dstCode = tokens[4];

        if (airports.find(srcCode) != airports.end() && airports.find(dstCode) != airports.end()) {
            Airport src = airports[srcCode];
            Airport dst = airports[dstCode];
            // Skip if coordinates are invalid
            if (!src.validCoords || !dst.validCoords) continue;

            double dist = haversine(src.latitude, src.longitude, dst.latitude, dst.longitude);

            FlightEdge edge;
            edge.destination = dstCode;
            edge.distance = dist;
            //random
            // edge.avgDelay = rand() % 60;               // Simulated delay: 0–59 mins
            // edge.cost = 50 + (rand() % 451);           // Simulated cost: $50–500
            //deterministic
            edge.cost = 0.1 * dist;
            edge.avgDelay = dist / 100;

            adjList[srcCode].push_back(edge);
        }
    }

    file.close();
}

//v2 display graph
void FlightGraph::displayGraph() {
    for (const auto& pair : adjList) {
        const string& src = pair.first;
        const auto& edges = pair.second;

        cout << src << " -> ";
        for (const auto& e : edges) {
            cout << e.destination << " (" 
                 << e.distance << " km, "
                 << e.avgDelay << " min delay, $"
                 << e.cost << "), ";
        }
        cout << "\n";
    }
}
//MODULE 1 END

//MODULE 2 START
vector<string> FlightGraph::dijkstra(const string& src, const string& dest, const string& weightType) {
    unordered_map<string, double> dist;
    unordered_map<string, string> parent;
    set<string> visited;

    for (const auto& pair : airports) {
        dist[pair.first] = numeric_limits<double>::infinity();
    }
    dist[src] = 0.0;

    priority_queue<pair<double, string>, vector<pair<double, string>>, greater<pair<double, string>>> pq;
    pq.push(make_pair(0.0, src));

    while (!pq.empty()) {
        pair<double, string> top = pq.top(); pq.pop();
        double currDist = top.first;
        string curr = top.second;

        if (visited.count(curr)) continue;
        visited.insert(curr);

        if (curr == dest) break;

        for (const auto& edge : adjList[curr]) {
            double weight = 0;
            if (weightType == "distance") weight = edge.distance;
            else if (weightType == "cost") weight = edge.cost;
            else if (weightType == "delay") weight = edge.avgDelay;
            else continue;

            double newDist = dist[curr] + weight;
            if (newDist < dist[edge.destination]) {
                dist[edge.destination] = newDist;
                parent[edge.destination] = curr;
                pq.push(make_pair(newDist, edge.destination));
            }
        }
    }

    vector<string> path;
    if (dist[dest] == numeric_limits<double>::infinity()) {
        cout << "No path found from " << src << " to " << dest << "\n";
        return path;
    }

    for (string at = dest; at != src; at = parent[at]) {
        path.push_back(at);
    }
    path.push_back(src);
    reverse(path.begin(), path.end());
    //optional - double
    // cout << "Path: ";
    // for (const auto& code : path) cout << code << " ";
    // cout << "\n";

    // cout << "Total " << weightType << ": " << dist[dest];
    // if (weightType == "cost") cout << " $\n";
    // else if (weightType == "delay") cout << " minutes\n";
    // else if (weightType == "distance") cout << " km\n";
    // else cout << "\n";

    return path;
}
// bellman ford
std::vector<std::string> FlightGraph::bellmanFord(const std::string& src, const std::string& dest) {
    std::unordered_map<std::string, double> dist;
    std::unordered_map<std::string, std::string> parent;

    // Initialize distances
    for (auto it = airports.begin(); it != airports.end(); ++it) {
        dist[it->first] = std::numeric_limits<double>::infinity();
    }
    dist[src] = 0.0;

    int V = airports.size();

    // Relax edges V - 1 times
    for (int i = 0; i < V - 1; ++i) {
        for (auto it = adjList.begin(); it != adjList.end(); ++it) {
            const std::string& u = it->first;
            const std::vector<FlightEdge>& edges = it->second;

            for (const auto& edge : edges) {
                if (dist[u] != std::numeric_limits<double>::infinity() &&
                    dist[u] + edge.avgDelay < dist[edge.destination]) {
                    dist[edge.destination] = dist[u] + edge.avgDelay;
                    parent[edge.destination] = u;
                }
            }
        }
    }

    // Detect negative-weight cycles
    for (auto it = adjList.begin(); it != adjList.end(); ++it) {
        const std::string& u = it->first;
        const std::vector<FlightEdge>& edges = it->second;

        for (const auto& edge : edges) {
            if (dist[u] != std::numeric_limits<double>::infinity() &&
                dist[u] + edge.avgDelay < dist[edge.destination]) {
                std::cout << "Graph contains a negative-weight cycle.\n";
                return {};
            }
        }
    }

    // Reconstruct path
    std::vector<std::string> path;
    if (dist[dest] == std::numeric_limits<double>::infinity()) {
        std::cout << "No path found from " << src << " to " << dest << "\n";
        return path;
    }

    for (std::string at = dest; at != src; at = parent[at]) {
        path.push_back(at);
    }
    path.push_back(src);
    std::reverse(path.begin(), path.end());

    std::cout << "===== SHORTEST PATH BY BELLMAN-FORD (delay) =====\n";
    std::cout << "Path: ";
    for (const auto& code : path) {
        std::cout << code << " ";
    }
    std::cout << "\nTotal delay: " << dist[dest] << " minutes\n";

    return path;
}
//getPathWeight
double FlightGraph::getPathWeight(const vector<string>& path, const string& weightType) {
    double total = 0;
    for (size_t i = 0; i + 1 < path.size(); ++i) {
        const string& from = path[i];
        const string& to = path[i + 1];

        for (const auto& edge : adjList[from]) {
            if (edge.destination == to) {
                if (weightType == "cost") total += edge.cost;
                else if (weightType == "delay") total += edge.avgDelay;
                else if (weightType == "distance") total += edge.distance;
                break;
            }
        }
    }
    return total;
}


//MODULE 2 END
int timeToMinutes(const string& t) {
    int h, m;
    char colon;
    stringstream ss(t);
    ss >> h >> colon >> m;
    return h * 60 + m;
}

void dfsConstrained(const string& curr, const string& dest, vector<string>& path,
                    double cost, int hops, int lastArrival,
                    const unordered_map<string, vector<FlightEdge>>& adj,
                    vector<vector<string>>& results, double maxCost, int maxHops, int maxLayover) {
    if (cost > maxCost || hops > maxHops) return;

    if (curr == dest && hops <= maxHops && cost <= maxCost) {
        results.push_back(path);
        return;
    }

    if (adj.find(curr) == adj.end()) return;

    for (const auto& edge : adj.at(curr)) {
        int dep = timeToMinutes(edge.departureTime);
        int arr = timeToMinutes(edge.arrivalTime);
        int layover = (lastArrival == -1) ? 0 : dep - lastArrival;
        if (lastArrival != -1 && layover > maxLayover) continue;

        path.push_back(edge.destination);
        dfsConstrained(edge.destination, dest, path, cost + edge.cost, hops + 1,
                       arr, adj, results, maxCost, maxHops, maxLayover);
        path.pop_back();
    }
}

void FlightGraph::findConstrainedRoutes(const string& src, const string& dest) {
    vector<string> path = {src};
    vector<vector<string>> results;

    dfsConstrained(src, dest, path, 0.0, 0, -1, adjList, results, 1200.0, 2, 180);

    if (results.empty()) {
        cout << "No valid routes found under constraints.\n";
    } else {
        cout << "Valid Routes under constraints:\n";
        // for (const auto& p : results) {
        //     for (size_t i = 0; i < p.size(); ++i) {
        //         cout << p[i];
        //         if (i < p.size() - 1) cout << " -> ";
        //     }
        //     cout << "\n";
        // }
         set<string> uniquePaths;

        for (const auto& p : results) {
            stringstream ss;
            for (size_t i = 0; i < p.size(); ++i) {
                ss << p[i];
                if (i < p.size() - 1) ss << " -> ";
            }
            uniquePaths.insert(ss.str());
        }

        for (const auto& route : uniquePaths) {
            cout << route << "\n";
        }

    }
}
string minutesToTime(int minutes) {
    int h = minutes / 60;
    int m = minutes % 60;
    stringstream ss;
    ss << setw(2) << setfill('0') << h << ":"
       << setw(2) << setfill('0') << m;
    return ss.str();
}

void FlightGraph::loadRoutesWithTimes(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening routes file (with times)\n";
        return;
    }

    srand(time(0));
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        vector<string> tokens;

        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() < 6) continue;

        string srcCode = tokens[2];
        string dstCode = tokens[4];

        if (airports.count(srcCode) && airports.count(dstCode)) {
            Airport src = airports[srcCode];
            Airport dst = airports[dstCode];

            if (!src.validCoords || !dst.validCoords) continue;

            double dist = haversine(src.latitude, src.longitude, dst.latitude, dst.longitude);
            FlightEdge edge;
            edge.destination = dstCode;
            edge.distance = dist;
            edge.cost = 0.1 * dist;
            edge.avgDelay = dist / 100;

            // Simulate departure (300–1200 mins → 5:00 to 20:00)
            int dep = 300 + rand() % 901;
            double duration = dist / 800.0;               // hrs
            int arr = dep + int(duration * 60);           // minutes

            edge.departureTime = minutesToTime(dep);
            edge.arrivalTime = minutesToTime(arr);

            adjList[srcCode].push_back(edge);
        }
    }

    file.close();
}
