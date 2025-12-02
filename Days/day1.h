//
// Created by plackett on 12/1/25.
//

#ifndef DAY1_H
#define DAY1_H
#include "../utils.h"

inline void handleRotation(int& origin, const std::string &rotation) {
    int amount = 0;

    if (rotation.at(0) == 'L') {
        amount = -std::stoi(splitString(rotation, "L").at(1));
    } else {
        amount = std::stoi(splitString(rotation, "R").at(1));
    }

    origin = (origin + amount) % 100;

    while (origin < 0) { // C++ modulo doesn't even work bruyh
        origin += 100;
    }
}

inline void handleRotationPt2(int& origin, const std::string &rotation, int& password) {
    const int amount = std::stoi(rotation.substr(1));

    if (rotation.at(0) == 'R') {
        password += (origin + amount) / 100;
        origin = (origin + amount) % 100;

    } else {
        if (origin == 0) {
            password += amount / 100;
        }
        else {
            if (amount >= origin) {
                password += 1 + (amount - origin) / 100;
            }
        }

        origin = (origin - amount) % 100;
        if (origin < 0) origin += 100;
    }

}

inline void day1(const std::string& input) {
    auto partOne = std::istringstream(input);
    auto partTwo = std::istringstream(input);
    int origin = 50; // the dial starts at 50 for part one? idk even why lol
    int password = 0;
    std::string line;
    while (std::getline(partOne,line)) {
        handleRotation(origin, line);
        if (origin == 0) password++;
    }
    std::cout << "The solution to part one is " << password << '\n';
    line = "";
    password = 0;
    origin = 50;
    while (std::getline(partTwo,line)) {
        handleRotationPt2(origin, line,password);
    }
    std::cout << "The solution to part two is " << password << '\n';
}

#endif //DAY1_H
