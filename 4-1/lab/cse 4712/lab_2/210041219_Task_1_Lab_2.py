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


def get_moves(position, size):
    moves = []
    row, col = divmod(position, size)
    if row > 0: moves.append(position - size)  # up
    if row < size - 1: moves.append(position + size)  # down
    if col > 0: moves.append(position - 1)  # left
    if col < size - 1: moves.append(position + 1)  # right
    return moves

def successors_fn(state, graph):
    return graph.get(state, [])

def goal_test_fn(state, goal):
    return state == goal

# --- CLI Interface ---
def parse_arguments():
    parser = argparse.ArgumentParser(description='Task 1')
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

    graph = {
        'A': ['B', 'C'],
        'B': ['D', 'E'],
        'C': ['F'],
        'D': [],
        'E': ['F'],
        'F': []
    }

    args = parse_arguments()
    start_state = 'A'
    goal_state = 'F'
    
    print(f"Initial State:")
    print(start_state)

    solution = uninformed_search(
        start_state=start_state,
        goal_test_fn=lambda s: goal_test_fn(s, goal_state),
        successor_fn=lambda s: successors_fn(s, graph),
        cost_fn=lambda c, n: 1,
        strategy=args.strategy
    )
    
    if solution:
        print_solution(solution, len(graph))
    else:
        print("No solution found.")

