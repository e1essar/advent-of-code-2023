def solve(src, grid):
	n, m = len(grid), len(grid[0])
	q = [src]
	vis = [[False for i in range(m)] for j in range(n)]
	seen = set()
	ans = 0
	while len(q) > 0:
		r, c, dr, dc = q.pop(0)
		if r < 0 or c < 0 or r == n or c == m or (r, c, dr, dc) in seen:
			continue

		seen.add((r, c, dr, dc))
		if not vis[r][c]:
			ans += 1
		vis[r][c] = True

		if grid[r][c] == "\\":
			dr, dc = dc, dr
		elif grid[r][c] == "/":
			dr, dc = -dc, -dr
		elif grid[r][c] == "|" and dc != 0:
			q.append((r-1, c, -1, 0))
			dr, dc = 1, 0
		elif grid[r][c] == "-" and dr != 0:
			q.append((r, c-1, 0, -1))
			dr, dc = 0, 1

		q.append((r+dr, c+dc, dr, dc))
	return ans

def part1(file_path):
    grid = []
    with open(file_path) as file:
        for line in file:
            grid.append(line.strip())
    print(solve((0, 0, 0, 1), grid))


if __name__ == "__main__":
    file_path = "C:\\Users\\Igor\\Desktop\\day16.txt"
    part1(file_path)

