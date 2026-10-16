import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

s1 = pd.read_csv("sensor1.csv")
s2 = pd.read_csv("sensor2.csv")

# s2["y"]= s2["y"]*-1

fig, ax = plt.subplots(figsize=(8,8))
ax.plot(s1["x"], s1["y"], ".", markersize=2, label="sensor1")
ax.plot(s2["x"], s2["y"], "o-", markersize=4, label="sensor2")

ax.set_aspect("equal")

ax.set_xlabel("x [m]")
ax.set_ylabel("y [m]")
ax.grid(True)
ax.legend()
fig.savefig("graf.png", dpi=150)

fig, (ax_x, ax_y) = plt.subplots(2, 1, sharex=True, figsize=(10,6))

for s, name in [(s1, "sensor1"),(s2, "sensor2")]:
    ax_x.plot(s["timestamp"], s["x"], label=name)
    ax_y.plot(s["timestamp"], s["y"], label=name)

ax_x.set_ylabel("x [m]")
ax_y.set_ylabel("y [m]")
ax_y.set_xlabel("t [m]")

for a in (ax_x, ax_y):
    a.grid(True)
    a.legend()
fig.savefig("graf2.png", dpi=150)

plt.show()