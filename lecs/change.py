# denom = [1, 4, 5, 10, 25, 100, 200]
# greedy doesn't work for 8

denom = [1, 5, 10, 25, 100, 200]

V = 150
OPT = [0] * (V + 1)
change = [0] * (V + 1)
for v in range(1, V+1):
    cur_min = 10000
    cur_min_denom  = -1
    for i in range(len(denom)):
        if denom[i] > v:
            continue
        if cur_min > 1 + OPT[v-denom[i]]:
            cur_min = 1 + OPT[v-denom[i]]
            cur_min_denom = i
    OPT[v] = cur_min
    change[v] = denom[cur_min_denom]


def make_change(amount, change):
    if amount == 0:
        return
    print(change[amount])
    make_change(amount - change[amount], change)