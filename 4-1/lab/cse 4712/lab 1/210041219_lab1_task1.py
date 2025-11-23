from typing import List
import sys

grid = [line.strip('\n') for line in sys.stdin]
r1 = 0
c1 = 0
r2 = len(grid) - 1
c2 = len(grid[0]) - 1

for i in range(len(grid)):
	for j in range(len(grid[i])):
		if grid[i][j] == 'S':
			r1 = i
			c1 = j
		elif grid[i][j] == 'G':
			r2 = i
			c2 = j

def BFS(grid, r1, c1, r2, c2):
	visited = [[False for _ in range(len(grid[0]))] for _ in range(len(grid))]
	visited[r1][c1] = True

	queue = [(r1, c1)]
	
	while queue:
		r, c = queue.pop(0)
		if r == r2 and c == c2:
			return True
		for dr, dc in [(1, 0), (-1, 0), (0, 1), (0, -1)]:
			nr = r + dr
			nc = c + dc
			if nr < 0 or nr >= len(grid) or nc < 0 or nc >= len(grid[0]) or grid[nr][nc] == '#':
				continue
			if visited[nr][nc] == False:
				visited[nr][nc] = True
				queue.append((nr, nc))
	return False

print(f"Start: {r1}, {c1}")
print(f"End: {r2}, {c2}")
print("Possible to reach goal ?: " + ("Yes" if BFS(grid, r1, c1, r2, c2) else "No"))