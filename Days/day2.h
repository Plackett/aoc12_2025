//
// Created by plackett on 12/1/25.
//

#ifndef DAY2_H
#define DAY2_H
#include <cmath>
#include <set>

inline int digits(const long long n) {
    return std::to_string(n).length();
}

long long rangeChecker(const std::string& range) {
    const size_t delimPos = range.find('-');
    const long long min = std::stoll(range.substr(0, delimPos));
    const long long max = std::stoll(range.substr(delimPos + 1));
    long long result = 0;
    const int minDigits = digits(min);
    const int maxDigits = digits(max);
    for (int i = minDigits; i <= maxDigits; i++) {
        // odd lengths don't even exist
        if (i % 2 != 0) continue;
        const int sideDigits = i/2;

        const long long patternStart = std::llround(std::pow(10, sideDigits-1));
        const long long patternEnd = std::llround(std::pow(10, sideDigits)-1);

        for (long long seed = patternStart; seed <= patternEnd; seed++) {
            std::string s = std::to_string(seed);
            std::string test = s + s;

            long long testButNumber = std::stoll(test);

            if (testButNumber >= min && testButNumber <= max) {
                result += testButNumber;
                //std::cout << "Found invalid ID! " << testButNumber << '\n';
            }
        }
    }
    return result;
}
long long rangeCheckerpt2(const std::string& range) {
    std::set<long long> uniqueInvalidIDs;
    const size_t delimPos = range.find('-');
    const long long min = std::stoll(range.substr(0, delimPos));
    const long long max = std::stoll(range.substr(delimPos + 1));
    long long result = 0;
    const int minDigits = digits(min);
    const int maxDigits = digits(max);
    for (int i = minDigits; i <= maxDigits; i++) {
        // odd lengths  exist now :(
        //if (i % 2 != 0) continue;
        const int sideDigits = i/2;
        for (int patternLen = 1; patternLen <= sideDigits; patternLen++) {
            if (i % patternLen != 0) continue;
            const int repetitions = i / patternLen;
            const long long patternStart = std::llround(std::pow(10, patternLen-1));
            const long long patternEnd = std::llround(std::pow(10, patternLen)-1);

            for (long long seed = patternStart; seed <= patternEnd; seed++) {
                std::string s = std::to_string(seed);
                std::string test;
                for (int j = 0; j < repetitions; ++j) {
                    test += s;
                }

                long long testButNumber = std::stoll(test);

                if (testButNumber >= min && testButNumber <= max) {
                    uniqueInvalidIDs.insert(testButNumber);
                    //std::cout << "Found invalid Id: " << testButNumber << "\n";
                }
            }
        }
    }
    for (const long long id : uniqueInvalidIDs) {
        result += id;
    }
    return result;
}


void day2(const std::string& input) {
    auto rawInput = std::istringstream(input);
    std::string range;
    long long invalidIds = 0;
    long long invalidIds2 = 0;
    while (std::getline(rawInput,range,',')) {
        invalidIds += rangeChecker(range);
        invalidIds2 += rangeCheckerpt2(range);
    }
    std::cout << "Day 2 Part 1: " << invalidIds << '\n';
    std::cout << "Day 2 Part 2: " << invalidIds2 << '\n';
}

#endif //DAY2_H
