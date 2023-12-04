#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>

int main() {
    std::ifstream file("day02.txt");

    if (!file.is_open()) {
        std::cerr << "unable to open the file." << std::endl;
        return 1;
    }

    int red, green, blue, result = 0;
    std::string s;
    while (std::getline(file, s)) {
        red = 0;
        green = 0;
        blue = 0;
        std::vector<std::string> vec;
        char sep = ';';
        for (int p = 0, q = 0; p != s.npos; p = q)
            vec.push_back(s.substr(p + (p != 0), (q = s.find(sep, p + 1)) - p - (p != 0)));

        for (int i = 0; i < vec.size(); i++) {
            if (vec[i].find("red") != std::string::npos) {
                std::string num = vec[i].substr(vec[i].find("red") - 3, 3);
                if (stoi(num) > red) {
                    red = stoi(num);
                }
            }
            if (vec[i].find("green") != std::string::npos) {
                std::string num = vec[i].substr(vec[i].find("green") - 3, 3);
                if (stoi(num) > green) {
                    green = stoi(num);
                }
            }
            if (vec[i].find("blue") != std::string::npos) {
                std::string num = vec[i].substr(vec[i].find("blue") - 3, 3);
                if (stoi(num) > blue) {
                    blue = stoi(num);
                }
            }
        }
        result += red * green * blue;
    }
    std::cout << result << std::endl;
}
