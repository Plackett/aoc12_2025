//
// Created by plackett on 12/7/25.
//

#ifndef DAY7_H
#define DAY7_H
#include <map>

long long calcSplits(const std::pair<int,int>& start, const std::vector<std::pair<int, int>> & splitters, const int maxLine, const int maxWidth) {
    std::set currentBeams{start};
    long long splits = 0;
    while (currentBeams.begin()->first != maxLine) {
        std::set<std::pair<int,int>> newBeams;
        for (auto beam : currentBeams) {
            if (std::find(splitters.begin(), splitters.end(), std::pair{beam.first+1,beam.second}) != splitters.end()) {
                splits++;
                if (beam.second-1 != -1) {
                    newBeams.insert(std::pair{beam.first+1,beam.second-1});
                }
                if (beam.second+1 != maxWidth) {
                    newBeams.insert(std::pair{beam.first+1,beam.second+1});
                }
            } else {
                newBeams.insert(std::pair{beam.first+1,beam.second});
            }
        }
        currentBeams = newBeams;
    }
    return splits;
}

inline long long calcTimelines(const std::pair<int,int>& start, const std::vector<std::pair<int, int>> & splitters, const int maxLine, const int maxWidth) {
    std::map<int, long long> currentTimelines;
    currentTimelines[start.second] = 1;
    for (int row = start.first; row < maxLine-1; ++row) {
        std::map<int, long long> nextTimelines;
        for (auto const& [col, count] : currentTimelines) {
            if (std::find(splitters.begin(), splitters.end(), std::pair{row+1,col}) != splitters.end()) {
                if (col - 1 != -1) nextTimelines[col-1] += count;
                if (col != maxWidth) nextTimelines[col+1] += count;
            } else nextTimelines[col] += count;
        }
        currentTimelines = nextTimelines;
    }
    long long totalTimelines = 0;
    for (auto const& [col, count] : currentTimelines) {
        totalTimelines += count;
    }
    return totalTimelines;
}

void day7(const std::string& input) {
    std::istringstream file(input);
    std::string line;
    std::vector<std::pair<int,int>> splitters{};
    std::pair<int,int> start;
    int currentLine = 0;
    int maxWidth = 0;
    while (std::getline(file,line)) {
        maxWidth = line.size();
        for (int i = 0; i < line.size(); ++i) {
            if (line.at(i) == 'S') start = {currentLine,i};
            if (line.at(i) == '^') splitters.emplace_back(currentLine,i);
        }
        currentLine++;
    }
    const long long dayone = calcSplits(start, splitters, currentLine-1,maxWidth-1);
    std::cout << "Day 7 Part 1: " << dayone << '\n';
    const long long daytwo = calcTimelines(start, splitters, currentLine-1,maxWidth-1);
    std::cout << "Day 7 Part 2: " << daytwo << '\n';
}

#endif //DAY7_H
