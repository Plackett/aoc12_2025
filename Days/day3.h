//
// Created by plackett on 12/2/25.
//

#ifndef DAY3_H
#define DAY3_H
#include <algorithm>
#include <iostream>

int getLargest(const std::string &line) {
    int firstMax = 0;
    int firstMaxIndex = 0;
    for (int i = 0; i < line.size(); ++i) {
        if (line[i] - '0' > firstMax) {
            firstMax = line[i] - '0';
            firstMaxIndex = i;
        }
    }
    int secondMax = -1;
    for (int i = firstMaxIndex+1; i < line.size(); ++i) {
        if (line[i] - '0' > secondMax) secondMax = line[i] - '0';
    }
    // go back and find new max
    while (secondMax == -1) {
        int newMax = 0;
        for (int i = 0; i < line.size(); ++i) {
            if (line[i] - '0' > newMax && line[i] - '0' != firstMax) {
                newMax = line[i] - '0';
                firstMaxIndex = i;
            }
        }
        for (int i = firstMaxIndex+1; i < line.size(); ++i) {
            if (line[i] - '0' > secondMax) secondMax = line[i] - '0';
        }
        if (secondMax != -1) firstMax = newMax;
    }
    return firstMax*10+secondMax;
}

long long getLargestPt2(const std::string& line) {
    // need 12 batteries now
    // im ngl the whole for loop going back thing was taking too long
    // so I rewrote it more general and less hard coded
    std::string jolt;
    for (int i = 0; i < line.size(); i++) {
        const char c = line[i];
        // this is LITERALLY SNAKE
        // I love this line so much
        // the tail end disappears if it finds a better starting value and has 12 numbers left after it
        while (!jolt.empty() && c > jolt.back() && (jolt.size() - 1 + (line.size() - i)) >= 12) {
            jolt.pop_back();
        }

        if (jolt.size() < 12) jolt.push_back(c);
    }

    long long finalValue = 0;
    for (const char c : jolt) {
        finalValue = finalValue * 10 + (c - '0');
    }

    return finalValue;
}

inline void day3(const std::string& input) {
    auto partOne = std::istringstream(input);
    std::string line;
    int partone = 0;
    long long parttwo = 0;
    while (std::getline(partOne,line)) {
        partone += getLargest(line);
        parttwo += getLargestPt2(line);
    }
    std::cout << "Day 3 Part 1: " << partone << '\n';
    std::cout << "Day 3 Part 1: " << parttwo << '\n';
}

#endif //DAY3_H
