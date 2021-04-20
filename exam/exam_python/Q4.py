import numpy as np 

def min_dist(u1, u2, u3):
    u1 = np.array(u1)
    u2 = np.array(u2)
    u3 = np.array(u3)
    v = np.random.rand(len(u1))
    learned_v  = gradient_descent(u1, u2, u3, v, 0.1, 100)
    return learned_v 

def gradient_descent(u1, u2, u3, v, alpha, epochs):
    #for the number of iterations specified
    #adjust v by the gradient vector times some learning rate 
    curr_epoch = 0
    while curr_epoch < epochs:
        curr_epoch += 1
        v = v - alpha*gradient(u1, u2, u3, v)
    return v 

def gradient(u1, u2, u3, v):
    #this is vector of partial derivatives of the cost function with respect to v_i
    #numpy does this element wise and returns a vector in the shape of v which is desired  
    grad = 2*(v-u1) + 2*(v-u2) + 2*(v-u3)
    return grad 


def cost(u1, u2, u3, v):
    #use numpy elementwise subtraction and squaring then sum over every element 
    return np.sum(np.square((v-u1))) + np.sum(np.square((v-u2))) + np.sum(np.square((v-u3)))

if __name__ == "__main__":
    u1 = [0, 1]
    u2 = [0, 1]
    u3 = [0, 1]
    print(min_dist(u1, u2, u3)) #prints [1.48110893e-40, 1.000000000e+10] which is essentially [0, 1] which makes sense 

    u1 = [0, 0, 1]
    u2 = [0, 1, 0]
    u3 = [1, 0, 0]
    print(min_dist(u1, u2, u3)) #prints [0.333333, 0.3333333, 0.3333333]
