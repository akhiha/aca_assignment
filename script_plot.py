import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import pandas as pd

# Load data from CSV
data = pd.read_csv('cache_results.csv')

# Assuming the CSV has columns 'L1_Size', 'L2_Size', and 'Miss_Ratio'
L1 = data['L1_Size']
L2 = data['L2_Size']
Miss_Ratio = data['Miss_Ratio']

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# Create a 3D scatter plot
scat = ax.scatter(L1, L2, Miss_Ratio, c=Miss_Ratio, cmap='viridis')

ax.set_xlabel('L1 Cache Size (KB)')
ax.set_ylabel('L2 Cache Size (KB)')
ax.set_zlabel('Miss Ratio')

# Adding a color bar
cbar = plt.colorbar(scat)
cbar.set_label('Miss Ratio')

plt.show()
