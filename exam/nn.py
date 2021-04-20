import math 
import numpy as np 

x_train = np.array([[10, 15], [12, 8]])
y_train = np.array([0.8, 0.4])

W = np.random.rand(11)*2 - 1
b = np.random.rand(6)*2 - 1


def sigma(x):
    return 1/(1+math.exp(-x))

def net(x):
    h = np.zeros(6)
    h[1] = sigma(W[1]*x[0] + W[2]*x[1] + b[1])
    h[2] = sigma(W[3]*x[0] + W[4]*x[1] + b[2])
    
    h[3] = sigma(W[5]*h[1] + W[6]*h[3] + b[3])
    h[4] = sigma(W[7]*h[1] + W[8]*h[3] + b[4])

    y = sigma(W[9]*h[3] + W[8]*h[4] + b[5])
    
    return y, h

def cost(x, y_hat):
    return math.pow(net(x[0])[0]-y_hat[0], 2) + math.pow(net(x[1])[0]-y_hat[1], 2)

def dcdw1(x, y):
    return dcdw1_1(x[0], y[0]) + dcdw1_1(x[1], y[1])

def dcdw1_1(x, y):
    y_hat, h = net(x)
    dcdy = -2*(y - y_hat)
    dydh3 = y_hat*(1-y_hat)*W[9]
    dydh4 = y_hat*(1-y_hat)*W[10]
    dh3dh1 = h[3]*(1-h[3])*W[5]
    dh4dh1 = h[4]*(1-h[4])*W[6]
    dh1dw1 = h[1]*(1-h[1])*x[0]
    dh3dw1 = dh3dh1*dh1dw1
    dh4dw1 = dh4dh1*dh1dw1
    dydw1 = dydh3*dh3dw1 + dydh4*dh4dw1
    dcdw1 = dcdy*dydw1
    return dcdw1

def fin_dif_dcdw1(x, y, h):
    cost1 = cost(x, y)
    W[1] = W[1] + h
    cost2 = cost(x, y)
    W[1] = W[1] - h
    return (cost2- cost1)/h

print(dcdw1(x_train, y_train))
print(fin_dif_dcdw1(x_train, y_train, 0.0001))
    
    
    
