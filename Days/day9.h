//
// Created by plackett on 12/9/25.
//

#ifndef DAY9_H
#define DAY9_H

#include "../utils.h"

inline long long calcBiggestArea(const std::vector<std::pair<long long, long long>> & redTiles) {
    long long largestArea = 0;
    for (int i = 0; i < redTiles.size(); ++i) {
        for (int j = redTiles.size() -1; j >= 0; j--) {
            const long long size = std::abs((redTiles.at(j).first-redTiles.at(i).first+1)*(redTiles.at(j).second-redTiles.at(i).second+1));
            if (size > largestArea) {
                //std::cout << "New Largest " << redTiles.at(j).first << "x + " << redTiles.at(j).second << "y and " << redTiles.at(i).first << "x + " << redTiles.at(i).second << "y are the new leaders!\n";
                largestArea = size;
            }
        }
    }
    return largestArea;
}

inline long long calcBiggestGreenTileArea(const std::vector<std::pair<long long, long long>> & redTiles) {
    long long largestArea = 0;
    for (int i = 0; i < redTiles.size(); ++i) {
        for (int j = redTiles.size() -1; j >= 0; j--) {
            if (j <= i) break;
            const long long size = std::abs((redTiles.at(j).first-redTiles.at(i).first+1)*(redTiles.at(j).second-redTiles.at(i).second+1));
            if (size > largestArea) {
                bool contained = true;
                for (int k = i; k <= j; ++k) {
                        if (redTiles.at(k).first < redTiles.at(j).first || redTiles.at(k).second < redTiles.at(j).second) {
                            contained = false;
                            break;
                        }
                }
                if (contained) largestArea = size;
                //std::cout << "New Largest " << redTiles.at(j).first << "x + " << redTiles.at(j).second << "y and " << redTiles.at(i).first << "x + " << redTiles.at(i).second << "y are the new leaders!\n"
            }
        }
    }
    return largestArea;
}

inline void day9(const std::string& input) {
    std::istringstream file(input);
    std::string line;
    std::vector<std::pair<long long, long long>> redTiles{};
    while (std::getline(file,line)) {
        auto tokens = splitString(line,",");
        std::cout << std::stoll(tokens.at(0)) << " x + " << std::stoll(tokens.at(1)) << " y\n";
        redTiles.emplace_back(std::stoll(tokens.at(0)),std::stoll(tokens.at(1)));
    }
    const long long dayone = calcBiggestArea(redTiles);
    std::cout << "Day 9 Part 1: " << dayone << "\n";
    const long long daytwo = calcBiggestGreenTileArea(redTiles);
    std::cout << "Day 9 Part 2: " << daytwo << "\n";
}
#endif //DAY9_H
