
// #include <iostream>
// #include <fstream>
// #include <sstream>
// #include <vector>
// #include "baggage.h"
// #include "bst.h"
// #include "minheap.h"

// using namespace std;

// // === Load from CSV file ===
// vector<Baggage> loadBaggageFromCSV(const string& filename) {
//     vector<Baggage> bags;
//     ifstream file(filename);
//     if (!file.is_open()) {
//         cerr << "Error opening baggage CSV file.\n";
//         return bags;
//     }

//     string line;
//     getline(file, line); // Skip header
//     while (getline(file, line)) {
//         stringstream ss(line);
//         string token;
//         Baggage b;

//         getline(ss, token, ',');
//         b.id = stoi(token);

//         getline(ss, b.passengerType, ',');
//         getline(ss, b.baggageType, ',');

//         getline(ss, token, ',');
//         b.riskLevel = stoi(token);


//         getline(ss, token, ',');
//         b.weight = stoi(token);  // <-- NEW


//         bags.push_back(b);
//     }

//     file.close();
//     return bags;
// }

// // === Urgency Calculation ===
// int computeUrgency(const Baggage& b) {
//     int u = 0;
//     if (b.passengerType == "VIP") u += 1;
//     else if (b.passengerType == "Business") u += 2;
//     else u += 3;

//     if (b.baggageType == "Fragile") u += 1;
//     else u += 2;

//     u += b.riskLevel * 2;
//     return u;
// }

// int main() {
//     BaggageBST bst;
//     BaggageMinHeap heap;

//     // Load baggage from CSV
//     string filepath = "../data/baggage_data.csv";
//     vector<Baggage> testBags = loadBaggageFromCSV(filepath);

//     if (testBags.empty()) {
//         cerr << "No baggage data loaded. Exiting.\n";
//         return 1;
//     }

//     for (const auto& bag : testBags) {
//         bst.insert(bag);
//         heap.push(bag);
//     }

//     cout << "\n=== In-Order BST Traversal ===\n";
//     bst.printInOrder();

//     cout << "\n=== Baggage by Category: VIP ===\n";
//     bst.printCategory("VIP");

//     cout << "\n=== Urgent Baggage Processing Order ===\n";
//     while (!heap.empty()) {
//         Baggage b = heap.pop();
//         cout << "Bag ID: " << b.id
//              << ", Urgency: " << computeUrgency(b)
//              << ", Passenger: " << b.passengerType
//              << ", Type: " << b.baggageType
//              << ", Risk: " << b.riskLevel << "\n";
//     }

//     return 0;
// }

/////////////////////////////
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "baggage.h"
#include "bst.h"
#include "minheap.h"
#include "weight_balancer.h"

using namespace std;

// === Load from CSV file ===
vector<Baggage> loadBaggageFromCSV(const string& filename) {
    vector<Baggage> bags;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening baggage CSV file.\n";
        return bags;
    }

    string line;
    getline(file, line); // Skip header
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        Baggage b;

        getline(ss, token, ',');
        b.id = stoi(token);

        getline(ss, b.passengerType, ',');
        getline(ss, b.baggageType, ',');

        getline(ss, token, ',');
        b.riskLevel = stoi(token);

        getline(ss, token, ',');
        b.weight = stoi(token);

        bags.push_back(b);
    }

    file.close();
    return bags;
}

// === Urgency Calculation ===
int computeUrgency(const Baggage& b) {
    int u = 0;
    if (b.passengerType == "VIP") u += 1;
    else if (b.passengerType == "Business") u += 2;
    else u += 3;

    if (b.baggageType == "Fragile") u += 1;
    else u += 2;

    u += b.riskLevel * 2;
    return u;
}

int main() {
    BaggageBST bst;
    BaggageMinHeap heap;

    // Load baggage from CSV
    string filepath = "../data/baggage_data.csv";
    vector<Baggage> testBags = loadBaggageFromCSV(filepath);

    if (testBags.empty()) {
        cerr << "No baggage data loaded. Exiting.\n";
        return 1;
    }

    for (const auto& bag : testBags) {
        bst.insert(bag);
        heap.push(bag);
    }

    cout << "\n=== In-Order BST Traversal ===\n";
    bst.printInOrder();

    cout << "\n=== Baggage by Category: VIP ===\n";
    bst.printCategory("VIP");

    cout << "\n=== Urgent Baggage Processing Order ===\n";
    while (!heap.empty()) {
        Baggage b = heap.pop();
        cout << "Bag ID: " << b.id
             << ", Urgency: " << computeUrgency(b)
             << ", Passenger: " << b.passengerType
             << ", Type: " << b.baggageType
             << ", Risk: " << b.riskLevel
             << ", Weight: " << b.weight << "\n";
    }

    // === Specialized Track: Weight Balancer ===
    // auto [groupA, groupB, weightA, weightB] = balanceBaggageWeight(testBags);
    tuple<vector<Baggage>, vector<Baggage>, int, int> result = balanceBaggageWeight(testBags);
    vector<Baggage> groupA = get<0>(result);
    vector<Baggage> groupB = get<1>(result);
    int weightA = get<2>(result);
    int weightB = get<3>(result);

    cout << "\n=== Compartment A (Weight: " << weightA << ") ===\n";
    for (const auto& b : groupA)
        cout << "Bag ID: " << b.id << ", Weight: " << b.weight << "\n";

    cout << "\n=== Compartment B (Weight: " << weightB << ") ===\n";
    for (const auto& b : groupB)
        cout << "Bag ID: " << b.id << ", Weight: " << b.weight << "\n";

    return 0;
}
