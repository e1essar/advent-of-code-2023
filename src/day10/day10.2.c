#include <stdio.h>

#define rows 140
#define cols 140

char matrix[rows][cols];

char startDirection(int *i, int *j) {
    if (matrix[*i - 1][*j] == '|' || matrix[*i - 1][*j] == 'F' || matrix[*i - 1][*j] == '7') {
        (*i)--;
        return 'u';
    } else if (matrix[*i + 1][*j] == '|' || matrix[*i + 1][*j] == 'J' || matrix[*i + 1][*j] == 'L') {
        (*i)++;
        return 'd';
    } else if (matrix[*i][*j + 1] == '-' || matrix[*i][*j + 1] == 'J' || matrix[*i][*j + 1] == '7') {
        (*j)++;
        return 'r';
    } else if (matrix[*i][*j - 1] == '-' || matrix[*i][*j - 1] == 'F' || matrix[*i][*j - 1] == 'L') {
        (*j)--;
        return 'l';
    } else
        return ' ';
}

void move(char *direction, int *i, int *j, int *steps) {
    if (*direction == 'u') {
        if (matrix[*i][*j] == '|') {
            (*i)--;
            *direction = 'u';
        } else if (matrix[*i][*j] == '7') {
            (*j)--;
            *direction = 'l';
        } else if (matrix[*i][*j] == 'F') {
            (*j)++;
            *direction = 'r';
        }
    } else if (*direction == 'd') {
        if (matrix[*i][*j] == '|') {
            (*i)++;
            *direction = 'd';
        } else if (matrix[*i][*j] == 'L') {
            (*j)++;
            *direction = 'r';
        } else if (matrix[*i][*j] == 'J') {
            (*j)--;
            *direction = 'l';
        }
    } else if (*direction == 'r') {
        if (matrix[*i][*j] == '-') {
            (*j)++;
            *direction = 'r';
        } else if (matrix[*i][*j] == 'J') {
            (*i)--;
            *direction = 'u';
        } else if (matrix[*i][*j] == '7') {
            (*i)++;
            *direction = 'd';
        }
    } else if (*direction == 'l') {
        if (matrix[*i][*j] == '-') {
            (*j)--;
            *direction = 'l';
        } else if (matrix[*i][*j] == 'L') {
            (*i)--;
            *direction = 'u';
        } else if (matrix[*i][*j] == 'F') {
            (*i)++;
            *direction = 'd';
        }
    }
    (*steps)++;
}

int main() {
    FILE *file = fopen("day10.txt", "r");

    if (!file) {
        fprintf(stderr, "Open Error\n");
        return 1;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (fscanf(file, " %c", &matrix[i][j]) == EOF) {
                perror("Read Error");
                fclose(file);
                return 1;
            }
        }
    }

    int loopMap[rows][cols] = {0};

    fclose(file);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            loopMap[i][j] = -1;
        }
    }

    int startRow = -1;
    int startCol = -1;
    for (int i = 0; i < rows && startRow == -1; ++i) {
        for (int j = 0; j < cols && startCol == -1; ++j) {
            if (matrix[i][j] == 'S') {
                loopMap[i][j] = 0;
                startRow = i;
                startCol = j;
            }
        }
    }

    int steps = 0;
    char direction = startDirection(&startRow, &startCol);
    loopMap[startRow][startCol] = 1;

    while (matrix[startRow][startCol] != 'S') {
        move(&direction, &startRow, &startCol, &steps);
        loopMap[startRow][startCol] = 1;
    }

    int count = 0;

   for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (loopMap[i][j] == -1) {
                int inLoop = 0;
                for (int _j = 0; _j < j; _j++) {
                    if (loopMap[i][_j] != -1 && (matrix[i][_j] == 'L' || matrix[i][_j] == 'J' || matrix[i][_j] == '|' || matrix[i][_j] == 'S')) {
                        inLoop = !inLoop;
                    }
                }
                if (inLoop) {
                    matrix[i][j] = '+';
                    count ++;
                }
                else {
                    matrix[i][j] = '.';
                }
            }
        }
    }

    printf("%d\n", count);
    return 0;
}
