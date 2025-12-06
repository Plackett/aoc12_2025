//
// Created by plackett on 12/5/25.
//

#ifndef DAY6_H
#define DAY6_H
#include <string>

inline long long calcColumns(const std::vector<std::vector<long long>> & columns, const std::vector<int> & operations) {
    long long result = 0;
    for (int i = 0; i < columns.size(); ++i) {
        long long subset = columns.at(i).at(0);
        for (int j = 1; j < columns.at(i).size(); ++j) {
            if (operations.at(i) == 0) {
                subset += columns.at(i).at(j);
            } else {
                subset *= columns.at(i).at(j);
            }
        }
        result += subset;
    }
    return result;
}

// ended up not needing a bigint class
// struct BigBootyJudy {
//     std::string storage;
//     explicit BigBootyJudy(const std::string& s) {
//         if (s.empty()) {
//             storage = "0";
//             return;
//         }
//         size_t first = s.find_first_not_of(" 0");
//         if (first == std::string::npos) {
//             storage = "0";
//         } else {
//             storage = s.substr(first);
//         }
//     }
//     void operator+=(const BigBootyJudy& other) {
//         std::string s1 = storage;
//         std::string s2 = other.storage;
//
//         std::reverse(s1.begin(), s1.end());
//         std::reverse(s2.begin(), s2.end());
//
//         std::string result;
//         int carry = 0;
//         const int n1 = static_cast<int>(s1.size());
//         const int n2 = static_cast<int>(s2.size());
//
//         for (int i = 0; i < std::max(n1, n2) || carry; ++i) {
//             const int d1 = (i < n1) ? s1.at(i) - '0' : 0;
//             const int d2 = (i < n2) ? s2.at(i) - '0' : 0;
//             const int sum = d1 + d2 + carry;
//
//             carry = sum / 10;
//             const int digit = sum % 10;
//
//             result.push_back(digit + '0');
//         }
//
//         std::reverse(result.begin(), result.end());
//         storage = result;
//     }
//
//     void operator*=(const BigBootyJudy& other) {
//         if (storage == "0" || other.storage == "0") {
//             storage = "0";
//             return;
//         }
//
//         const int n1 = static_cast<int>(storage.size());
//         const int n2 = static_cast<int>(other.storage.size());
//
//         // MINOR FIX: Explicitly type this as std::vector<int> to be safe across compilers
//         std::vector res(n1 + n2, 0);
//
//         for (int i = n1 - 1; i >= 0; --i) {
//             for (int j = n2 - 1; j >= 0; --j) {
//
//                 const int mul = (storage[i] - '0') * (other.storage[j] - '0');
//                 const int sum = mul + res[i + j + 1];
//
//                 res[i + j + 1] = sum % 10;
//                 res[i + j] += sum / 10;
//             }
//         }
//
//         std::string s;
//         for (const int num : res) {
//             if (!(s.empty() && num == 0)) {
//                 s.push_back(num + '0');
//             }
//         }
//
//         storage = s.empty() ? "0" : s;
//     }
// };

inline long long calcR2LColumns(const std::vector<std::string> & lines) {
    long long result = 0;
    std::vector<std::string> currentBlock;

    while (currentBlock.size() < lines.at(0).size()) currentBlock.emplace_back();

    for (int i = lines.at(0).size()-1; i >= 0; i--) {
        long long subTotal = 0;

        for (int j = 0; j < lines.size(); ++j) {

            if (!isspace(lines.at(j).at(i)) && !isdigit(lines.at(j).at(i))) {

                int startIndex = 0;
                for (int k = 0; k < currentBlock.size(); ++k) {
                    if (!currentBlock.at(k).empty()) {startIndex = k; break;}
                }

                subTotal = std::stoll(currentBlock.at(startIndex));

                for (int k = startIndex+1; k < currentBlock.size(); ++k) {
                    if (currentBlock.at(k).empty()) break;
                    if (lines.at(j).at(i) == '+') {
                        subTotal += std::stoll(currentBlock.at(k));
                    } else {
                        subTotal *= std::stoll(currentBlock.at(k));
                    }
                }

                result += subTotal;
                currentBlock = {};
                while (currentBlock.size() < lines.at(0).size()) currentBlock.emplace_back();
                break;
            }
            if (isdigit(lines.at(j).at(i))) {
                currentBlock.at(i) += lines.at(j).at(i);
            }
        }
    }
    return result;
}

inline void day6(const std::string& input) {
    std::istringstream file(input);
    std::vector<std::vector<long long>> columns{};
    std::vector<std::string> lines{};
    std::string line;
    std::vector<int> operations{};
    while (std::getline(file,line)) {
        lines.emplace_back(line);
        auto cols = splitString(line, " ");
        while (cols.at(0).empty()) cols.erase(cols.begin());
        if (isdigit(cols.at(0).at(0))) {
            int current = 0;
            for (const auto & col : cols) {
                if (col.empty()) continue;
                while (columns.size() <= current) {
                    columns.emplace_back();
                }
                std::string temp = col;
                temp.erase(std::remove_if(temp.begin(), temp.end(), ::isspace), temp.end());
                columns.at(current).emplace_back(std::stoll(temp));
                current++;
            }
        } else {
            for (auto col : cols) {
                if (col.empty()) continue;
                std::string temp = col;
                temp.erase(std::remove_if(temp.begin(), temp.end(), ::isspace), temp.end());
                switch (col.at(0)) {
                    case '+':
                        operations.push_back(0);
                        break;
                    default:
                        operations.push_back(1);
                        break;
                }
            }
        }
    }
    long long dayone = calcColumns(columns,operations);
    std::cout << "Day 6 Part 1: " << dayone << "\n";
    long long daytwo = calcR2LColumns(lines);
    std::cout << "Day 6 Part 2: " << daytwo << "\n";
}

#endif //DAY6_H