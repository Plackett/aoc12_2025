//
// Created by plackett on 12/1/25.
//

#include "main.h"

std::string getInput() {
    std::string input;
    std::string line;
    std::cout << "Enter the input data for part one followed by ENDPART to end\n";
    while (std::getline(std::cin, line)) {
        if (line == "ENDPART") {
            break;
        }
        if (!input.empty()) {
            input += "\n";
        }
        input += line;
    }
    return input;
}

int main() {
    const std::string input = getInput();
    std::cout << "Enter the number (1-12) for the day to run or type * for all days\n";
    char day;
    std::cin >> day;
    switch(day) {
        case('1'):
            day1(input);
            break;
        case('*'): day1(input);
            break;
        default: day1(input);
            break;
    }
    return 0;
}
