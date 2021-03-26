import numpy as np

energies = [[24,      22,      30,      15,      18,      19],
            [12,      23,      15,      23,      10,     15],
            [11,      13,      22,      13,      21,      14],
            [13,      15,      17,      28,      19,      21],
            [17,      17,      7,       27,      20,      19]]

width = len(energies[0])
height = len(energies)

min_energies = np.zeros((height, width))
min_energies[0] = energies[0]

for j in range(1, height):
    for i in range(0, width):
        left = i-1
        right = i+1
        top = i
        if(i == 0):
            left = i
        if(i == width - 1):
            right = i
        min_energies[j][i] = energies[j][i] + min(min_energies[j-1][left], min_energies[j-1][right], min_energies[j-1][top])
        
print(np.amin(min_energies[height - 1]))



