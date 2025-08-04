#  GlobalAir Hackathon — Technical Design Document

## 1. Project Overview
The GlobalAir system simulates real-time operations across airports including flight scheduling, baggage tracking, delay analysis, and route optimization. The solution is fully implemented in C++ using STL and custom-built data structures for performance and clarity.

---

## 2. System Architecture
**Core Engine**: FlightGraph (Module 1)  
**Interconnected Modules**:
- Pathfinding (Module 2)
- Baggage System (Module 3)
- Delay Analyzer (Module 5)
- Dashboard (Module 7)

Each module interacts with shared datasets and produces analytics or actions that feed into the dashboard and optimizers.

---

## 3. Module-wise Breakdown

###  Module 1 & 2: Flight Graph + Shortest Path
- **Algorithms**: Dijkstra, Bellman-Ford
- **Data Structures**: `unordered_map<string, vector<FlightEdge>>`
- **Trade-off**: Used adjacency list for sparse graph efficiency
- **Time Complexity**:
  - Dijkstra: O((V + E) log V)
  - Bellman-Ford: O(VE)
- **Space Complexity**: O(V + E)

###  Module 3: Baggage Flow & Weight Balance
- **Data Structures**:
  - BST (Sorted Insertion)
  - MinHeap (Urgency Queue)
  - DP for Weight Balance (Subset Sum)
- **Trade-offs**:
  - Heap over full sort per urgency poll
  - DP for perfect weight balance (not greedy)
- **Time Complexity**:
  - Heap ops: O(log n)
  - BST: O(log n)
  - DP: O(n * W)
- **Space Complexity**: O(n + W)

###  Module 4: Lost Baggage Tracker
- **Structures**: Doubly Linked List + Hash Table
- **Trade-off**: DLL for O(1) deletion + ordered flow
- **Time Complexity**:
  - Insertion/Deletion/Search: O(1)
- **Space Complexity**: O(n)

###  Module 5: Delay Analyzer
- **Aggregation**: HashMap of vectors by month
- **Chain Analysis**: DFS + Memoization
- **Trade-off**: DFS chosen for variable weights and memo speedup
- **Time Complexity**:
  - Monthly Avg: O(n)
  - Longest Chain: O(V + E)
- **Space Complexity**: O(V + E)

###  Module 6: Gate Allocation
- **Sorting Method**: Merge Sort
- **Sort By**: Time → Passenger Type → Risk
- **Trade-off**: Merge Sort ensures stable & predictable sorting
- **Time Complexity**: O(n log n)
- **Space Complexity**: O(n)

###  Module 7: Dashboard
- **Tech**: Live aggregation using hash maps, minheaps, and sorting
- **Trade-offs**:
  - Lazy updates used for delay/jam scores
- **Time Complexity**:
  - Ranking: O(n log n)
- **Space Complexity**: O(n)

###  Module 8: Multi-Leg Route Optimizer
- **Algorithm**: DFS with constraints (cost, hops, layover)
- **Trade-offs**: DFS allows pruning early and backtracking
- **Constraints**: max 2 hops, ≤ $1200, ≤ 3hr layover
- **Time Complexity**: O(b^k), practical: O(valid paths)
- **Space Complexity**: O(p * k)

---

## 4. Pseudocode Snippets

**DFS with Constraints (Module 8)**:
```cpp
dfs(curr, dest, path, cost, hops) {
    if (hops > 2 || cost > 1200) return;
    if (curr == dest) save path;
    for (neighbor : graph[curr]) {
        if (layover_ok(curr, neighbor)) 
            dfs(neighbor, dest, path + neighbor, cost + c, hops + 1);
    }
}
```

**DP Subset-Sum for Weight Balance (Module 3)**:
```cpp
dp[0][0] = true
for (i = 1 to n)
  for (j = 0 to W)
    dp[i][j] = dp[i-1][j] || dp[i-1][j - wt[i]]
```

---

## 5. Benchmarks (Empirical)
| Module      | Dataset Size   | Time        |
|-------------|----------------|-------------|
| Flight Load | 6000+ airports | < 2 sec     |
| DFS Routes  | 500 paths → 30 valid | ~1 sec |
| Merge Sort  | 100 flights    | < 0.05 sec  |
| Dashboard   | Live Ranking   | Instant     |

---

## 6. Conclusion
-  All modules are independently tested and integrated.
-  Custom DS used only where performance was critical.
-  Real-time simulation achieved via smart pruning, hashing, sorting.

###  Future Improvements
- SQLite or JSON-based persistent caching
- Visualization dashboard in HTML or Qt
- Airport-level simulations of congestion

---

## Appendix
**Time and Space Complexities Table**: See Module breakdown  
**Data Sources**: airports.dat, routes.dat, *.csv  
**Author**: Meghraj Patil