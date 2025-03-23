#ifndef SHUTTLEROUTE_H
#define SHUTTLEROUTE_H

#include <vector>
#include <string>
#include "Stop.h"

class ShuttleRoute {
public:
    std::string name;
    std::vector<Stop> stops;
    std::vector<int> costs; // Costs between consecutive stops

    ShuttleRoute(const std::string &n) : name(n) {}

    void addStop(const std::string &stopName) {
        stops.emplace_back(stopName);
    }

    void addCost(int cost) {
        costs.push_back(cost);
    }

    int totalCost() const {
        int total = 0;
        for (int cost : costs) {
            total += cost;
        }
        return total;
    }

    int costBetweenStops(int startIndex, int endIndex) const {
        int total = 0;
        for (int i = startIndex; i < endIndex; ++i) {
            total += costs[i];
        }
        return total;
    }
};

#endif // SHUTTLEROUTE_H