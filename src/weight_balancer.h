// weight_balancer.h
#ifndef WEIGHT_BALANCER_H
#define WEIGHT_BALANCER_H

#include "baggage.h"
#include <vector>
#include <tuple>

using namespace std;

// Returns: (Group A, Group B, Weight A, Weight B)
tuple<vector<Baggage>, vector<Baggage>, int, int> balanceBaggageWeight(const vector<Baggage>& bags);

#endif
