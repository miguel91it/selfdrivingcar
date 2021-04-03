"""
  Class created to deal with matrices and its math operations.
  
  Created by me, João Miguel during the Udacity Nanodegree 'Introduction to self driving cars'.
  
  
"""

import math
from math import sqrt
import numbers

def zeroes(height, width):
        """
        Creates a matrix of zeroes.
        """
        g = [[0.0 for _ in range(width)] for __ in range(height)]
        return Matrix(g)

def identity(n):
        """
        Creates a n x n identity matrix.
        """
        I = zeroes(n, n)
        for i in range(n):
            I.g[i][i] = 1.0
        return I

def dot_product(vectorA, vectorB):
    
    if len(vectorA) != len(vectorB):
        raise(NotImplementedError, 'the vector must have the same length')
        return
#     print(vectorA, vectorB)
#     print([vectorA[i] * vectorB[i] for i in range(len(vectorA))])
    return sum( [vectorA[i] * vectorB[i] for i in range(len(vectorA))] )
    
class Matrix(object):

    # Constructor
    def __init__(self, grid):
        self.g = grid
        self.h = len(grid)
        self.w = len(grid[0])

    #
    # Primary matrix math methods
    #############################
 
    def determinant(self):
        """
        Calculates the determinant of a 1x1 or 2x2 matrix.
        """
        if not self.is_square():
            raise(ValueError, "Cannot calculate determinant of non-square matrix.")
        if self.h > 2:
            raise(NotImplementedError, "Calculating determinant not implemented for matrices largerer than 2x2.")
        
        if self.h == 1:
            return self.g[0][0]
        
        if self.h == 2:
            return self.g[0][0] * self.g[1][1] - self.g[0][1] * self.g[1][0]

    def trace(self):
        """
        Calculates the trace of a matrix (sum of diagonal entries).
        """
        if not self.is_square():
            raise(ValueError, "Cannot calculate the trace of a non-square matrix.")

        trace = 0
        
        for i in range(self.h):
            for j in range(self.w):
                if i == j:
                    trace += self.g[i][j]
        return trace
    
    def inverse(self):
        """
        Calculates the inverse of a 1x1 or 2x2 Matrix.
        """
        if not self.is_square():
            raise(ValueError, "Non-square Matrix does not have an inverse.")
        if self.h > 2:
            raise(NotImplementedError, "inversion not implemented for matrices larger than 2x2.")

        if self.h == 1:
            return Matrix([[1/self.g[0][0]]])

        elif self.h == 2:
            det = self.determinant()
            
            a = self.g[0][0]
            b = self.g[0][1]
            c = self.g[1][0]
            d = self.g[1][1]
            
            return Matrix([ [d/det, -b/det], [-c/det, a/det] ])
        
    def T(self):
        """
        Returns a transposed copy of this Matrix.
        """
        transposed = []
        
        for j in range(self.w):
            
            transposed_col = []
            
            for i in range(self.h):
                
                transposed_col.append(self.g[i][j])
                
            transposed.append(transposed_col)
        
        return Matrix(transposed)

    def is_square(self):
        return self.h == self.w

    #
    # Begin Operator Overloading
    ############################
    def __getitem__(self,idx):
        """
        Defines the behavior of using square brackets [] on instances
        of this class.

        Example:

        > my_matrix = Matrix([ [1, 2], [3, 4] ])
        > my_matrix[0]
          [1, 2]

        > my_matrix[0][0]
          1
        """
        return self.g[idx]

    def __repr__(self):
        """
        Defines the behavior of calling print on an instance of this class.
        """
        s = ""
        for row in self.g:
            s += " ".join(["{} ".format(x) for x in row])
            s += "\n"
        return s

    def __add__(self,other):
        """
        Defines the behavior of the + operator
        """
        if self.h != other.h or self.w != other.w:
            raise(ValueError, "Matrices can only be added if the dimensions are the same") 
        
        new_grid = []
        
        for i in range(self.h):
            
            new_row = []
            
            for j in range(self.w):
                
                new_row.append(self.g[i][j] + other.g[i][j])
            
            new_grid.append(new_row)
            
        return Matrix(new_grid) 

    def __neg__(self):
        """
        Defines the behavior of - operator (NOT subtraction)

        Example:

        > my_matrix = Matrix([ [1, 2], [3, 4] ])
        > negative  = -my_matrix
        > print(negative)
          -1.0  -2.0
          -3.0  -4.0
        """
        return Matrix([[-cell for cell in row] for row in self.g])

    def __sub__(self, other):
        """
        Defines the behavior of - operator (as subtraction)
        """
        if self.h != other.h or self.w != other.w:
            raise(ValueError, "Matrices can only be added if the dimensions are the same") 
        
        new_grid = []
        
        for i in range(self.h):
            
            new_row = []
            
            for j in range(self.w):
                
                new_row.append(self.g[i][j] - other.g[i][j])
            
            new_grid.append(new_row)
            
        return Matrix(new_grid) 

    def __mul__(self, other):
        """
        Defines the behavior of * operator (matrix multiplication)
        """
        if self.w != other.h:
            raise(ValueError, "Matrices can only be multiplied if the cols of the first matrice is the same that the row of the second") 
        
        other_T = other.T()
        
        new_grid = []
        
        for i in range(self.h):
            
            new_row = []
            
            for j in range(other.w):
                
                new_row.append( dot_product(self.g[i], other_T.g[j]) )
            
            new_grid.append(new_row)
            
        return Matrix(new_grid) 

    def __rmul__(self, other):
        """
        Called when the thing on the left of the * is not a matrix.

        Example:

        > identity = Matrix([ [1,0], [0,1] ])
        > doubled  = 2 * identity
        > print(doubled)
          2.0  0.0
          0.0  2.0
        """
        if isinstance(other, numbers.Number):
            
                return Matrix( [[other * cell for cell in row]for row in self.g] )
            
