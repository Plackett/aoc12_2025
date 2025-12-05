//
// Created by plackett on 12/4/25.
//

#ifndef DAY5_H
#define DAY5_H

#include "../utils.h"
#include <algorithm>

inline long long checkVeggies(const std::vector<std::pair<long long,long long>>& fresh, const std::vector<long long>& toCheck) {
    long long total = 0;
    for (const auto val : toCheck) {
        for (auto [fst, snd] : fresh) {
            if (val >= fst && val <= snd) {
                total++;
                break;
            }
        }
    }
    return total;
}

inline long long checkNumberFresh(const std::vector<std::pair<long long,long long>>& fresh) {
    std::vector<std::pair<long long, long long>> sortedFresh = fresh;
    std::sort(sortedFresh.begin(), sortedFresh.end());
    std::vector<std::pair<long long,long long>> consolidatedFresh{};
    consolidatedFresh.emplace_back(sortedFresh[0]);

    for (int i = 0; i < sortedFresh.size(); ++i) {
        std::pair<long long, long long>& last = consolidatedFresh.at(consolidatedFresh.size()-1);

        if (sortedFresh[i].first <= last.second) {
            if (sortedFresh[i].second > last.second) last.second = sortedFresh[i].second;
        } else {
            consolidatedFresh.emplace_back(sortedFresh[i]);
        }
    }
    long long result = 0;
    for (auto [fst, snd] : consolidatedFresh) {
        result += snd - fst + 1;
    }
    return result;
}

void day5(const std::string& input) {
    std::istringstream file(input);
    std::string line;
    std::vector<std::pair<long long,long long>> freshRanges{};
    std::vector<long long> toCheck{};
    bool split = false;
    while (std::getline(file,line)) {
        if (line.empty()) {split = true; continue;}
        if (!split) {
            freshRanges.emplace_back(std::stoll(splitString(line,"-").at(0)),std::stoll(splitString(line,"-").at(1)));
        } else {
            toCheck.emplace_back(std::stoll(line));
        }
    }
    long long dayone = checkVeggies(freshRanges,toCheck);
    long long daytwo = checkNumberFresh(freshRanges);
    std::cout << "Day 5 Part 1: " << dayone << "\n";
    std::cout << "Day 5 Part 2: " << daytwo << "\n";
}

#endif //DAY5_H
