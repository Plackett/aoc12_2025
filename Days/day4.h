//
// Created by plackett on 12/3/25.
//

#ifndef DAY4_H
#define DAY4_H
#include <string>
#include <algorithm>
#include <utility>
#include <iostream>

long long findAcessibleRolls(std::vector<std::pair<int,int>> rolls) {
    long long accessible = 0;
    for (int i = 0; i < rolls.size(); ++i) {
        int numNeighbors = 0;
        for (int j = -1; j <= 1; ++j) {
            for (int k = -1; k <= 1; ++k) {
                if (k == 0 && j == 0) continue;
                if (std::find(rolls.begin(),rolls.end(), std::pair<int,int>(rolls.at(i).first+j,rolls.at(i).second+k)) != rolls.end()) numNeighbors++;
            }
        }
        if (numNeighbors < 4) accessible++;
    }
    return accessible;
}

std::vector<std::pair<int,int>> findAcessibleRollsPt2(std::vector<std::pair<int,int>> rolls, long long& accessible) {
    std::vector<std::pair<int,int>> result{};
    for (int i = 0; i < rolls.size(); ++i) {
        int numNeighbors = 0;
        for (int j = -1; j <= 1; ++j) {
            for (int k = -1; k <= 1; ++k) {
                if (k == 0 && j == 0) continue;
                if (std::find(rolls.begin(),rolls.end(),std::pair<int,int>(rolls.at(i).first+j,rolls.at(i).second+k)) != rolls.end()) numNeighbors++;
            }
        }
        if (numNeighbors < 4) {
            accessible++;
        } else {
            result.emplace_back(rolls.at(i));
        }
    }
    return result;
}

inline void day4(const std::string& input) {
    std::vector<std::pair<int,int>> rolls{};
    std::istringstream file(input);
    std::string line;
    int currentLine = 0;
    while (std::getline(file,line)) {
        for (int i = 0; i < line.size(); i++) {
            if (line.at(i) == '@') rolls.emplace_back(currentLine,i);
        }
        currentLine++;
    }
    long long dayone = findAcessibleRolls(rolls);
    int oldAccessible = 0;
    long long daytwo = 0;
    auto temp = findAcessibleRollsPt2(rolls, daytwo);
    while (daytwo - oldAccessible != 0) {
        oldAccessible = daytwo;
        temp = findAcessibleRollsPt2(temp, daytwo);
    }

    std::cout << "Day 4 Part 1: " << dayone << '\n';
    std::cout << "Day 4 Part 2: " << daytwo << '\n';
}

#endif //DAY4_H
