#include <iostream>
#include <vector>
#include "matrix.h"

using namespace std;

Matrix::Matrix(int rows, int columns, float value) {

    grid = vector< vector<float> > (rows, vector<float> (columns, value));
}

Matrix::Matrix(vector< vector<float> > grid_in){

    grid = grid_in;

}

vector< std::vector<float> > Matrix::getGrid(){

    return grid;
}

vector< float > Matrix::getColumn(int column){

    vector< float > columnVector;

    // TODO:
    // descobrir depois como lançar uma exceção ou retornar um erro em caso do
    // parametro column estar fora dos limites

    for(int i = 0; i < grid.size(); ++i)
        
        columnVector.push_back( grid[i][column] );

    return columnVector;
}

int Matrix::dotProduct(char axis, int indexGrid, vector< float > otherVector){

    float sum = 0;

    vector< float > vGrid;

    // recupera a linha ou coluna do grid do objeto, de acordo com o parametro passado
    if (axis == 'c') {
        vGrid = getColumn(indexGrid);
    } 
    else {
        vGrid = grid[indexGrid];
    }

    // TODO:
    // descobrir depois como lançar uma exceção ou retornar um erro em caso do
    // vGrid[indexGrid].size() diferente de otherVector.size()

    for(int i = 0; i < vGrid.size(); ++i)
        sum += vGrid[i] * otherVector[i];

    return sum;
}

Matrix Matrix::multiplication(Matrix otherMatrix){

    // TODO:
    // descobrir depois como lançar uma exceção ou retornar um erro em caso do
    // numero de coluna de grid ser diferente do numero de linhas de OtherGrid

    vector< vector<float> > gridRes;
    vector<float> vectorRes;

    for (int i = 0; i < grid.size(); ++i){

        for (int j = 0; j < grid[0].size(); ++j){

            vectorRes.push_back( dotProduct('r', i, otherMatrix.getColumn(j)) );
        }

        gridRes.push_back( vectorRes );
    }

    return Matrix(gridRes);

}

Matrix Matrix::add(Matrix otherMatrix){

    vector< vector<float> >  otherGrid = otherMatrix.getGrid();
    vector< vector<float> > gridRes;
    vector<float> vectorRes;

    for(int i = 0; i < grid.size(); ++i){
        for(int j = 0; j < grid[0].size(); ++j){

            vectorRes.push_back( grid[i][j] + otherGrid[i][j] );
        }
        gridRes.push_back(vectorRes);
    }

    return Matrix(gridRes);
}

int Matrix::determinant(){

    int rows = grid.size();
    int cols = grid[0].size();

    if (rows == cols && rows == 1)
        return grid[0][0];

    else if (rows == cols && rows == 2){

        return grid[0][0] * grid[1][1] - grid[0][1] * grid[1][0];
    }

    else
        return -10000;
}

void Matrix::printMatrix(){

    for (int i=0; i < grid.size(); ++i){
        for (int j=0; j < grid[0].size(); ++j){
            cout << grid[i][j] << " ";
        }
        cout << "\n";
    }

    cout << "\n";
}

void Matrix::printVector(vector< float > v){

    for (int i=0; i < v.size(); ++i){
            cout << v[i] << " ";
    }

    cout << "\n";

}