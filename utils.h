//
// Created by plackett on 12/1/25.
//

#ifndef UTILS_H
#define UTILS_H
#include <string>
#include <vector>
#include <sstream>

inline std::vector<std::string> splitString(const std::string& s, const std::string& delimiter) {
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end = s.find(delimiter);

    while (end != std::string::npos) {
        tokens.push_back(s.substr(start, end - start));
        start = end + delimiter.length();
        end = s.find(delimiter, start);
    }
    tokens.push_back(s.substr(start));
    return tokens;
}

#endif //UTILS_H
