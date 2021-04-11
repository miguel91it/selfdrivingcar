#include <iostream>
#include <vector>
#include "matrix.h"

using namespace std;

// contrutor
Matrix::Matrix(int rows, int columns, float value) {

    grid = vector< vector<float> > (rows, vector<float> (columns, value));
    rows = rows;
    columns = columns;
}

// contrutor
Matrix::Matrix(vector< vector<float> > grid_in){

    grid = grid_in;
    rows = grid_in.size();
    columns = grid_in[0].size();
}

// Get Grid
vector< std::vector<float> > Matrix::getGrid(){

    return grid;
}

// Set Grid
void Matrix::setGrid( vector< vector<float> > grid_in){

    grid = grid_in;
    rows = grid_in.size();
    columns = grid_in[0].size();
}

// Get Rows
vector<float>::size_type Matrix::getRows(){
    return rows;
}

// Get Cols
vector<float>::size_type Matrix::getCols(){
    return columns;
}

// Get Matrix Column
vector< float > Matrix::getColumn(int column){

    vector< float > columnVector;

    if (column < 0 || column > grid.size()){
        throw std::invalid_argument("Column passed is out of bound of the grid");
    }

    for(int i = 0; i < grid.size(); ++i)
        
        columnVector.push_back( grid[i][column] );

    return columnVector;
}

// Dot Product of a vector
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

    if (vGrid.size() != otherVector.size()){
        throw std::invalid_argument("Vector passed to Dot Product must have the same length the vector from Matrix");
    }

    for(int i = 0; i < vGrid.size(); ++i)
        sum += vGrid[i] * otherVector[i];

    return sum;
}

// Matrix Multiplication
Matrix Matrix::multiplication(Matrix otherMatrix){

    if (columns != otherMatrix.getRows() ){
        throw std::invalid_argument("Number of columns of the current matrix must be tha same as the number of rows of the passed in matrix to multiply.");
    }

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

// Matrix addition
Matrix Matrix::add(Matrix otherMatrix){

    vector< vector<float> >  otherGrid = otherMatrix.getGrid();

    if (rows != otherGrid.size() || columns != otherGrid[0].size()){
        throw invalid_argument("In Matrices addition, both matrices must have the same number of rows and columns");
    }

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

// Determinant
int Matrix::determinant(){

    int rows = grid.size();
    int cols = grid[0].size();

    if (rows == cols && rows == 1)
        return grid[0][0];

    else if (rows == cols && rows == 2){

        return grid[0][0] * grid[1][1] - grid[0][1] * grid[1][0];
    }

    else
        throw invalid_argument("For now, it's possible calculate determinants of matrices with size 1x1 or 2x2");
}

// Transpose
Matrix Matrix::transpose(){

    vector< vector<float> > grid_res;
    vector< float > column_transpose;

    for (int j = 0; j < getCols(); ++j){

        for (int i = 0; i < getRows(); ++i){

            column_transpose.push_back(grid[i][j]);
        }

        grid_res.push_back(column_transpose);
        column_transpose.clear();
    }

    return Matrix(grid_res);
}

// Print Matrix
void Matrix::printMatrix(){

    for (int i=0; i < grid.size(); ++i){
        for (int j=0; j < grid[0].size(); ++j){
            cout << grid[i][j] << " ";
        }
        cout << "\n";
    }

    cout << "\n";
}

// Print Vector
void Matrix::printVector(vector< float > v){

    for (int i=0; i < v.size(); ++i){
            cout << v[i] << " ";
    }

    cout << "\n\n";

}