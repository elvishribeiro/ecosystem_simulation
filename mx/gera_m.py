import random
from tqdm import tqdm
import math 


L = [int(math.sqrt(300000)), int(math.sqrt(600000)), int(math.sqrt(1200000)), int(math.sqrt(2400000)), int(math.sqrt(4800000))]
G_P_C = random.randint(1, 5)
G_P_R = random.randint(1, 5)
G_C_R = random.randint(2, 8)

N_GEN = 30

for i in range(len(L)):
    x_pos = [i for i in range(L[i] - 1)]
    y_pos = [i for i in range(L[i] - 1)]
    random.shuffle(x_pos)
    random.shuffle(y_pos)

    N = random.randint(int(L[i] * L[i] * .35), int(L[i] * L[i] * .5))
    with open('m' + str(i) + '.txt', 'w') as f:
        f.write(str(G_P_C) + ' ' + str(G_P_R) + ' ' + str(G_C_R) + ' ' + str(N_GEN) + ' ' + str(L[i]) + ' ' + str(L[i]) + ' ' + str(N) + '\n')
        #f.write(str(G_P_C) + ' ' + str(G_P_R) + ' ' + str(G_C_R) + ' ' + str(N))
        for j in tqdm(range(N - 1), position=0):
            if j < L[i] - 1:
                x = x_pos[j]
                y = y_pos[j]
                b = ['ROCHA', 'RAPOSA', 'COELHO'][random.randint(0, 2)]
                f.write(str(b) + ' ' + str(x) + ' ' + str(y) + '\n')
        G_P_C += 1
        G_P_R += 1
        G_C_R += 1

