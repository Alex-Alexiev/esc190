def construct_D_arr(L1, L2):
    D = [[0 for x in range(len(L2)+1)] for x in range(len(L1)+1)]
    for i in range(len(L1)+1):
        D[i][0] = i
    for j in range(len(L2)+1):
        D[0][j] = j
    for i in range(1, len(L1)+1):
        for j in range(1, len(L2)+1):
            if L1[i-1] == L2[j-1]:
                #if the last element is the same, then no operation is needed
                D[i][j] = D[i-1][j-1]
            else:
                #otherwise determine the minimum of replacing, removing, or inserting 
                D[i][j] = min(D[i-1][j-1], D[i-1][j], D[i][j-1]) + 1
    return D 

def min_dist(L1, L2):
    D = construct_D_arr(L1, L2)
    return D[len(L1)][len(L2)]

def recover_path(L1, L2):
    return [[1, 2], [1, 3]]


if __name__ == "__main__":
    L1 = [1, 1, 2, 3]
    L2 = [2, 2, 3]
    #print(construct_D_arr(L1, L2))
    print(min_dist(L1, L2))

    