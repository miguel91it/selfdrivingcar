#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

vector<float> sense(vector<float> p, string z);

vector<float> move(vector<float> p, int u);

int calcVectorIndex(int indexBefore, int vectorSize);

void printVector(vector<float> v);

// variáveis globais
vector<string> world = {"green", "red", "red", "green", "green"};
float pHit = 0.6;
float pMiss = 0.2;

float pExact = 0.8;
float pOvershoot = 0.1;
float pUndershoot = 0.1;

int main(){

    cout << "Iniciando auto localização" << endl;

    vector<float> p (5, 0.2);

    vector<string> measurements = {"red", "green"};

    vector<int> motions = {1, 1};

    printVector(p);

    for (int i=0; i < measurements.size(); ++i){
        p = sense(p, measurements[i]);
        printVector(p);
        p = move(p, motions[i]);
        printVector(p);
    }

    return 0;
}

vector<float> sense(vector<float> p, string z){

    // declarando um vetor q de tamanho igual ao tamanho de p
    vector<float> q;

    int hit;
    float posterior_p;
    float sum_posterior_p = 0;

    // varrer o vetor passado 'p' e o vetor global 'world'
    // para calcular as novas probabilidades de localização não normalizadas
    for (int i=0; i < p.size(); ++i){

        // hit = 1 se a medição z é igual à posição world[i]
        if (z == world[i])
            hit = 1;
        else
            hit = 0;

        // insere no vetor q a nova probabilidade de localição 
        // prob. prior (p[i]) * prob nova medida
        posterior_p = p[i] * (hit * pHit + (1 - hit) * pMiss); 
        
        q.push_back( posterior_p );

        sum_posterior_p += posterior_p;
        
    }

    // agora vamos normalizar o vetor de distribuição de probabilidades
    // dividir todas cada probabilidade pela soma de todas elas
    for (int i=0; i < q.size(); ++i)
        q[i] = q[i] / sum_posterior_p;

    return q;
}

// calcula a probabilidade de estar em uma posição futura, a partir do estado atual das distribuições de probabilidades de p
// ha 3 movimentos possiveis: andar exatamente a quantidade de posições passadas, andar a quantidade + 1 (over) ou a quantidade -1 (under)
// essas possibilidades são traduzidas em probabilidades e levadas em consideração ao mesmo tempo
vector<float> move(vector<float> p, int u){

    vector<float> q;

    float s;

    // observação IMPORTANTE:
    // pego o size do vetor aqui porque o operador % não funciona corretamente quando o divisor é a função vector.size()
    // por algum motivo ainda nao compreendido ele retorna valores incorretos quando o dividendo é negativo
    int sizeVector = p.size();

    for (int i=0; i < p.size(); ++i){

        s = pExact * p[calcVectorIndex((i - u) % sizeVector, sizeVector)];
        

        s += pOvershoot * p[calcVectorIndex((i - u - 1) % sizeVector, sizeVector)];

        s += pUndershoot * p[calcVectorIndex((i - u + 1) % sizeVector, sizeVector)];

        q.push_back(s);
    }

    return q;
}

int calcVectorIndex(int indexBefore, int vectorSize) {

    // cout << "bef: " << indexBefore << " size: " << vectorSize << endl;

    int indexAfter = indexBefore;

    // se o index passado é negativo, então soma ele com o size do vetor para retornar o indice de traz pra frente
    if (indexBefore < 0)
        indexAfter = vectorSize + indexBefore;

    return indexAfter;
}

void printVector(vector<float> v){

    cout << "[ ";

    for( int i = 0; i < v.size(); ++i)
        cout << v[i] << " ";

    cout << "]" << endl;
}

