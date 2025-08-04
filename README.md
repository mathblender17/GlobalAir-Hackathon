#  GlobalAir Hackathon Project

Welcome to **GlobalAir**, a C++-based real-time simulation system for managing and analyzing flight operations, baggage, delays, and optimizations at an international airport scale.

---

##  Project Structure

```
GlobalAir/
├── data/                  # All CSV and .dat input files
│   ├── airports.dat
│   ├── routes.dat
│   ├── delay_data.csv
│   ├── forced_chains_delay_data.csv
│   └── gate_flights.csv

├── src/                   # All source code and compiled binaries
│   ├── graph.cpp / .h           - Flight graph and routing
│   ├── baggage.cpp / .h         - Baggage data and logic
│   ├── bst.cpp / .h             - BST for baggage
│   ├── minheap.cpp / .h         - Urgency-based MinHeap
│   ├── weight_balancer.cpp / .h - DP-based weight balancer
│   ├── lost_tracker.cpp / .h    - Linked List + HashMap for missing bags
│   ├── delays.cpp / .h          - Delay prediction engine
│   ├── gate_sort.cpp / .h       - Gate assignment using Merge Sort
│   ├── dashboard.cpp / .h       - Live dashboard ranking
│   ├── main.cpp
│   ├── main_baggage.cpp
│   ├── main_lost.cpp
│   ├── main_delay.cpp
│   ├── main_gate.cpp
│   ├── main_dashboard.cpp
│   ├── main_route_opt.cpp
│   └── output/                  - Compiled executables
```

---

##  Compilation Instructions

Use the following commands from the `src/` directory:

```bash
g++ -std=c++11 main.cpp graph.cpp -o output/flight.exe
g++ -std=c++11 main_baggage.cpp bst.cpp minheap.cpp weight_balancer.cpp baggage.cpp -o output/baggage.exe
g++ -std=c++11 main_lost.cpp lost_tracker.cpp -o output/lost_tracker.exe
g++ -std=c++11 main_delay.cpp delays.cpp -o output/delay_analysis.exe
g++ -std=c++11 main_gate.cpp gate_sort.cpp -o output/gate_sort.exe
g++ -std=c++11 main_dashboard.cpp dashboard.cpp -o output/dashboard.exe
g++ -std=c++11 main_route_opt.cpp graph.cpp -o output/main_route_opt.exe
```

---

##  Features Overview

| Module                  | Name / Focus                                | Key Features & Techniques                              |
|-------------------------|---------------------------------------------|---------------------------------------------------------|
| **Module 1 & 2**        | Flight Pathfinding                          | Airport Graph, Dijkstra, Bellman-Ford, Adjacency List   |
| **Module 3**            | Baggage Flow & Balancer                     | BST for tracking, MinHeap for urgency, DP for balance   |
| **Special Use Case 1**  | Weight-Constrained Baggage Optimization     | Subset Sum DP for weight-balanced loading               |
| **Module 4**            | Lost Baggage Tracker                        | Doubly Linked List + HashMap (O(1) updates + traversal) |
| **Module 5**            | Historical Delay Analysis                   | Memoized DP, Delay Aggregation, Longest Delay Chain     |
| **Module 6**            | Gate Allocation System                      | Multi-key Merge Sort (Time, Priority, Risk)             |
| **Module 7**            | System Monitoring Dashboard                 | Live aggregation using HashMaps, MinHeaps               |
| **Special Use Case 2**  | Multi-Leg Route Optimizer                   | DFS + Constraints (max hops, cost, layover)             |


---

##  Concepts Used

- Graphs, Dijkstra, Bellman-Ford
- HashMaps, Min Heaps, BSTs
- Memoization, Tabular DP
- Merge Sort (Custom)
- DFS with Constraints (Multi-Hop + Layover + Cost)
- Lazy Aggregation for dashboards

---

##  Documentation

- [ design_doc.md](./design_doc.md) — contains architecture, complexity, trade-offs, and benchmarks.
- CSV examples available under `/data/`.
- [video link 1](https://youtu.be/a_pO8Q3vz54)
- [video link - 2](https://www.youtube.com/watch?v=X-bQgG2l5zQ)
---

##  Author

**Meghraj Patil**  
GitHub: [@mathblender17](https://github.com/mathblender17)  
Email: mp3459@srmist.edu.in

---

##  Note

This is a project built for educational purposes as part of the GlobalAir Hackathon. It demonstrates hands-on DSA in system-level software.
