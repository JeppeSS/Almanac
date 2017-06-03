import numpy as np
import pylab as plt
from scipy import stats


print("Drawing plot: Lambda as a function of time")
with open("Data/timeComplex.txt") as data:
    lambdaV = []
    timeC   = []

    for line in data:
        points = np.fromstring(line, dtype=float, sep=" ")

        lambdaV.append(int(points[0]))
        timeC.append(points[1])

data.close()

xp = np.linspace(0, 10, 50)

fit = np.polyfit(lambdaV,timeC,3)
fit_fn = np.poly1d(fit) 
# fit_fn is now a function which takes in x and returns an estimate for y

plt.plot(lambdaV,timeC, '.', xp, fit_fn(xp), '-')
plt.xlabel("$\lambda$")
plt.xlim([0, 10])
plt.ylim([0, 465])
plt.ylabel("Seconds")
plt.title("Public key generation")
plt.savefig("Data/publickey.png")
print("Saving Public key plot as publickey.png")

