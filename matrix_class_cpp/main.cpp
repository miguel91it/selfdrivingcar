#include <iostream>
#include <vector>
#include "matrix.h"

using namespace std;

void print();

int main(){

    // ######### TESTE criando matriz usando o construtor de celulas de mesmo valor
    cout << "Test: Constuctor identical cells\n";
    Matrix m(2, 4, 2.9);
    m.printMatrix();

    print();

    // ######### TESTE criando matriz usando o construtor de grid pronto
    cout << "Test: Construtor take in grid\n";
    vector< vector<float> > _m1 (3, vector<float> (4));

    _m1[0][0] = 1; _m1[0][1] = 2; _m1[0][2] = 3; _m1[0][3] = 4;

    _m1[1][0] = 5.1; _m1[1][1] = 5.2; _m1[1][2] = 5.3; _m1[1][3] = 5.4;

    _m1[2][0] = 10; _m1[2][1] = 11.4;  _m1[2][2] = 12;_m1[2][3] = 15.8;

    Matrix m1 = Matrix(_m1);

    m1.printMatrix();

    // ######### TESTE recuperando grid da matriz
    cout << "TEST Get Grid from Matrix\n";
    cout << "Matrix created with size 3x4\n";
    vector<float>::size_type rows, cols;
    rows = m1.getGrid().size();
    cols = m1.getGrid()[0].size();

    cout << "Returned grid with " << rows << " rows and " << cols << " cols\n\n";

    // ######### TESTE setando novo grid
    cout << "TEST Set Matrix Grid from new Grid\n";
    Matrix sg = Matrix(5, 5, -1);
    sg.printMatrix();


    // ######### TESTE recuperando coluna da matriz
    cout << "TEST Get Matrix Column\n";
    m1.printVector(m1.getColumn(0));

    // ######### TESTE produto escalar
    cout << "TEST Dot Product\n";
    int matrix_index = 1, vector_size = 4;
    cout << "Size of the Matrix vector: " << m1.getGrid()[1].size() << " | size of the vector passed in: " << vector_size << "\n";
    float dotP = m1.dotProduct('r', matrix_index, vector<float> (vector_size, 1)) ;
    cout << "Dot Product: " << dotP << "\n\n";

    // ######### TESTE multiplicação
    cout << "TEST Matrices Multiplication\n";

    Matrix m2 = Matrix(vector< vector<float> > (3, vector<float>(3, -1)));
    Matrix m3 = Matrix(vector< vector<float> > (3, vector<float>(4, -2)));

    Matrix mul = m2.multiplication(m3);

    mul.printMatrix();

    // ######### TESTE adição
    cout << "TEST Matrices Addition\n";
    Matrix add = m2.add(m2);

    add.printMatrix();

    // ######### TESTE Determinante da matriz (1x1 ou 2x2)
    cout << "TEST Matrices Determinants (1x1 and 2x2)\n";

    Matrix m4 = Matrix(vector< vector<float> > (1, vector<float>(1, -2)));
    cout << m4.determinant() << "\n";

    Matrix m5 = Matrix(vector< vector<float> > (2, vector<float>(2, -2)));
    cout << m5.determinant() << "\n";

    // Matrix m6 = Matrix(vector< vector<float> > (3, vector<float>(3, -2)));
    // cout << m6.determinant() << "\n";

    // ######### TESTE Matriz Transposta
    cout << "TEST Matrix transpose\n";
    Matrix m1_T = m1.transpose();
    cout << "Before Tranpose:\n";
    m1.printMatrix();
    cout << "After Tranpose:\n";
    m1_T.printMatrix();

    return 0;
}

void print(){
    cout << endl;
}