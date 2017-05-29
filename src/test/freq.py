import numpy as np
import pylab as plt


print("Drawing Frequency plot")
with open("Data/freq.txt") as data:
    freq = []
    for line in data:
        freq.append(int(line))

data.close()

dataPoints = len(freq)

z = np.unique(freq, return_counts=True)
plt.bar(z[0], z[1], width=0.80)
plt.ylabel('Frequency')
plt.xlabel('Random Range')
plt.title('Number of samples: %d' % dataPoints)
plt.savefig("Data/freq.png")
print("Saving frequency plot as freq.png")

