import numpy as np
import  matplotlib.pyplot as plt

def f(x):
    return .1*x**2 + np.sin(.1*(x-2)**2)

def dfdx(x):
    return .2*x+np.cos(.1*(x-2)**2)*(.2*(x-2))


def grad_descent(f, dfdx, init_x, alpha):
    EPS = 1e-5
    prev_x = init_x-2*EPS
    x = init_x

    while abs(x - prev_x) >  EPS:
        prev_x = x
        x -= alpha*dfdx(x)
        print(x, f(x))

    return x





x = np.arange(-10, 10, .1)
y = f(x)

plt.figure(1)
plt.plot(x, y)
plt.xlabel("x")
plt.ylabel("$.1 x^2 + sin(.1 (x-2)^2)$")
plt.show()

grad_descent(f, dfdx, 0, 0.01)