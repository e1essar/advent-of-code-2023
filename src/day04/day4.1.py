total = 0

with open("text.txt", "r") as file:
    for line in file:
        if ':' and '|' in line:
            w_nums, my_nums = [part.split() for part in line.split(':')[1].split('|')]
            win = sum(1 for number in w_nums if number in my_nums)
            total += int(2**(win - 1))

print(total)
