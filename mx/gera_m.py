L = 30000
N = random.randint(int(L * L * .35), int(L * L * .5))
G_P_C = random.randint(1, 5)
G_P_R = random.randint(1, 5)
G_C_R = random.randint(2, 8)

N_GEN = 30

x_pos = [i for i in range(L - 1)]
y_pos = [i for i in range(L - 1)]
random.shuffle(x_pos)
random.shuffle(y_pos)

for i in range(1):
    with open('m' + str(i) + '.txt', 'w') as f:
        f.write(str(G_P_C) + ' ' + str(G_P_R) + ' ' + str(G_C_R) + ' ' + str(N))
        for j in tqdm(range(N - 1), position=0):
            if j < L - 1:
                x = x_pos[j]
                y = y_pos[j]
                b = ['ROCHA', 'RAPOSA', 'COELHO'][random.randint(0, 2)]
                f.write(str(b) + ' ' + str(x) + ' ' + str(y) + '\n')
        G_P_C += 1
        G_P_R += 1
        G_C_R += 1

