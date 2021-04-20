import sys 
import numpy as np 


def LCS(s1, s2):
    arr = []
    curr_len = 0
    arr.append([(0, 0)])
    for i in range(1, min(len(s1), len(s2)) + 1):
        arr.append([])
        for pair in arr[i-1]:
            start_1 = pair[0]
            start_2 = pair[1]
            for s1_check in range(start_1 + 1, len(s1)):
                searching = s1[s1_check]
                for s2_check in range(start_2 + 1, len(s2)):
                    if searching == s2[s2_check]:
                        arr[i].append((s1_check, s2_check))
    print(arr)

def LCSlength(s1, s2):
    if len(s1) == 0 or len(s2) == 0:
        return 0
    if s1[-1] == s2[-1]:
        return 1 + LCSlength(s1[:-1], s2[:-1])
    else:
        return max(LCSlength(s1, s2[:-1]), LCSlength(s1[:-1], s2))

def SCSlength(s1, s2):
    if len(s1) == 0:
        return len(s2)
    if len(s2) == 0:
        return len(s1)
    if s1[-1] == s2[-1]:
        return 1 + SCSlength(s1[:-1], s2[:-1])
    else:
        return min(SCSlength(s1, s2[:-1]) + 1, SCSlength(s1[:-1], s2) + 1)

def LIS(A, i, n , prev):
    if i == n: return 0 
    excl = LIS(A, i+1, n, prev)
    incl = 0 
    if (A[i] > prev):
        incl = 1 + LIS(A, i+1, n, A[i])
    
    return max(incl, excl)
    
def LD(s1, s2, i1, i2, n1, n2):
    if i1 == n1 or i2 == n2:
        return max(n1-i1, n2-i2)
    if s1[i1] == s2[i2]:
        return LD(s1, s2, i1+1, i2+1, n1, n2)
    return 1 + min(LD(s1, s2, i1, i2+1, n1, n2), LD(s1, s2, i1+1, i2, n1, n2), LD(s1, s2, i1+1, i2+1, n1, n2))
    
 
def MCOP(dims, i, j, lookup):
    if i >= j - 1:
        lookup[i][j] = 0
        return 0
    if lookup[i][j] != 0:
        return lookup[i][j]
    poss = []
    for k in range(i+1, j):
        poss.append(MCOP(dims, i, k, lookup) + MCOP(dims, k, j, lookup) + dims[i]*dims[k]*dims[j])
    lookup[i][j] = min(poss)
    return lookup[i][j]

def MCOPn(dims):
    n = len(dims)
    c = np.zeros((n, n))

    for length in range(2, n):
        for i in range(0, n - length):
            j = i + length
            k = i + 1
            c[i][j] = sys.maxsize
            while k < j:
                cost = c[i][k] + c[k][j] + dims[i]*dims[k]*dims[j]
                c[i][j] = min(cost, c[i][j])
                k += 1

    return c[0][n-1]


def NS(values, weights, W):
    n = len(values)
    maxVal = np.zeros((n, W+1))
    for i in range(n):
        for w in range(W+1):
            if w - weights[i] >= 0:
                maxVal[i][w] = max(maxVal[i-1][w-weights[i]] + values[i], maxVal[i-1][w])
            else:
                maxVal[i][w] = maxVal[i-1][w]
    return maxVal[n-1][W]

def subsetSum(A, n, sum):
    if n == 0:
        return A[0] == sum

    if subsetSum(A, n-1, sum-A[n]) or subsetSum(A, n-1, sum):
        return True 
    
    return False 
    
def partition(A):
    total = sum(A)
    if total%2 == 0 and subsetSum(A, len(A)-1, total/2):
        return True 
    return False 

def partition_n(A):
    total = sum(A)
    if total%2 == 1: return False 
    pos = np.zeros((len(A), total//2+1))
    for i in range(len(A)):
        for s in range(0, total//2 + 1):
            if s - A[i] == 0:
                pos[i][s] = 1
            elif s - A[i] > 0:
                pos[i][s] = pos[i-1][s-A[i]] or pos[i-1][s]
            else:
                pos[i][s] = pos[i-1][s]

    return pos[len(A)-1][total//2] == 1

def rods(values, L):
    if L == 0: return 0 
    max_val = values[L-1]
    for i in range(1, L):
        max_val = max(max_val, rods(values, i) + rods(values, L-i))

    return max_val

def rods_n(values, L):
    max_val = np.zeros(L+1)
    for i in range(1, L+1): #current length
        for v in range(1, i+1): 
            max_val[i] = max(max_val[i], values[v-1] + max_val[i-v])
    return max_val[L]

# def wordBreak(dict, str, out=""):
#     if not str: 
#         print(out)
#         return 
#     for i in range(len(str)):
#         if str[:i+1] in dict: 
#             wordBreak(dict, str[i+1:], out + str[:i+1] + " ")
    
def wordBreak(dict, str, lookup):
    if not str: 
        return True 

    if lookup[len(str)] == 1:
        return True 

    for i in range(len(str)):
        if str[:i+1] in dict and wordBreak(dict, str[i+1:], lookup):
            lookup[len(str)] = True 
            
    return lookup[len(str)]

class Solution:
    def diffWaysToCompute(self, expression: str) -> List[int]:
        if len(expression) < 2: 
            return [int(expression)]
        m = {}
        op = {
            "*": lambda x, y: x*y, 
            "+": lambda x, y: x+y,
            "-": lambda x, y: x-y
        }
        
        def divideandconquer(s):
            if s in m: 
                return m[s]
            left, right, res = [], [], []
            for i in range(len(s)):
                if s[i] in op:
                    s1 = s[:i]
                    s2 = s[i+1:]
                    left = divideandconquer(s1)
                    right = divideandconquer(s2)
                    for l in m[s1]:
                        for r in m[s2]:
                            res.append(op[s[i]](l, r))
            if not res:
                res.append(int(s))
            m[s] = res
            return res 
        
        ans = divideandconquer(expression)
        return ans 

if __name__ == '__main__':
 
    # List of strings to represent a dictionary
    dict = [
        "self", "th", "is", "famous", "Word",
        "break", "b", "r", "e", "a", "k", "br",
        "bre", "brea", "ak", "problem"
    ]
 
    str = "Wordbreakproblem"
 
    if wordBreak(dict, str, np.zeros(len(str)+1)):
        print("The string can be segmented")
    else:
        print("The string can't be segmented")