import re
import os

def process_line(line, lines, i):
    result = 0
    e = 0

    while True:
        numbers = re.search(r'\d+', line[e:])
        if not numbers:
            break

        e += numbers.end()
        b = e - numbers.end() + numbers.start()

        if b > 0 and line[b - 1] != '.':
            result += int(re.sub('[^0-9]+', '', line[b:e]))
        elif e < len(line) and line[e] != '.':
            result += int(re.sub('[^0-9]+', '', line[b:e]))
        else:
            found = False

            if i != 0:
                for z in range(b - 1 if b > 0 else b, e + 1 if e < len(line) else e):
                    if lines[i - 1][z] != '.':
                        result += int(re.sub('[^0-9]+', '', line[b:e]))
                        found = True
                        break

            if not found and i < len(lines) - 1:
                for z in range(b - 1 if b > 0 else b, e + 1 if e < len(line) else e):
                    if lines[i + 1][z] != '.':
                        result += int(re.sub('[^0-9]+', '', line[b:e]))
                        break

    return result


with open("day03.txt", 'r') as file:
    lines = file.readlines()

total = 0

for i in range(len(lines)):
    line = lines[i].strip()
    result = process_line(line, lines, i)
    total += result

print(f'{total}')
