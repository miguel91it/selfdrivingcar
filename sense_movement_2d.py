# Arquivo criado para implementar as funcoes de sense e move para localização de veiculo autonomo em mapa 2d (matriz)
# Função sense implementada por mim realiza a atualizacao das probabilidades de localizacao no mapa matricial (2D)
# apos realizar uma leitura de sensor.
# ela retorna uma nova amtriz 2D de tamanho igual contendo uma nova probabilidade de encontrar o veiculo em cada celula DADO QUE UMA LEITURA DE SENSOR FOI REALIZADA
# usado teorema de Bayes para realizar os calculos de probabilidades condicionais



from helpers import normalize, blur

def initialize_beliefs(grid):
    height = len(grid)
    width = len(grid[0])
    area = height * width
    belief_per_cell = 1.0 / area
    beliefs = []
    for i in range(height):
        row = []
        for j in range(width):
            row.append(belief_per_cell)
        beliefs.append(row)
    return beliefs

def sense(color, grid, beliefs, p_hit, p_miss):
    new_beliefs = []

    color_observed = color
        
    height = len(grid)
    width = len(grid[0])
    
    sum_p = 0
    
    for i in range(height):
        
        new_line_beliefs = []
        
        for j in range(width):
            
            # recupera a prob priori da celula na matriz de beliefs
            p_priori_cell = beliefs[i][j]
            
            # recupera a cor da celula no grid
            curr_color_cell = grid[i][j]
            
            # calcula a nova probabilidade da celula em funcao da cor observada pelo sensor e da cor real da celula
            p_after_measure = p_priori_cell * p_hit if color_observed == curr_color_cell else p_priori_cell * p_miss
            
            # adiciona a probabilidade atualizada na nova linha de p
            new_line_beliefs.append(p_after_measure)
            
            # acumula a soma de cada nova probabilidade calculada para depois realizar normalizacao de new_beliefs
            sum_p += p_after_measure
            
        new_beliefs.append(new_line_beliefs)
            
    # ate aqui, new_beliefs ainda nao esta normalizado, isto e, a soma de todas probabilidades nao soma 1 ainda
    for i in range(height):
        for j in range(width):
            new_beliefs[i][j] /= sum_p
    
    
    # print(new_beliefs)
            
    return new_beliefs

def move(dy, dx, beliefs, blurring):
    height = len(beliefs)
    width = len(beliefs[0])
    new_G = [[0.0 for i in range(width)] for j in range(height)]
    for i, row in enumerate(beliefs):
        for j, cell in enumerate(row):
            
            new_i = (i + dy ) % height
            new_j = (j + dx ) % width
            #print('dy: ', dy, ' | dx: ', dx, ' | i: ', i, ' | j: ', j, ' | new_i: ', new_i, ' | new_j: ', new_j, ' | width: ', width, ' | height: ', height)
            new_G[int(new_i)][int(new_j)] = cell
    return blur(new_G, blurring)
