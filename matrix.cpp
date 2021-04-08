#include <iostream>
#include <vector>
#include <stdio.h> /* exit, EXIT_FAILURE */

using namespace std;

vector< vector<float> > matrixMultiplication(vector< vector<float> > m1, vector< vector<float> > m2);
float vectorsDotProduct( vector<float> v1, vector<float> v2);
vector<float> getMatrixColumn(vector< vector<float> > m, int column);
void printVector(vector<float> v);
void printMatrix(vector< vector<float> > m);

int main(){

    vector< vector<float> > m1 (2, vector< float > (2, 1.5));
    vector< vector<float> > m2 (3, vector< float > (2, 3.2));
    
    vector< vector<float> > mRes (3, vector< float > (2));

    mRes = matrixMultiplication(m2, m1);

    printMatrix(m2);
    printMatrix(m1);

    printMatrix(mRes);

    return 0;
}

vector< vector<float> > matrixMultiplication(vector< vector<float> > m1, vector< vector<float> > m2){

    int rowsM1 = m1.size();
    int columnsM1 = m1[0].size();

    int rowsM2 = m2.size();
    int columnsM2 = m2[0].size();

    vector< vector<float> > matrixres;
    vector<float> vectorres;
    float dotProduct;

    vector<float> rowM1;
    vector<float> columnM2asRow;

    cout << rowsM1 << ", " << columnsM2 << endl;

    // verificando se matrizes 1 e 2 podem se rmultiplicadas
    // apenas se o numero de colunas da matriz 1 for igual ao numero de linhas da matriz 2
    if (columnsM1 != rowsM2){
        cout << "As matrizes não podem ser multiplicadas. O numero de colunas da primeira matriz não é igual ao de linhas da segunda matriz: ";
        cout << "M1 (" << rowsM1 << "x" << columnsM1 << ") | ";
        cout << "M2 (" << rowsM2 << "x" << columnsM2 << ")" << endl;
    
        exit(EXIT_FAILURE);
    }

    // perocrre as linhas da matriz 1 e as colunas da matriz 2
    // realiza os produtos escalares e insere os resultados na nova matriz
    for(int i = 0; i < rowsM1; ++i) {

        // recupera a linha i da matriz 1
        rowM1 = m1[i];

        for(int j = 0; j < columnsM2; ++j){

            // recupera a coluna j da matriz 2
            columnM2asRow = getMatrixColumn(m2, j);

            // realiza o produto escalar entre a linha e a coluna
            dotProduct = vectorsDotProduct(rowM1, columnM2asRow);

            // insere o resultado no novo vetor linha da matriz resultado
            vectorres.push_back(dotProduct);
        }

        // após acabar de preencher a nova linha de resultado da matriz, adiciona essa linha na matriz resultado
        matrixres.push_back(vectorres);
    }
    
    return matrixres;
}

float vectorsDotProduct( vector<float> v1, vector<float> v2) {

    float dotProduct = 0;

    for (int i=0; i < v1.size(); ++i)
        dotProduct += v1[i] * v2[i];
    
    return dotProduct;
}

vector<float> getMatrixColumn(vector< vector<float> > m, int column){

    vector<float> columnAsVector;

    int rows = m.size();

    // para a dada coluna, percorre as linhas
    // e transforma a coluna em um vetor e o retorna
    for(int i = 0; i < rows; ++i){

        columnAsVector.push_back( m[i][column] );

    }

    return columnAsVector;
}

void printVector(vector<float> v){

    cout << "[ ";

    for (int i=0; i < v.size(); ++i)
        cout << v[i] << " ";

    cout << "]" << endl;

}

void printMatrix(vector< vector<float> > m){

    int rows = m.size();
    int columns = m[0].size();

    cout << "[" << endl;

    for(int i = 0; i < rows; ++i){
        for(int j = 0; j < columns; ++j){

            cout << m[i][j] << " ";
        }

        cout << endl;
    }

    cout << "]" << endl;

}