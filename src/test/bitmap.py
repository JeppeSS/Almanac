
import numpy as np
import pylab as plt


print("Drawing bitmap plot")
with open("Data/bitmap.txt") as data:
    dim = int(data.readline())
    bitmap = np.ones((dim, dim), dtype=int)

    x = 0
    for line in data:
        bits = np.fromstring(line, dtype=int, sep=',')
        
        bits = list(bits)

        for y in range(len(bits)):
            bitmap[x][y] = bits[y]

        x += 1


data.close()

plt.imshow(bitmap, cmap='gray', interpolation='nearest')
plt.axis('off')
plt.savefig('Data/bitmap.png')
