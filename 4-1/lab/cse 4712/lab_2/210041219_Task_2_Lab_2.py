import heapq
import argparse
import sys
from collections import deque

# --- Generic Uninformed Search Implementation ---
def uninformed_search(
    start_state,
    goal_test_fn,
    successor_fn,
    cost_fn=lambda current, neighbor: 1,
    strategy='bfs'
):
    """
    Generic uninformed search supporting DFS, BFS, and UCS.
    
    Args:
        start_state: Initial state
        goal_test_fn: Function that returns True if state is goal
        successor_fn: Function that returns list of successor states
        cost_fn: Function that returns cost between states (for UCS)
        strategy: 'dfs', 'bfs', or 'ucs'
    """
    if strategy == 'dfs':
        frontier = [(start_state, [], 0)]  # Stack: (state, path, cost)
    elif strategy == 'bfs':
        frontier = deque([(start_state, [], 0)])  # Queue: (state, path, cost)
    elif strategy == 'ucs':
        frontier = []  # Priority queue: (cost, state, path)
        heapq.heappush(frontier, (0, start_state, []))
    else:
        raise ValueError(f"Unknown strategy: {strategy}")
    
    visited = set()
    open_nodes = 1
    closed_nodes = 0
    
    while frontier:
        # Pop from frontier based on strategy
        if strategy == 'dfs':
            current, path, g = frontier.pop()  # LIFO (stack)
        elif strategy == 'bfs':
            current, path, g = frontier.popleft()  # FIFO (queue)
        else:  # ucs
            g, current, path = heapq.heappop(frontier)  # Min-heap
        
        closed_nodes += 1
        
        if goal_test_fn(current):
            print(f"Strategy: {strategy.upper()}")
            print(f"Open Nodes: {open_nodes}")
            print(f"Closed Nodes: {closed_nodes}")
            return path + [current]
        
        if current in visited:
            continue
        
        visited.add(current)
        
        for neighbor in successor_fn(current):
            if neighbor not in visited:
                new_cost = g + cost_fn(current, neighbor)
                
                if strategy == 'dfs':
                    frontier.append((neighbor, path + [current], new_cost))
                elif strategy == 'bfs':
                    frontier.append((neighbor, path + [current], new_cost))
                else:  # ucs
                    heapq.heappush(frontier, (new_cost, neighbor, path + [current]))
                
                open_nodes += 1
    
    print(f"Strategy: {strategy.upper()}")
    print("No solution found.")
    print(f"Open Nodes: {open_nodes}")
    print(f"Closed Nodes: {closed_nodes}")
    return None

def successor_only_states(s):
    return [pos for (pos, act) in successors_fn(s)]

# --- Puzzle Utilities ---
def create_goal_state(size):
    return tuple(list(range(1, size * size)) + [0])

def get_moves(position, size):
    moves = []
    row, col = divmod(position, size)
    if row > 0: moves.append(position - size)  # up
    if row < size - 1: moves.append(position + size)  # down
    if col > 0: moves.append(position - 1)  # left
    if col < size - 1: moves.append(position + 1)  # right
    return moves

def successors_fn(state, grid):
    pos, cleaned = state
    """
    successors = []
    moves = [(0,1,'right'), (0,-1,'left'), (1,0,'down'), (-1,0,'up')]

    for dr, dc, action in moves:
        nr, nc = pos[0]+dr, pos[1]+dc

        if 0 <= nr < rows and 0 <= nc < cols and grid[nr][nc] != '#':
            new_cleaned = cleaned
            if grid[nr][nc] == 'T':
                new_cleaned = cleaned | {(nr, nc)}
            
            successors.append(((nr, nc, new_cleaned)))
    return successors
    """
    moves = []
    directions = {
        "up": (-1, 0),
        "down": (1, 0),
        "left": (0, -1),
        "right": (0, 1)
    }

    for action, (dx, dy) in directions.items():
        nx, ny = x + dx, y + dy
        if 0 <= nx < rows and 0 <= ny < cols and grid[nx][ny] == 0:
            moves.append(( (nx, ny), action ))  # store action also

    return moves
    

def goal_test_fn(state, to_clean):
    pos, cleaned = state
    return cleaned == to_clean

def extract_actions(solution):
    actions = []
    for i in range(len(solution)-1):
        cur = solution[i]
        nxt = solution[i+1]

        # find which action matches the next step
        for pos, act in successors_fn(cur):
            if pos == nxt:
                actions.append(act)
                break
    return actions

# --- CLI Interface ---
def parse_arguments():
    parser = argparse.ArgumentParser(description='Solve N-Puzzle using uninformed search.')
    parser.add_argument('--strategy', choices=['dfs', 'bfs', 'ucs'], default='bfs', 
                        help='Search strategy: dfs, bfs, or ucs')
    return parser.parse_args()

if __name__ == '__main__':
    args = parse_arguments()
    grid = [
    ['#','#','#','#','#','#','#','#'],
    ['#','R','.','.','.','T','.','#'],
    ['#','.','.','#','#','.','.','#'],
    ['#','.','.','#','.','.','T','#'],
    ['#','#','#','#','#','#','#','#']
    ]
    
    world = '########\n#R...T.#\n##..##..#\n##..#..T#\n#########'
    
    grid = world.strip("\n").split("\n")
    rows = len(grid)
    cols = len(grid[0])
    
    start_pos = (0, 0)
    to_clean = []
    cleaned = []
    
    for i in range(len(grid)):
        for j in range(len(grid[0])):
            if grid[i][j] == 'R':
                start_pos = (i, j)
            if grid[i][j] == 'T':
                to_clean.append((i, j))
    
    start_state = start_pos, cleaned
    
    solution = uninformed_search(
        start_state=start_state,
        goal_test_fn=lambda s: goal_test_fn(s, to_clean),
        successor_fn=lambda s: successors_fn(s, grid, to_clean, rows, cols),
        cost_fn=lambda c, n: 1,
        strategy=args.strategy
    )
    
    if solution:
        actions = extract_actions(solution)
        print("Actions :", " , ".join(actions))
    else:
        print("No solution found.")
