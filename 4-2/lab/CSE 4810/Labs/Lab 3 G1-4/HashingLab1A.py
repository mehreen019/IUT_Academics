import time

class HashTable:
    def __init__(self, size, mode="LP"):
        self.capacity = size
        self.mode = mode # "LP" for Linear Probing, "DH" for Double Hashing
        self.table = [None] * self.capacity

    def _hash1(self, key):
        # TODO: Implement primary hash function using the Division Method
        return 0

    def _hash2(self, key):
        # TODO: Implement secondary hash function for Double Hashing
        return 1

    def insert(self, key):
        # TODO: Implement insertion logic with proper collision resolution
        return True

    def search(self, key):
        probes = 0
        found = False
        
        # TODO: Implement search logic.
        # CRITICAL: Increment 'probes' every single time you look at a slot index.
        
        return found, probes


def generate_insertion_keys(count):
    return [i * 10 for i in range(1, count + 1)] # 10, 20, 30...

def generate_unsuccessful_keys(count):
    return [i * 10 + 5 for i in range(1, count + 1)] # 15, 25, 35...


def main():
    m = 1009 # Assigned prime table size
    num_test_keys = 200
    
    with open("data.txt", "w") as f:
        f.write("#Alpha\tTime_LP\tTime_DH\tProbes_LP\tProbes_DH\n")
        
        print("Starting empirical profiling for Flavor 1 (Unsuccessful Searches)...")
        
        for i in range(1, 10):
            alpha = i / 10.0
            num_elements = int(m * alpha)
            
            insertion_keys = generate_insertion_keys(num_elements)
            ghost_keys = generate_unsuccessful_keys(num_test_keys)
            
            # ------------------------------------------
            # PROFILE LINEAR PROBING
            # ------------------------------------------
            lp_table = HashTable(m, mode="LP")
            for key in insertion_keys:
                lp_table.insert(key)
                
            lp_probes = 0
            start_lp = time.perf_counter()
            for ghost_key in ghost_keys:
                _, p = lp_table.search(ghost_key)
                lp_probes += p
            stop_lp = time.perf_counter()
            duration_lp = (stop_lp - start_lp) * 1_000_000
            avg_probes_lp = lp_probes / num_test_keys
            
            # ------------------------------------------
            # PROFILE DOUBLE HASHING
            # ------------------------------------------
            dh_table = HashTable(m, mode="DH")
            for key in insertion_keys:
                dh_table.insert(key)
                
            dh_probes = 0
            start_dh = time.perf_counter()
            for ghost_key in ghost_keys:
                _, p = dh_table.search(ghost_key)
                dh_probes += p
            stop_dh = time.perf_counter()
            duration_dh = (stop_dh - start_dh) * 1_000_000
            avg_probes_dh = dh_probes / num_test_keys
            
            f.write(f"{alpha:.2f}\t{duration_lp:.2f}\t{duration_dh:.2f}\t{avg_probes_lp:.2f}\t\t{avg_probes_dh:.2f}\n")
            print(f"Finished processing Load Factor (\u03B1): {alpha:.1f}")

    print("Profiling completed successfully. Results recorded in data.txt")

if __name__ == "__main__":
    main()