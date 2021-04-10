#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

class Matrix
{
    private:

        // linhas e colunas
        int rows, columns;

        // a propria matrix (grid)
        std::vector< std::vector<float> > grid;
        

    public:

        // construtor default da Matrix -> parece nao fazer sentido ainda
        // Matrix();

        // construtor da Matrix passando linhas e colunas e um mesmo valor para todas celulas
        Matrix( int rows, int columns, float value );

        // construtor da MatriX passando grid pronto
        Matrix(std::vector< std::vector<float> > grid_in);

        std::vector< std::vector<float> > getGrid();

        // recupera uma coluna
        std::vector< float > getColumn(int column);

        // calcula produto escalar
        int dotProduct(char axis, int indexGrid, std::vector< float > otherVector);

        // multiplicação matrizes
        Matrix multiplication(Matrix otherGrid);

        // adição matrizes
        Matrix add(Matrix otherGrid);

        // calcula determinante
        int determinant();

        // Print Matrix
        void printMatrix();

        void printVector(std::vector< float >);
};

#endif /* MATRIX_H */