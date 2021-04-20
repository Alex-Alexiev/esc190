import numpy as np
from numpy.linalg import norm
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

def f(x, y):
    r = np.sqrt(x**2 + y**2)
    return -.4 + (x+15)/30. + (y+15)/40.+.5*np.sin(r)

def drdx(x, y, r):
    return (.5*(x**2 + y**2)**-.5)*(2*x)

def drdy(x, y, r):
    return (.5*(x**2 + y**2)**-.5)*(2*y)

def dfdx(x, y):
    r = np.sqrt(x**2 + y**2)
    return 1/30. + .5*np.cos(r)*drdx(x, y, r)

def dfdy(x, y):
    r = np.sqrt(x**2 + y**2)
    return 1/40. + .5*np.cos(r)*drdy(x, y, r)

def gradf(x, y):
    return np.array([dfdx(x, y), dfdy(x, y)])


def grad_descent2(f, gradf, init_t, alpha):
    EPS = 1e-5
    prev_t = init_t-10*EPS
    t = init_t.copy()

    while norm(t - prev_t) >  EPS:
        prev_t = t.copy()
        t -= alpha*gradf(t[0], t[1])
        print(t, f(t[0], t[1]), gradf(t[0], t[1]))

    return t


x = np.arange(-15, 15, 0.25)
y = np.arange(-15, 15, 0.25)
X, Y = np.meshgrid(x, y)
Z = f(X, Y)
fig = plt.figure(1)
ax = fig.gca(projection='3d')
surf = ax.plot_surface(X, Y, Z, rstride=1, cstride=1, cmap=plt.cm.coolwarm,
                       linewidth=0, antialiased=False)
ax.set_zlim(-2.01, 2.01)

fig.colorbar(surf, shrink=0.5, aspect=5)
plt.show()

#grad_descent2(f, gradf, np.array([1.0, 1.0]), 0.01)
