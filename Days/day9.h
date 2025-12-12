//
// Created by plackett on 12/9/25.
//

#ifndef DAY9_H
#define DAY9_H

#include "../utils.h"
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>

inline bool isPointInPolygon(const double x, const double y, const std::vector<std::pair<double, double>>& poly) {
    bool inside = false;
    for (size_t i = 0; i < poly.size(); i++) {
        const size_t j = (i + 1) % poly.size();

        const double x1 = poly[i].first;
        const double y1 = poly[i].second;
        const double x2 = poly[j].first;
        const double y2 = poly[j].second;

        const bool yBetween = (y1 > y) != (y2 > y);

        if (yBetween) {
            const double intersectX = x1 + (y - y1) * (x2 - x1) / (y2 - y1);

            if (x < intersectX) {
                inside = !inside;
            }
        }
    }
    return inside;
}

inline bool doesWallCutRectangle(const double x1, const double y1, const double x2, const double y2, const double minX, const double maxX, const double minY, const double maxY) {

    if (x1 == x2) {
        if (x1 > minX && x1 < maxX) {
            const double wallMinY = std::min(y1, y2);
            const double wallMaxY = std::max(y1, y2);
            if (std::max(wallMinY, minY) < std::min(wallMaxY, maxY)) {
                return true;
            }
        }
    } else if (y1 == y2) {
        if (y1 > minY && y1 < maxY) {
            double wallMinX = std::min(x1, x2);
            double wallMaxX = std::max(x1, x2);
            if (std::max(wallMinX, minX) < std::min(wallMaxX, maxX)) {
                return true;
            }
        }
    }
    return false;
}

inline bool isValidRectangle(const std::pair<double, double>& r1, const std::pair<double, double>& r2, const std::vector<std::pair<double, double>>& poly) {
    const double minX = std::min(r1.first, r2.first);
    const double maxX = std::max(r1.first, r2.first);
    const double minY = std::min(r1.second, r2.second);
    const double maxY = std::max(r1.second, r2.second);

    const double centerX = (minX + maxX) / 2.0;
    const double centerY = (minY + maxY) / 2.0;
    
    if (!isPointInPolygon(centerX, centerY, poly)) {
        return false;
    }

    for (size_t i = 0; i < poly.size(); i++) {
        size_t j = (i + 1) % poly.size();
        if (doesWallCutRectangle(poly[i].first, poly[i].second, 
                                 poly[j].first, poly[j].second,
                                 minX, maxX, minY, maxY)) {
            return false;
        }
    }

    return true;
}

inline double calcBiggestArea(const std::vector<std::pair<double, double>> & redTiles) {
    double largestArea = 0;
    for (int i = 0; i < redTiles.size(); ++i) {
        for (int j = static_cast<int>(redTiles.size())-1; j >= 0; j--) {
            const double size = (std::abs(redTiles.at(j).first-redTiles.at(i).first)+1)*(std::abs(redTiles.at(j).second-redTiles.at(i).second)+1);
            if (size > largestArea) {
                largestArea = size;
            }
        }
    }
    return largestArea;
}

inline double calcBiggestGreenTileArea(const std::vector<std::pair<double, double>> & redTiles) {
    double largestArea = 0;

    for (int i = 0; i < redTiles.size(); ++i) {
        for (int j = i + 1; j < redTiles.size(); ++j) {

            const double size = (std::abs(redTiles.at(j).first-redTiles.at(i).first)+1)*(std::abs(redTiles.at(j).second-redTiles.at(i).second)+1);
            
            if (size > largestArea) {
                if (isValidRectangle(redTiles[i], redTiles[j], redTiles)) {
                    largestArea = size;
                }
            }
        }
    }
    return largestArea;
}

inline void day9(const std::string& input) {
    std::istringstream file(input);
    std::string line;
    std::vector<std::pair<double, double>> redTiles{};
    while (std::getline(file,line)) {
        auto tokens = splitString(line,",");
        redTiles.emplace_back(std::stoll(tokens.at(0)),std::stoll(tokens.at(1)));
    }
    const auto dayone = static_cast<long long>(calcBiggestArea(redTiles));
    std::cout << "Day 9 Part 1: " << dayone << "\n";
    const auto daytwo = static_cast<long long>(calcBiggestGreenTileArea(redTiles));
    std::cout << "Day 9 Part 2: " << daytwo << "\n";
}
#endif //DAY9_H