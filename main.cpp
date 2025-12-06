//
// Created by plackett on 12/1/25.
//

#include "main.h"

std::string getInput() {
    std::string input;
    std::string line;
    std::cout << "Enter the input file followed by ENDPART to end\n";
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
        case '1':
            day1(input);
            break;
        case '2':
            day2(input);
            break;
        case '3':
            day3(input);
            break;
        case '4':
            day4(input);
            break;
        case '5':
            day5(input);
            break;
        case '6':
            day6(input);
            break;
        // case '7':
        //     day7(input);
        //     break;
        // case '8':
        //     day8(input);
        //     break;
        // case '9':
        //     day9(input);
        //     break;
        // case '10':
        //     day10(input);
        //     break;
        // case '11':
        //     day11(input);
        //     break;
        // case '12':
        //     day12(input);
        //     break;
        default:
            day1(input);
            day2(input);
            day3(input);
            day4(input);
            day5(input);
            day6(input);
            // day7(input);
            // day8(input);
            // day9(input);
            // day10(input);
            // day11(input);
            // day12(input);
            break;
    }
    return 0;
}
