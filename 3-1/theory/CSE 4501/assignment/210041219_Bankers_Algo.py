import csv
import sys
from collections import defaultdict

def validate_and_parse_csv(file_path):
    try:
        with open(file_path, 'r') as f:
            reader = csv.reader(f, delimiter='\t')
            rows = list(reader)
    except Exception as e:
        return None, "Invalid File Format"

    if not rows:
        return None, "Invalid File Format"
    
    header = rows[0]
    if len(header) < 1 or header[0] != 'PID':
        return None, "Invalid File Format"
    
    groups = []
    current_group = None
    for col in header[1:]:
        parts = col.split('_')
        if len(parts) != 2 or parts[0] not in ['Allocation', 'Max', 'Available', 'Need']:
            return None, "Invalid File Format"
        prefix, resource = parts
        if not current_group or current_group[0] != prefix:
            groups.append((prefix, []))
            current_group = groups[-1]
        current_group[1].append(resource)
    
    expected_groups = ['Allocation', 'Max', 'Available', 'Need']
    if len(groups) != 4 or any(groups[i][0] != expected_groups[i] for i in range(4)):
        return None, "Invalid File Format"
    
    resources = groups[0][1]
    for group in groups[1:]:
        if group[1] != resources:
            return None, "Invalid File Format"
    
    resource_order = resources
    n_resources = len(resource_order)
    
    processes = []
    available = None
    for row in rows[1:]:
        if len(row) != len(header):
            return None, "Invalid File Format"
        pid = row[0]
        alloc = []
        max_ = []
        avail = []
        need = []
        for r in resource_order:
            alloc_col = f'Allocation_{r}'
            max_col = f'Max_{r}'
            avail_col = f'Available_{r}'
            need_col = f'Need_{r}'
            try:
                alloc_val = int(row[header.index(alloc_col)])
                max_val = int(row[header.index(max_col)])
                need_val = int(row[header.index(need_col)])
                if rows.index(row) == 1:
                    avail_val = int(row[header.index(avail_col)])
                else:
                    if row[header.index(avail_col)] != '-':
                        return None, "Invalid File Format"
                    avail_val = None
            except ValueError:
                return None, "Invalid File Format"
            except Exception as e:
                return None, "Invalid File Format"
            
            alloc.append(alloc_val)
            max_.append(max_val)
            need.append(need_val)
            if rows.index(row) == 1:
                avail.append(avail_val)
        
        if any(n < 0 for n in alloc + max_ + need) or (rows.index(row) == 1 and any(a < 0 for a in avail)):
            return None, "Invalid File Format"
        
        computed_need = [max_[i] - alloc[i] for i in range(n_resources)]
        if computed_need != need:
            return None, "Invalid File Format"
        
        processes.append({
            'pid': pid,
            'allocation': alloc,
            'max': max_,
            'need': need
        })
        
        if rows.index(row) == 1:
            available = avail
    
    if available is None:
        return None, "Invalid File Format"
    
    for row in rows[2:]:
        for r in resource_order:
            avail_col = f'Available_{r}'
            if row[header.index(avail_col)] != '-':
                return None, "Invalid File Format"
    
    return {
        'resources': resource_order,
        'processes': processes,
        'available': available
    }, "Valid File Format"

def bankers_algorithm(data):
    processes = data['processes']
    available = data['available']
    n_resources = len(data['resources'])
    n_processes = len(processes)
    allocations = [p['allocation'] for p in processes]
    needs = [p['need'] for p in processes]
    pids = [p['pid'] for p in processes]
    
    safe_sequences = []
    
    def backtrack(current_avail, finished, path, depth):
        if len(path) == n_processes:
            safe_sequences.append(path.copy())
            return
        
        for i in range(n_processes):
            if not finished[i]:
                need = needs[i]
                can_allocate = all(need[j] <= current_avail[j] for j in range(n_resources))
                
                print(f"Step {depth}: Checking {pids[i]}. Need {need} <= Available {current_avail}? {'Yes' if can_allocate else 'No'}")
                if can_allocate:
                    new_avail = [current_avail[j] + allocations[i][j] for j in range(n_resources)]
                    new_finished = finished.copy()
                    new_finished[i] = True
                    new_path = path + [pids[i]]
                    print(f"Step {depth}: Allocated {pids[i]}. New Available: {allocations[i]} + {current_avail} = {new_avail}. Current sequence: {new_path}")
                    backtrack(new_avail, new_finished, new_path, depth + 1)
                    new_finished[i] = False
    
    print("\nReasoning Steps:")
    backtrack(available.copy(), [False]*n_processes, [], 1)
    
    return safe_sequences

def main():
    if len(sys.argv) != 2:
        print("Usage: python 210041219_Banker's_Algo.py <input_file.csv>")
        return
    
    input_file = sys.argv[1]
    data, msg = validate_and_parse_csv(input_file)
    print(msg)
    if msg != "Valid File Format":
        return
    
    safe_sequences = bankers_algorithm(data)
    
    print("\nResults:")
    if safe_sequences:
        print("1. At least one safe sequence:", ' -> '.join(safe_sequences[0]))
        print("2. Total number of safe sequences:", len(safe_sequences))
    else:
        print("1. No safe sequences found.")
        print("2. Total number of safe sequences: 0")

if __name__ == "__main__":
    main()