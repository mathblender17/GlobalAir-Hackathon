#include "weight_balancer.h"
#include <numeric>
#include <unordered_map>
#include <iostream>
using namespace std;

// DP table to trace the partition
tuple<vector<Baggage>, vector<Baggage>, int, int> balanceBaggageWeight(const vector<Baggage>& bags) {
    int n = bags.size();
    int totalWeight = 0;
    for (const auto& b : bags) totalWeight += b.weight;

    int target = totalWeight / 2;

    // DP table: dp[i][j] = true if weight j can be formed with first i bags
    vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));
    dp[0][0] = true;

    // Tracking for backtracking
    unordered_map<int, vector<int>> prevBagUsed;

    for (int i = 1; i <= n; ++i) {
        int w = bags[i - 1].weight;
        for (int j = 0; j <= target; ++j) {
            if (dp[i - 1][j]) {
                dp[i][j] = true;
                    if (j + w <= target) {
                        dp[i][j + w] = true;
                        prevBagUsed[j + w] = prevBagUsed[j];
                        prevBagUsed[j + w].push_back(i - 1);
                    }


                // dp[i][j] = true;
                // dp[i][j + w] = true;
                // prevBagUsed[j + w] = prevBagUsed[j];
                // prevBagUsed[j + w].push_back(i - 1);
            }
        }
    }

    // Find closest possible sum to half
    int bestSum = 0;
    for (int j = target; j >= 0; --j) {
        if (dp[n][j]) {
            bestSum = j;
            break;
        }
    }

    vector<Baggage> groupA, groupB;
    vector<bool> used(n, false);

    // Use prevBagUsed to backtrack
    for (int idx : prevBagUsed[bestSum]) {
        groupA.push_back(bags[idx]);
        used[idx] = true;
    }
    for (int i = 0; i < n; ++i) {
        if (!used[i]) groupB.push_back(bags[i]);
    }

    int weightA = accumulate(groupA.begin(), groupA.end(), 0, [](int acc, const Baggage& b) { return acc + b.weight; });
    int weightB = accumulate(groupB.begin(), groupB.end(), 0, [](int acc, const Baggage& b) { return acc + b.weight; });

    return {groupA, groupB, weightA, weightB};
}
