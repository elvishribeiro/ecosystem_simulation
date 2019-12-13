import random
from tqdm import tqdm
import math 

def gera_posicoes(a=[]):
    if a == []:
        return None
    tuplas = []
    k = len(a) - 1
    x = [-1 for _ in a]
    i = 0
    n = 0
    while i != -1:
        if x[i] != a[i]:
            x[i] += 1
            if i < k:
                i += 1
            else:
                tuplas += [(x[0], x[1])]
                n += 1
                pass
        else:
            x[i] = -1
            i -= 1
    return tuplas

#número de entradas da matriz
L = [
    int(math.sqrt(300000)), 
    int(math.sqrt(600000)), 
    int(math.sqrt(1200000)), 
    int(math.sqrt(2400000)), 
    int(math.sqrt(4800000))
    ]

#É SÓ ALTERAR O NÚMERO DE GERAÇÕES, OS OUTROS PARÂMETROS SÃO ESTIMADOS AUTOMATICAMENTE
#NÚMERO DE GERAÇÕES DEVE SER MAIOR OU IGUAL À 24 PRAS EQUAÇÕES FUNCIONAREM
N_GEN = 365

#estimação gerações
GEN_PROC_COELHO = int((1 / 12) * N_GEN)
GEN_PROC_RAPOSA = int((50 / (12 * 30)) * N_GEN)
GEN_COMIDA_RAPOSA = int((15 / (12 * 30)) * N_GEN)

#porcentagem de cada objeto no mapa
porc_coelhos = .5
porc_raposas = .3
porc_rochas = .2

for L_i in L:
    pos = gera_posicoes([L_i - 1, L_i - 1])
    random.shuffle(pos)

    N = int(((L_i - 1) ** 2) * .4)
    n_obj = [[int(N * porc_coelhos), 'COELHO'], [int(N * porc_raposas), 'RAPOSA'], [int(N * porc_rochas), 'ROCHA']]

    total = sum([o[0] for o in n_obj])
    if total < N:
        #aumenta o número de rochas
        n_obj[-1][0] += N - total
        total += N - total

    with open('m' + str(L_i - 1) + '.txt', 'w') as f:
        f.write(
            str(GEN_PROC_COELHO) + ' ' + 
            str(GEN_PROC_RAPOSA) + ' ' + 
            str(GEN_COMIDA_RAPOSA) + ' ' + 
            str(N_GEN) + ' ' + 
            str(L_i - 1) + ' ' + 
            str(L_i - 1) + ' ' + 
            str(total) + '\n'
            )

        k = 0
        for j in tqdm(range(total), position=0):
            x, y = pos[j]
            b = n_obj[k][1]
            f.write(str(b) + ' ' + str(x) + ' ' + str(y) + '\n')
            n_obj[k][0] -= 1
            if n_obj[k][0] == 0:
                k += 1
