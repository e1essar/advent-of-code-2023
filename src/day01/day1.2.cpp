#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <map>

std::string toDigit(const std::string& input) {
    std::map<std::string, int> digits;
    digits["one"] = 1;
    digits["two"] = 2;
    digits["three"] = 3;
    digits["four"] = 4;
    digits["five"] = 5;
    digits["six"] = 6;
    digits["seven"] = 7;
    digits["eight"] = 8;
    digits["nine"] = 9;

    std::string result = input;

    for (size_t i = 0; i < result.length(); ++i) {
        for (const auto& entry : digits) {
            std::string findDigit = result.substr(i, entry.first.length());
            if (findDigit == entry.first) {
                result.replace(i, entry.first.length(), std::to_string(entry.second));
                i += std::to_string(entry.second).length() - 1;
                break;
            }
        }
    }

    return result;
}

int main() {
    std::ifstream file("day01.txt");

    if (!file.is_open()) {
        std::cerr << "unable to open the file." << std::endl;
        return 1;
    }

    int sum = 0;
    std::string s;
    while (std::getline(file, s)) {
        std::string digits = toDigit(s);
        int first = 0, last = 0;

        for (char ch : digits) {
            if (std::isdigit(ch)) {
                first = ch - '0';
                break;
            }
        }

        for (auto it = digits.rbegin(); it != digits.rend(); ++it) {
            if (std::isdigit(*it)) {
                last = *it - '0';
                break;
            }
        }

        sum += first * 10 + last;
        std::cout << first * 10 + last << std::endl;
    }

    std::cout << sum << std::endl;
    file.close();
    return 0;
}
