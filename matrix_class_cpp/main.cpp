#include <iostream>
#include <vector>
#include "matrix.h"

using namespace std;

void print();

int main(){

    // ######### TESTE
    // criando matriz usando o construtor de celualr de mesmo valor
    Matrix m(2, 4, 2.9);
    m.printMatrix();

    print();

    // ######### TESTE
    // criando matriz usando o construtor de grid pronto
    vector< vector<float> > _m1 (3, vector<float> (4));

    _m1[0][0] = 1; _m1[0][1] = 2; _m1[0][2] = 3; _m1[0][3] = 4;

    _m1[1][0] = 5.1; _m1[1][1] = 5.2; _m1[1][2] = 5.3; _m1[1][3] = 5.4;

    _m1[2][0] = 10; _m1[2][1] = 11.4;  _m1[2][2] = 12;_m1[2][3] = 15.8;

    Matrix m1 = Matrix(_m1);

    m1.printMatrix();

    // ######### TESTE
    // recuperando coluna da matriz
    m1.printVector(m1.getColumn(0));

    // ######### TESTE
    // dotProduct
    float dotP = m1.dotProduct('r', 1, vector<float> (4, 1)) ;
    // cout << "dotP: " << dotP;

    // ######### TESTE
    // multiplication
    vector< vector<float> > _m2 (3, vector<float>(3, -1));
    vector< vector<float> > _m3 (3, vector<float>(4, -2));

    Matrix m2(_m2);
    Matrix m3(_m3);

    Matrix mul = m2.multiplication(m3);

    mul.printMatrix();

    // ######### TESTE
    // add
    Matrix add = m2.add(m3);

    add.printMatrix();

    // ######### TESTE
    // determinant

    vector< vector<float> > _m4 (1, vector<float>(1, -2));
    Matrix m4 = Matrix(_m4);
    cout << m4.determinant() << "\n";

    vector< vector<float> > _m5 (2, vector<float>(2, -2));
    Matrix m5 = Matrix(_m5);
    cout << m5.determinant() << "\n";

    return 0;
}

void print(){
    cout << endl;
}