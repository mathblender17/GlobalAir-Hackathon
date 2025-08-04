#include "graph.h"
#include <iostream>

// int main() {
//     FlightGraph g;
//     g.loadAirports("data/airports.dat");
//     g.loadRoutes("data/routes.dat");  // Make sure this contains time info!

//     string src, dest;
//     cout << "Enter source airport code: ";
//     cin >> src;
//     cout << "Enter destination airport code: ";
//     cin >> dest;

//     g.findConstrainedRoutes(src, dest);
//     return 0;
// }
int main() {
    FlightGraph g;
    // g.loadAirports("..data/airports.dat");

    // // Call this instead of loadRoutes
    // g.loadRoutesWithTimes("..data/routes.dat");
    g.loadAirports("C:/Users/Admin/OneDrive/Desktop/vscode/GlobalAir/data/airports.dat");
    g.loadRoutesWithTimes("C:/Users/Admin/OneDrive/Desktop/vscode/GlobalAir/data/routes.dat");


    string src, dest;
    cout << "Enter source airport code: ";
    cin >> src;
    cout << "Enter destination airport code: ";
    cin >> dest;

    g.findConstrainedRoutes(src, dest);
    return 0;
}

