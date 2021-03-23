# Codigo para estimar a localizacao final dado que nao se sabe a posicao inicial do veiculo 
# e que as posicoes iniciais possiveis possuem uma distribuicao uniforme de probabilidades (0.2).
# o veiculo leu (sense) o ambiente e percebeu vermelho, em seguida andou (move) uma posicao para a direita
# em seguida leu novamente vermelho e, por fim, andou mais uma posicao para a direita
# Qual seria a distribuicao de probabilidades das possíveis posicoes ao final desse processo?

# Neste exemplo, cada movimento reduz a entropia do sistema, isto e, aumenta-se a incerteza da localizao.
# E cada nova leitura aumenta a entropia do sistema, isto e, diminui-se a incerteza da localizacao.

# SENSE <========> MOVE
# aumenta         diminui
# entropia       entropia 

# A pior incerteza possivel e a distribuicao uniforme de probabilidades porque todos os valores possiveis possuem probabilidades iguais.

# p eh o vetor (circular) inicial que representa cada posicao possivel no mapa. Apos cada nova medica ou novo movimento, suas probabilidades sao atualizadas 'in place'

p=[0.2, 0.2, 0.2, 0.2, 0.2]
world=['green', 'red', 'red', 'green', 'green']
measurements = ['red', 'red']
motions = [1,1]
pHit = 0.6
pMiss = 0.2
pExact = 0.8
pOvershoot = 0.1
pUndershoot = 0.1

def sense(p, Z):
    q=[]
    for i in range(len(p)):
        hit = (Z == world[i])
        q.append(p[i] * (hit * pHit + (1-hit) * pMiss))
    s = sum(q)
    for i in range(len(q)):
        q[i] = q[i] / s
    return q

def move(p, U):
    q = []
    for i in range(len(p)):
        s = pExact * p[(i-U) % len(p)]
        s = s + pOvershoot * p[(i-U-1) % len(p)]
        s = s + pUndershoot * p[(i-U+1) % len(p)]
        q.append(s)
    return q

for k in range(len(measurements)):
    p = sense(p, measurements[k])
    p = move(p, motions[k])
    
print p         
