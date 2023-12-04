import string

def getNumbers() -> None:
    start, end = 0, 0
    sum = 0
    for i in range(n):
        j = 0
        while j < m:
            if matrix[i][j].isdigit():
                num = 0
                start = j
                while j < m and matrix[i][j].isdigit():
                    num *= 10
                    num += int(matrix[i][j])
                    j += 1
                end = j - 1
                if numNearSymbol(i, start, end):
                    sum += num
            j += 1
    print(sum)

def isSymbol(symbol: str) -> bool:
    return symbol != '.' and symbol in string.punctuation


def numNearSymbol(row:int, colStart:int, colEnd:int) -> bool:
    for j in range(colStart, colEnd + 1):
        if row - 1 >= 0 and isSymbol(matrix[row - 1][j]):
            return True
        if row + 1 < n and isSymbol(matrix[row + 1][j]):
            return True
    if colStart - 1 >= 0:
        if row + 1 < n and isSymbol(matrix[row + 1][colStart - 1]):
            return True
        if isSymbol(matrix[row][colStart - 1]):
            return True
        if row - 1 >= 0 and isSymbol(matrix[row - 1][colStart - 1]):
            return True

    if colEnd + 1 < m:
        if row + 1 < n and isSymbol(matrix[row + 1][colEnd + 1]):
            return True
        if isSymbol(matrix[row][colEnd + 1]):
            return True
        if row - 1 >= 0 and isSymbol(matrix[row - 1][colEnd + 1]):
            return True

    return False


if __name__ == "__main__":
    with open('day03.txt', 'r') as file:
        matrix = [line.strip() for line in file.readlines()]

    n = len(matrix)
    m = len(matrix[0])
    getNumbers()
