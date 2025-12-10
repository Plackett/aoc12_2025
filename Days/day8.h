//
// Created by plackett on 12/1/25.
//

#ifndef DAY8_H
#define DAY8_H
#include "../utils.h"
#include <functional>

struct Coordinate {
    long long x = 0;
    long long y = 0;
    long long z = 0;
    int circuit = 0;
};

struct TwoCoordinates {
    double distance;
    int first;
    int second;
};

inline double get3DDistance(const Coordinate& p1, const Coordinate& p2) {
    return std::sqrt(std::pow(p2.x-p1.x,2)+std::pow(p2.y-p1.y,2)+std::pow(p2.z-p1.z,2));
}

inline long long calcThreeLargestCircuits(const std::vector<Coordinate> &junctionBoxes) {
    /*for(int i = 0; i < junctionBoxes.size(); ++i) {
        junctionBoxes.at(i).circuit = i;
    }
    int numConnections = 0;
    while(numConnections < 999) {
        TwoCoordinates shortestDistance = {INT_MAX,-1,-1};
        for(int i = 0; i < junctionBoxes.size(); ++i) {
            for(int j = junctionBoxes.size()-1; j >= 0; j--) {
                if(i != j && get3DDistance(junctionBoxes.at(i),junctionBoxes.at(j)) < shortestDistance.distance && junctionBoxes.at(i).circuit != junctionBoxes.at(j).circuit) {
                    shortestDistance.distance = get3DDistance(junctionBoxes.at(i),junctionBoxes.at(j));
                    shortestDistance.first = i;
                    shortestDistance.second = j;
                }
            }
        }
        int oldCircuit = int(junctionBoxes.at(shortestDistance.second).circuit);
        int newCircuit = int(junctionBoxes.at(shortestDistance.first).circuit);
        if (oldCircuit != newCircuit) {
            for (int i = 0; i < junctionBoxes.size(); ++i) {
                if (junctionBoxes.at(i).circuit == oldCircuit) {
                    junctionBoxes.at(i).circuit = newCircuit;
                }
            }
            numConnections++;
        
        }
    }
    std::pair<int,int> LargestCircuit = std::pair{0,0};
    for(int i = 0; i < junctionBoxes.size(); ++i) {
        int currentSize = 0;
        for(int j = 0; j < junctionBoxes.size(); ++j) {
            if (junctionBoxes.at(j).circuit == i) {
                currentSize++;
            }
        }
        if(currentSize > LargestCircuit.second) LargestCircuit = std::pair{i,currentSize};
    }
    std::pair<int,int> SecondLargest = std::pair{0,0};
    for(int i = 0; i < junctionBoxes.size(); ++i) {
        int currentSize = 0;
        for(int j = 0; j < junctionBoxes.size(); ++j) {
            if(junctionBoxes.at(j).circuit == i) currentSize++;
        }
        if(currentSize > SecondLargest.second && i != LargestCircuit.first ) SecondLargest = std::pair{i,currentSize};
    }
    std::pair<int,int> ThirdLargest = std::pair{0,0};
    for(int i = 0; i < junctionBoxes.size(); ++i) {
        int currentSize = 0;
        for(int j = 0; j < junctionBoxes.size(); ++j) {
            if(junctionBoxes.at(j).circuit == i) currentSize++;
        }
        if(currentSize > ThirdLargest.second && i != LargestCircuit.first && i != SecondLargest.first) ThirdLargest = std::pair{i,currentSize};
    }
    return LargestCircuit.second * SecondLargest.second * ThirdLargest.second;*/

    const long long n = junctionBoxes.size();

    std::vector<int> parent(n);
    for (int i = 0; i < n; ++i) parent[i] = i;

    std::function<int(int)> find = [&](int x) {
        // weird lambda function to ensure we don't form a cycle yet
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    };

    std::vector<std::tuple<double,int,int>> distances;
    distances.reserve(n * (n - 1) / 2);
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            double dist = get3DDistance(junctionBoxes[i], junctionBoxes[j]);
            distances.emplace_back(dist, i, j);
        }
    }

    std::sort(distances.begin(), distances.end());

    int limit = 1000;
    if (distances.size() < limit) limit = distances.size();

    for (int k = 0; k < limit; ++k) {
        auto [dist, i, j] = distances[k];
        const int pi = find(i);
        const int pj = find(j);

        if (pi != pj) {
            parent[pi] = pj;
        }
    }

    std::map<int, int> circuitSizes;
    for (int i = 0; i < n; ++i) {
        circuitSizes[find(i)]++;
    }

    std::vector<int> sizes;
    sizes.reserve(circuitSizes.size());
    for (auto [id, size] : circuitSizes) {
        sizes.push_back(size);
    }
    std::sort(sizes.rbegin(), sizes.rend());

    if (sizes.size() < 3) {
        return 0;
    }

    return static_cast<long long>(sizes[0]) * sizes[1] * sizes[2];
}

inline long long calcLargestCircuit(const std::vector<Coordinate>& junctionBoxes) {
    const long long n = junctionBoxes.size();

    std::vector<int> parent(n);
    for (int i = 0; i < n; ++i) parent[i] = i;

    std::function<int(int)> find = [&](const int x) {
        // weird lambda function to ensure we don't form a cycle yet
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    };

    std::vector<std::tuple<double, int, int>> distances;
    distances.reserve(n * (n - 1) / 2);
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            double dist = get3DDistance(junctionBoxes[i], junctionBoxes[j]);
            distances.emplace_back(dist, i, j);
        }
    }

    std::sort(distances.begin(), distances.end());
    int merges = 0;

    for (auto [dist, first, second] : distances) {
        // every node starts by having itself as a parent
        const int parentOfFirst = find(first);
        const int parentOfSecond = find(second);

        if (parentOfFirst != parentOfSecond) {
            parent[parentOfFirst] = parentOfSecond;
            merges++;

            if (merges == n - 1) {
                return junctionBoxes[first].x * junctionBoxes[second].x;
            }
        }
    }

    return 0;
}

inline void day8(const std::string& input) {
    std::istringstream file(input);
    std::string line;
    std::vector<Coordinate> junctionBoxes{};

    while(std::getline(file,line)) {
        auto formattedLine = splitString(line,",");
        junctionBoxes.emplace_back(Coordinate{std::stoll(formattedLine.at(0)),std::stoll(formattedLine.at(1)),std::stoll(formattedLine.at(2))});
    }

    const long long dayone = calcThreeLargestCircuits(junctionBoxes);
    std::cout << "Day 8 Part 1: " << dayone << "\n";
    const long long daytwo = calcLargestCircuit(junctionBoxes);
    std::cout << "Day 8 Part 2: " << daytwo << "\n";
}

#endif