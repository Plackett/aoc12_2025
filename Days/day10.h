//
// Created by plackett on 12/10/25.
//

#ifndef DAY10_H
#define DAY10_H
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <queue>
#include <set>
#include <algorithm>

#include "../utils.h"

inline long long ButtonBFS(const std::vector<bool>& targetState, const std::vector<std::vector<int>>& buttons) {
    std::vector allOff(targetState.size(), false);

    std::queue<std::pair<std::vector<bool>, long long>> q;
    std::set<std::vector<bool>> visited;

    q.emplace(allOff, 0);
    visited.insert(allOff);

    while (!q.empty()) {
        auto [currentState, steps] = q.front();
        q.pop();

        if (currentState == targetState) {
            return steps;
        }

        for (const auto& btnIndices : buttons) {
            std::vector<bool> nextState = currentState;

            for (const int index : btnIndices) {
                if (index >= 0 && index < nextState.size()) {
                    nextState[index] = !nextState[index];
                }
            }

            if (visited.find(nextState) == visited.end()) {
                visited.insert(nextState);
                q.emplace(nextState, steps + 1);
            }
        }
    }

    return -1;
}

inline long long calcMinButtons(const std::vector<std::vector<bool>> & desiredOutput, const std::vector<std::vector<std::vector<int>>> & buttons) {
    long long totalButtonPresses = 0;

    for (size_t i = 0; i < desiredOutput.size(); ++i) {
        long long steps = ButtonBFS(desiredOutput.at(i), buttons.at(i));

        if (steps == -1) {
             std::cerr << "help im dying\n";
        } else {
            totalButtonPresses += steps;
        }
    }
    return totalButtonPresses;
}

inline long long ButtonJoltBFS(const std::vector<int>& targetState, const std::vector<std::vector<int>>& buttons) {
    std::vector allOff(targetState.size(), 0);

    std::queue<std::pair<std::vector<int>, long long>> q;
    std::set<std::vector<int>> visited;

    q.emplace(allOff, 0);
    visited.insert(allOff);

    while (!q.empty()) {
        auto [currentState, steps] = q.front();
        q.pop();

        if (currentState == targetState) {
            return steps;
        }

        for (const auto& btnIndices : buttons) {
            std::vector<int> nextState = currentState;

            for (const int index : btnIndices) {
                if (index >= 0 && index < nextState.size()) {
                    nextState[index]++;
                }
            }

            if (visited.find(nextState) == visited.end()) {
                visited.insert(nextState);
                q.emplace(nextState, steps + 1);
            }
        }
    }

    return -1;
}

// im not going to lie I googled how to solve a linear system in C++ and got this
inline long long solveLinearSystem(const std::vector<int>& target, const std::vector<std::vector<int>>& buttons) {
    const int rows = target.size();
    const int cols = buttons.size();
    std::vector matrix(rows, std::vector(cols + 1, 0.0));

    // Fill the matrix (buttons are columns, target is the last column)
    for (int j = 0; j < cols; ++j) {
        for (int i : buttons[j]) {
            if (i < rows) matrix[i][j] = 1.0;
        }
    }
    for (int i = 0; i < rows; ++i) {
        matrix[i][cols] = target[i];
    }

    // Forward Elimination
    int pivotRow = 0;
    for (int col = 0; col < cols && pivotRow < rows; ++col) {
        int maxRow = pivotRow;
        for (int i = pivotRow + 1; i < rows; ++i) {
            if (std::abs(matrix[i][col]) > std::abs(matrix[maxRow][col])) {
                maxRow = i;
            }
        }

        if (std::abs(matrix[maxRow][col]) < 0.000001) continue;

        std::swap(matrix[pivotRow], matrix[maxRow]);

        for (int i = pivotRow + 1; i < rows; ++i) {
            double factor = matrix[i][col] / matrix[pivotRow][col];
            for (int k = col; k <= cols; ++k) {
                matrix[i][k] -= factor * matrix[pivotRow][k];
            }
        }
        pivotRow++;
    }

    std::vector solution(cols, 0.0);
    for (int i = pivotRow - 1; i >= 0; --i) {
        int pivotCol = -1;
        for (int j = 0; j < cols; ++j) {
            if (std::abs(matrix[i][j]) > 0.000001) {
                pivotCol = j;
                break;
            }
        }

        if (pivotCol == -1) continue;

        double sum = matrix[i][cols];
        for (int j = pivotCol + 1; j < cols; ++j) {
            sum -= matrix[i][j] * solution[j];
        }
        solution[pivotCol] = sum / matrix[i][pivotCol];
    }

    long long total = 0;
    for (double s : solution) {
        long long presses = std::llround(s);
        if (presses < 0) return -1;
        total += presses;
    }
    return total;
}

inline long long calcMinButtonsJoltage(const std::vector<std::vector<int>>& joltage, const std::vector<std::vector<std::vector<int>>> & buttons) {
    long long totalButtonPresses = 0;

    for (size_t i = 0; i < joltage.size(); ++i) {
        long long steps = solveLinearSystem(joltage.at(i), buttons.at(i));

        if (steps == -1) {
            std::cerr << "help im dying\n";
        } else {
            totalButtonPresses += steps;
        }
    }
    return totalButtonPresses;
}

inline void day10(std::string& input) {
    std::istringstream file(input);
    std::string line;
    std::vector<std::vector<bool>> targets{};
    std::vector<std::vector<std::vector<int>>> buttons{};
    std::vector<std::vector<int>> joltage{};

    while (std::getline(file,line)) {
        if(line.empty()) continue;

        auto mainSplit = splitString(line,"] ");
        if (mainSplit.size() < 2) continue;

        auto splitJoltage = splitString(mainSplit.at(1)," {");

        std::vector<bool> outputState{};
        for (size_t i = 1; i < mainSplit.at(0).size(); ++i) {
            if (mainSplit.at(0).at(i) == '.') {
                outputState.emplace_back(false);
            }
            else outputState.emplace_back(true);
        }
        targets.emplace_back(outputState);

        bool open = false;
        std::vector<std::vector<int>> currentButtons{};
        std::string numBuffer;

        for (const char c : splitJoltage.at(0)) {
            if (c == '(') {
                open = true;
                currentButtons.emplace_back();
                numBuffer.clear();
            }
            else if (c == ')') {
                if (!numBuffer.empty()) {
                    currentButtons.back().emplace_back(std::stoi(numBuffer));
                    numBuffer.clear();
                }
                open = false;
            }
            else if (open) {
                if (isdigit(c)) {
                    numBuffer += c;
                }
                else if (c == ',' || c == ' ') {
                    if (!numBuffer.empty()) {
                        currentButtons.back().emplace_back(std::stoi(numBuffer));
                        numBuffer.clear();
                    }
                }
            }
        }
        buttons.emplace_back(currentButtons);

        std::vector<int> currentJolts{};
        if (splitJoltage.size() > 1) {
             for (const auto& token : splitString(splitJoltage.at(1),",")) {
                std::string cleanToken = token;
                if (cleanToken.find('}') != std::string::npos) {
                    cleanToken = cleanToken.substr(0, cleanToken.find('}'));
                }
                if (!cleanToken.empty())
                    currentJolts.emplace_back(std::stoi(cleanToken));
            }
        }
        joltage.emplace_back(currentJolts);
    }

    const long long dayone = calcMinButtons(targets, buttons);
    std::cout << "Day 10 Part 1: " << dayone << "\n";
    const long long daytwo = calcMinButtonsJoltage(joltage, buttons);
    std::cout << "Day 10 Part 2: " << daytwo << "\n";
}
#endif //DAY10_H