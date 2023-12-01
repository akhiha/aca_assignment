import subprocess
import re
import pandas as pd

# Function to run cachegrind and parse output
def run_cachegrind(l1_size, l2_size):
    command = [
        "valgrind", "--tool=cachegrind",
        f"--I1={l1_size},8,64", f"--D1={l1_size},8,64",
        f"--LL={l2_size},16,64", "./3_cache"
    ]
    result = subprocess.run(command, capture_output=True, text=True)
    output = result.stderr

    # Regular expressions to find cache misses
    l1_misses = re.search(r'I1\s+misses:\s+(\d+)', output)
    l2_misses = re.search(r'LL\s+misses:\s+(\d+)', output)

    if l1_misses and l2_misses:
        return (int(l1_misses.group(1)), int(l2_misses.group(1)))
    else:
        return (None, None)

# Sizes to test (in KB)
l1_sizes = [32768, 65536] # Extend this list
l2_sizes = [1048576, 2097152] # Extend this list

data = []

for l1_size in l1_sizes:
    for l2_size in l2_sizes:
        l1_misses, l2_misses = run_cachegrind(l1_size, l2_size)
        total_miss = l1_misses + l2_misses
        total_miss_ratio = total_miss / 2
        if l1_misses is not None and l2_misses is not None:
            data.append({
                'L1_Size': l1_size,
                'L2_Size': l2_size,
                'L1_Misses': l1_misses,
                'L2_Misses': l2_misses,
                'Miss_Ratio': total_miss_ratio
            })

# Convert to DataFrame and save as CSV
df = pd.DataFrame(data)
df.to_csv('cache_results.csv', index=False)
print("Data collection complete. Results saved to 'cache_results.csv'.")
