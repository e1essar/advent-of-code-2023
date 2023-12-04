wins = []

with open("text.txt", "r") as file:
    copies = [0] * len(file.readlines())
    file.seek(0)
    k = 1
    for line in file:
        if ':' and '|' in line:
            w_nums, my_nums = [part.split() for part in line.split(':')[1].split('|')]
            win = sum(1 for number in w_nums if number in my_nums)
            wins.append(win)
        for i in range(k, win+k):
            copies[i] += 1
        k += 1

for i in range(1, len(wins)):
    k = i
    for j in range(k, wins[i] + k):
        copies[j+1] += copies[k]
    
print(sum(copies) + len(copies))