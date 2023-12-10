#include <iostream>
#include <fstream>
#include <vector>

const int rows = 140;
const int cols = 141;

std::vector<std::vector<char>> matrix(rows, std::vector<char>(cols, ' '));

char direction(int& i, int& j) {
    if (matrix[i - 1][j] == '|' || matrix[i - 1][j] == 'F' || matrix[i - 1][j] == '7') {
        i--;
        return 'u';
    }
    else if (matrix[i + 1][j] == '|' || matrix[i + 1][j] == 'J' || matrix[i + 1][j] == 'L') {
        i++;
        return 'd';
    }
    else if (matrix[i][j + 1] == '-' || matrix[i][j + 1] == 'J' || matrix[i][j + 1] == '7') {
        j++;
        return 'r';
    }
    else if (matrix[i][j - 1] == '-' || matrix[i][j - 1] == 'F' || matrix[i][j - 1] == 'L') {
        j--;
        return 'l';
    }
    else
        return ' ';
}

void move(char &direction, int& i, int& j, int& steps) {
    if (direction == 'u') {
        if (matrix[i][j] == '|') {
            i--;
            direction = 'u';
        }
        else if (matrix[i][j] == '7') {
            j--;
            direction = 'l';
        }
        else if (matrix[i][j] == 'F') {
            j++;
            direction = 'r';
        }
    }
    else if (direction == 'd') {
        if (matrix[i][j] == '|') {
            i++;
            direction = 'd';
        }
        else if (matrix[i][j] == 'L') {
            j++;
            direction = 'r';
        }
        else if (matrix[i][j] == 'J') {
            j--;
            direction = 'l';
        }
    }
    else if (direction == 'r') {
        if (matrix[i][j] == '-') {
            j++;
            direction = 'r';
        }
        else if (matrix[i][j] == 'J') {
            i--;
            direction = 'u';
        }
        else if (matrix[i][j] == '7') {
            i++;
            direction = 'd';
        }
    }
    else if (direction == 'l') {
        if (matrix[i][j] == '-') {
            j--;
            direction = 'l';
        }
        else if (matrix[i][j] == 'L') {
            i--;
            direction = 'u';
        }
        else if (matrix[i][j] == 'F') {
            i++;
            direction = 'd';
        }
    }
    steps++;
}

int main() {

    std::ifstream inputFile("day10.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Open Error" << std::endl;
        return 1;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (inputFile.eof()) {
                std::cerr << "Err" << std::endl;
                return 1;
            }
            inputFile.get(matrix[i][j]);
        }
    }

    inputFile.close();

    int startRow = -1;
    int startCol = -1;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (matrix[i][j] == 'S') {
                startRow = i;
                startCol = j;
                break;
            }
        }
        if (startRow != -1) {
            break;
        }
    }

    int i = startRow;
    int j = startCol;
    
    int steps = 0;
    char directions = direction(i, j);
    while (matrix[i][j] != 'S') {
        move(directions, i, j, steps); 
    }
    
    std::cout << steps/2 + 1 << std::endl;
    return 0;
}
