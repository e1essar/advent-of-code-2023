import re
import os

def process_lines(lines):
    num_map = []

    for x in range(len(lines)):
        e = 0
        while True:
            nums = re.search(r'\d+', lines[x][e:])
            if not nums:
                break
            e += nums.end()
            b = e - nums.end() + nums.start()
            num_map.append((int(lines[x][b:e]), (x, b, e - 1)))

    gears = {}
    for num in num_map:
        for x in range(num[1][0] - 1, num[1][0] + 2):
            if 0 <= x < len(lines):
                for y in range(num[1][1] - 1, num[1][2] + 2):
                    if 0 <= y < len(lines[0]) and lines[x][y] == "*":
                        gears.setdefault((x, y), []).append(num[0])

    gear_ratios = 0
    for gear in gears:
        if len(gears[gear]) == 2:
            gear_ratios += gears[gear][0] * gears[gear][1]

    return gear_ratios

with open("day03.txt", 'r') as file:
    lines = file.readlines()

total = process_lines(lines)
print(f'{total}')
