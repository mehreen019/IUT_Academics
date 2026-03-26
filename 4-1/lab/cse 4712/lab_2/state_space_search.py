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

def puzzle_successors(state, size):
    zero_pos = state.index(0)
    successors = []
    for move in get_moves(zero_pos, size):
        new_state = list(state)
        new_state[zero_pos], new_state[move] = new_state[move], new_state[zero_pos]
        successors.append(tuple(new_state))
    return successors

def puzzle_goal_test(state, size):
    return state == create_goal_state(size)

# --- CLI Interface ---
def parse_arguments():
    parser = argparse.ArgumentParser(description='Solve N-Puzzle using uninformed search.')
    parser.add_argument('--size', type=int, default=3, help='Puzzle size (e.g., 3 for 8-puzzle)')
    parser.add_argument('--start', type=str, help='Comma-separated list of initial state tiles')
    parser.add_argument('--strategy', choices=['dfs', 'bfs', 'ucs'], default='bfs', 
                        help='Search strategy: dfs, bfs, or ucs')
    return parser.parse_args()

def print_solution(solution, size):
    if not solution:
        return
    
    print("\nSolution Path:")
    for step_num, step in enumerate(solution):
        print(f"Step {step_num}:")
        for i in range(size):
            row = step[i*size:(i+1)*size]
            print(' '.join(str(x) if x != 0 else '_' for x in row))
        print()
    print(f"Total steps: {len(solution) - 1}")

# --- Entry Point ---
if __name__ == '__main__':
    args = parse_arguments()
    
    if args.start:
        try:
            start_state = tuple(int(x) for x in args.start.strip().split(','))
            if len(start_state) != args.size * args.size:
                print(f"Start state must have {args.size * args.size} elements.")
                sys.exit(1)
        except ValueError:
            print("Invalid start state. Use comma-separated integers.")
            sys.exit(1)
    else:
        # Default test case for 8-puzzle
        start_state = (1, 2, 3, 4, 0, 5, 6, 7, 8)
    
    print(f"Initial State (size={args.size}):")
    for i in range(args.size):
        row = start_state[i*args.size:(i+1)*args.size]
        print(' '.join(str(x) if x != 0 else '_' for x in row))
    print()
    
    solution = uninformed_search(
        start_state=start_state,
        goal_test_fn=lambda s: puzzle_goal_test(s, args.size),
        successor_fn=lambda s: puzzle_successors(s, args.size),
        cost_fn=lambda c, n: 1,
        strategy=args.strategy
    )
    
    if solution:
        print_solution(solution, args.size)
    else:
        print("No solution found.")
