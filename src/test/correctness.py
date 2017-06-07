import numpy as np
import pylab as plt


print("Drawing plot: Lambda as a function of correctness")
with open("Data/correctness.txt") as data:
    lambdaV   = []
    percent   = []

    for line in data:
        points = np.fromstring(line, dtype=float, sep=" ")

        lambdaV.append(int(points[0]))
        percent.append(points[1])

data.close()

xp = np.linspace(0, 10, 100)

fit = np.polyfit(lambdaV,percent,1)
fit_fn = np.poly1d(fit) 
# fit_fn is now a function which takes in x and returns an estimate for y

plt.plot(lambdaV,percent, '.', xp, fit_fn(xp), '-')
plt.xlabel("$\lambda$")
plt.ylabel("Correctness %")
plt.ylim([0.0, 1.0])
plt.title("Correctness according to $\lambda$")
plt.savefig("Data/correctness.png")
print("Saving correctness plot as correctness.png")

