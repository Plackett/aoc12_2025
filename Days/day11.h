//
// Created by plackett on 12/11/25.
//

#ifndef DAY11_H
#define DAY11_H
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include "../utils.h"

inline long long pathDFS(const std::map<std::string,std::vector<std::string>>& paths, const std::string& currentNode, const std::string& endNode, std::map<std::string, long long>& memoization) {
    if (memoization.count(currentNode)) {
        return memoization[currentNode];
    }

    if (currentNode == endNode) {
        return 1;
    }

    if (paths.find(currentNode) == paths.end()) {
        return 0;
    }

    long long totalPaths = 0;

    for (const auto& neighbor : paths.at(currentNode)) {
        totalPaths += pathDFS(paths, neighbor, endNode, memoization);
    }

    memoization[currentNode] = totalPaths;
    return totalPaths;
}

inline long long solvePath(const std::map<std::string, std::vector<std::string>>& paths, const std::string& start, const std::string& end) {
    std::map<std::string, long long> memo;
    return pathDFS(paths, start, end, memo);
}

inline void day11(const std::string& input) {
    std::istringstream file(input);
    std::string line;
    std::map<std::string,std::vector<std::string>> paths{};

    while (std::getline(file, line)) {
        auto mainSplit = splitString(line, ": ");
        if (mainSplit.size() >= 2) {
            paths[mainSplit.at(0)] = splitString(mainSplit.at(1), " ");
        }
    }

    const long long partone = solvePath(paths, "you", "out");
    std::cout << "Day 11 Part 1: " << partone << "\n";
    const long long svr2dac = solvePath(paths, "svr", "dac");
    const long long dac2fft = solvePath(paths, "dac", "fft");
    const long long fft2out = solvePath(paths, "fft","out");
    const long long svr2fft = solvePath(paths, "svr", "fft");
    const long long fft2dac = solvePath(paths, "fft", "dac");
    const long long dac2out = solvePath(paths, "dac","out");
    std::cout << "Day 11 Part 1: " << ((svr2dac*dac2fft*fft2out)+(svr2fft*fft2dac*dac2out)) << "\n";
}

#endif //DAY11_H