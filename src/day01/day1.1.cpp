#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

int main() {
    std::ifstream file("day01.txt");

    if (!file.is_open()) {
        std::cerr << "Unable to open the file." << std::endl;
        return 1;
    }

    int sum = 0;

    std::string s;
    while (std::getline(file, s)) {
        //std::cout << s << std::endl;

        int first = 0, last = 0;

        for (char ch : s) {
            if (std::isdigit(ch)) {
                first = ch - '0';
                break;
            }
        }

        for (auto it = s.rbegin(); it != s.rend(); ++it) {
            if (std::isdigit(*it)) {
                last = *it - '0';
                break;
            }
        }

        sum += first * 10 + last;

        //std::cout << first * 10 + last << std::endl;
    }

    std::cout << sum << std::endl;

    file.close();

    return 0;
}