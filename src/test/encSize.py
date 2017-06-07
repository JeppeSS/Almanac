import numpy as np
import pylab as plt


print("Drawing plot: Lambda as a function of time")
with open("Data/encSize.txt") as data:
    lambdaV   = []
    encSize   = []

    for line in data:
        points = np.fromstring(line, dtype=int, sep=" ")

        lambdaV.append(int(points[0]))
        encSize.append(int(points[1]))

data.close()

xp = np.linspace(0, 10, 100)

fit = np.polyfit(lambdaV,encSize,4)
fit_fn = np.poly1d(fit) 
# fit_fn is now a function which takes in x and returns an estimate for y

plt.plot(lambdaV,encSize, '.', xp, fit_fn(xp), '-')
plt.xlabel("$\lambda$")
plt.ylabel("Bit size", labelpad=1)
plt.xlim([0, 10])
plt.ylim([0, 101000])
plt.title("Encryption size of a single Bit according to $\lambda$")
plt.savefig("Data/encryptBit.png")
print("Saving Encryption plot as encryptionBit.png")

