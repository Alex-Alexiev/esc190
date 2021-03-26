def fib(n, mem={}):
    if n in mem: return mem[n]
    mem[n] = fib(n-1, mem) + fib(n-2, mem)

def fib_iter(n):
    fib_list = [0]*n
    fib_list[0:2] = [0, 1]
    for i in range(2, n+1):
        fib_list[i] = fib_list[i-1] + fib_list[i-2]
    return fib_list[n-1]



