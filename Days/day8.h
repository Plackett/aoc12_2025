//
// Created by plackett on 12/1/25.
//

#ifndef DAY8_H
#define DAY8_H
#include "../utils.h"

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

double get3DDistance(const Coordinate& p1, const Coordinate& p2) {
    return std::sqrt(std::pow(p2.x-p1.x,2)+std::pow(p2.y-p1.y,2)+std::pow(p2.z-p2.z,2));
}

long long calcThreeLargestCircuits(std::vector<Coordinate> junctionBoxes) {
    for(int i = 0; i < junctionBoxes.size(); ++i) {
        junctionBoxes.at(i).circuit = i;
    }
    int numConnections = 0;
    while(numConnections < 10) {
        TwoCoordinates shortestDistance = {INT_MAX,-1,-1};
        for(int i = 0; i < junctionBoxes.size(); ++i) {
            for(int j = junctionBoxes.size()-1; j >= 0; j--) {
                if(i != j && get3DDistance(junctionBoxes.at(i),junctionBoxes.at(j)) < shortestDistance.first) {
                    shortestDistance.distance = get3DDistance(junctionBoxes.at(i),junctionBoxes.at(j));
                    shortestDistance.first = i;
                    shortestDistance.second = j;
                }
            }
        }
        for(int i = 0; i < junctionBoxes.size(); ++i) {
            if(junctionBoxes.at(i).circuit == junctionBoxes.at(shortestDistance.second).circuit) junctionBoxes.at(i).circuit = junctionBoxes.at(shortestDistance.first).circuit;
        }
        numConnections++;
    }
    std::pair<int,int> LargestCircuit = std::pair{0,1};
    for(int i = 0; i < junctionBoxes.size(); ++i) {
        int currentSize = 0;
        for(int j = 0; j < junctionBoxes.size(); ++j) {
            if(junctionBoxes.at(j).circuit == i) currentSize++;
        }
        if(currentSize > LargestCircuit.second) LargestCircuit = std::pair{i,currentSize};
    }
    std::pair<int,int> SecondLargest = std::pair{0,1};
    for(int i = 0; i < junctionBoxes.size(); ++i) {
        int currentSize = 0;
        for(int j = 0; j < junctionBoxes.size(); ++j) {
            if(junctionBoxes.at(j).circuit == i) currentSize++;
        }
        if(currentSize > SecondLargest.second && currentSize != LargestCircuit.second ) SecondLargest = std::pair{i,currentSize};
    }
    std::pair<int,int> ThirdLargest = std::pair{0,1};
    for(int i = 0; i < junctionBoxes.size(); ++i) {
        int currentSize = 0;
        for(int j = 0; j < junctionBoxes.size(); ++j) {
            if(junctionBoxes.at(j).circuit == i) currentSize++;
        }
        if(currentSize > ThirdLargest.second && currentSize != LargestCircuit.second ) ThirdLargest = std::pair{i,currentSize};
    }
    return LargestCircuit.second * SecondLargest.second * ThirdLargest.second;
}

void day8(const std::string& input) {
    std::istringstream file(input);
    std::string line;
    std::vector<Coordinate> junctionBoxes{};

    while(std::getline(file,line)) {
        auto formattedLine = splitString(line,",");
        junctionBoxes.emplace_back(Coordinate{std::stoll(formattedLine.at(0)),std::stoll(formattedLine.at(1)),std::stoll(formattedLine.at(2))});
    }

    long long dayone = calcThreeLargestCircuits(junctionBoxes);
    std::cout << "Day 8 Part 1: " << dayone << "\n";
}

#endif