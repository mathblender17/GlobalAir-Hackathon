#include "graph.h"
#include <ctime>
#include <string>
#include <iostream>

//module 2.4
int main() {
    srand(42);

    FlightGraph g;
    g.loadAirports("data/airports.dat");
    g.loadRoutes("data/routes.dat");

    string src, dest;
    cout << "Enter source airport code (e.g., MAA): ";
    cin >> src;
    cout << "Enter destination airport code (e.g., SFO): ";
    cin >> dest;

    vector<string> metrics = {"cost", "delay", "distance"};
    for (const auto& type : metrics) {
        cout << "\n===== SHORTEST PATH BY DIJKSTRA (" << type << ") =====\n";

        auto path = g.dijkstra(src, dest, type);
        if (!path.empty()) {
            cout << "Path: ";
            for (const string& code : path) cout << code << " ";
            cout << endl;

            double total = g.getPathWeight(path, type);
            if (type == "cost") cout << "Total cost: " << total << " $\n";
            else if (type == "delay") cout << "Total delay: " << total << " minutes\n";
            else cout << "Total distance: " << total << " km\n";
        } else {
            cout << "No path found using Dijkstra for " << type << "\n";
        }
    }

    char choice;
    cout << "\nDo you want to run Bellman-Ford for delay? (y/n): ";
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        auto path = g.bellmanFord(src, dest);
        cout << "\n===== SHORTEST PATH BY BELLMAN-FORD (delay) =====\n";
        if (!path.empty()) {
            cout << "Path: ";
            for (const auto& code : path) cout << code << " ";
            cout << "\nTotal delay: " << g.getPathWeight(path, "delay") << " minutes\n";
        } else {
            cout << "No path found using Bellman-Ford.\n";
        }
    }

    return 0;
}

//Module 3

