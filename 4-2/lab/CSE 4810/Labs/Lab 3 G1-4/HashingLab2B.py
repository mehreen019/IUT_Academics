import time
import math

class HashTable:
    def __init__(self, size, mode="LP"):
        self.capacity = size
        self.mode = mode # "LP" for Linear Probing, "DH" for Double Hashing
        self.table = [None] * self.capacity # Elements stored as (key, "OCCUPIED") or (key, "DELETED")
        self.KNUTH_A = 0.6180339887

    def _hash1(self, key):
        # TODO: Implement primary hash function using the Multiplication Method
        return 0

    def _hash2(self, key):
        # TODO: Implement secondary hash function for Double Hashing
        # Must always produce an odd number
        return 1

    def insert(self, key):
        # TODO: Implement insertion logic handling OCCUPIED and DELETED spots
        pass

    def search(self, key):
        probes = 0
        found = False
        
        # TODO: Implement successful search logic.
        # CRITICAL: Increment 'probes' every single time you look at a slot index.
        # Ensure you scan right past "DELETED" tokens.
        
        return found, probes

    def remove(self, key):
        # TODO: Implement lazy deletion by tagging the slot status as "DELETED"
        pass


def generate_keys(count):
    return [i * 7 + 3 for i in range(1, count + 1)]


def main():
    m = 1024 # Assigned power-of-2 table size
    
    with open("data.txt", "w") as f:
        f.write("#Alpha\tTime_LP\tTime_DH\tProbes_LP\tProbes_DH\n")
        
        print("Starting empirical profiling for Flavor 2 (Lazy Deletion Overhead)...")
        
        # Stepping active load factor alpha from 0.1 to 0.45
        for step in range(2, 10):
            alpha = (step * 5) / 100.0
            active_elements = int(m * alpha)
            total_to_insert = active_elements * 2
            
            keys = generate_keys(total_to_insert)
            
            # ------------------------------------------
            # PROFILE LINEAR PROBING
            # ------------------------------------------
            lp_table = HashTable(m, mode="LP")
            for key in keys:
                lp_table.insert(key)
            for i in range(0, total_to_insert, 2):
                lp_table.remove(keys[i]) # Delete half
                
            lp_probes = 0
            start_lp = time.perf_counter()
            for i in range(1, total_to_insert, 2): # Search remaining keys
                _, p = lp_table.search(keys[i])
                lp_probes += p
            stop_lp = time.perf_counter()
            duration_lp = (stop_lp - start_lp) * 1_000_000
            avg_probes_lp = lp_probes / active_elements
            
            # ------------------------------------------
            # PROFILE DOUBLE HASHING
            # ------------------------------------------
            dh_table = HashTable(m, mode="DH")
            for key in keys:
                dh_table.insert(key)
            for i in range(0, total_to_insert, 2):
                dh_table.remove(keys[i])
                
            dh_probes = 0
            start_dh = time.perf_counter()
            for i in range(1, total_to_insert, 2):
                _, p = dh_table.search(keys[i])
                dh_probes += p
            stop_dh = time.perf_counter()
            duration_dh = (stop_dh - start_dh) * 1_000_000
            avg_probes_dh = dh_probes / active_elements
            
            f.write(f"{alpha:.2f}\t{duration_lp:.2f}\t{duration_dh:.2f}\t{avg_probes_lp:.2f}\t{avg_probes_dh:.2f}\n")
            print(f"Finished processing Active Load Factor (\u03B1): {alpha:.2f}")

    print("Profiling completed successfully. Results recorded in data.txt")

if __name__ == "__main__":
    main()