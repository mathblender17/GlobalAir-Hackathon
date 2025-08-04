#ifndef FLIGHT_GRAPH_H
#define FLIGHT_GRAPH_H

#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct FlightEdge {
    string destination;
    double distance;
    double avgDelay;
    double cost;

    // For special use case
    string departureTime;
    string arrivalTime;
};

struct Airport {
    string code;    // IATA Code
    string city;
    string country;
    double latitude;
    double longitude;
    bool validCoords = true;
};

class FlightGraph {
private:
    unordered_map<string, Airport> airports; // IATA code → Airport
    unordered_map<string, vector<FlightEdge>> adjList;

public:
    void loadAirports(const string& filename);
    void loadRoutes(const string& filename);
    void displayGraph(); // for debugging
    double haversine(double lat1, double lon1, double lat2, double lon2);
    //MODULE 2
    vector<string> dijkstra(const string& src, const string& dest, const string& weightType);
    vector<string> bellmanFord(const string& src, const string& dest);
    double getPathWeight(const vector<string>& path, const string& weightType);

    //MODULE 2 END

    void findConstrainedRoutes(const string& src, const string& dest);
    void loadRoutesWithTimes(const string& filename);
};

#endif
