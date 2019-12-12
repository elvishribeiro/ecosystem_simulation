import random

L = random.randint(100, 1000)
L = 6
N = random.randint(int(L * L * .35), int(L * L * .5))
G_P_C = random.randint(0, 5)
G_P_R = random.randint(0, 5)
G_C_R = random.randint(2, 8) 

N_GEN = 30

for i in range(10):
    with open('n6/' + str(i) + '.txt', 'w') as f:
        f.write(str(G_P_C) + ' ' + str(G_P_R) + ' ' + str(G_C_R) + ' ' + str(N_GEN) + ' ' + str(L) + ' ' + str(L) + ' ' + str(N) + '\n')
        pos = []
        for _ in range(N - 1):
            while True:
                x = random.randint(0, L-1)
                y = random.randint(0, L-1)
                if (x, y) not in pos:
                    pos += [(x, y)]
                    break
            b = ['ROCHA', 'RAPOSA', 'COELHO'][random.randint(0, 2)]
            f.write(str(b) + ' ' + str(x) + ' ' + str(y) + '\n')
        G_P_C += 1
        G_P_R += 1
        G_C_R += 1