#include <iostream>
#include <vector>

using namespace std;

void printMatrix(vector< vector<int> > m);

vector< vector<int> > sumMatrices(vector< vector<int> > m1, vector< vector<int> > m2);

int main(){
    
    vector< vector<int> > m1 (2, vector<int> (3));
    vector< vector<int> > m2 (2, vector<int> (3));
    
    m1[0][0] = 0;
    m1[0][1] = 1;
    m1[0][2] = 2;
    m1[1][0] = 3;
    m1[1][1] = 4;
    m1[1][2] = 5;
    
    m2[0][0] = 10;
    m2[0][1] = 11;
    m2[0][2] = 12;
    m2[1][0] = 13;
    m2[1][1] = 14;
    m2[1][2] = 15;
    
    printMatrix(m1);
    
    cout << endl;
    
    printMatrix(m2);
    
    cout << endl;
    
    printMatrix(sumMatrices(m1, m2));
    
    
    return 0;
}


vector< vector<int> > sumMatrices(vector< vector<int> > m1, vector< vector<int> > m2){
    
    int rows = m1.size();
    int columns = m1[0].size();
    
    vector< vector<int> > res (rows, vector<int> (columns));
    
    for (int i=0; i<rows; ++i){
        for( int j=0; j<columns; ++j){
            res[i][j] = m1[i][j] + m2[i][j];
        }
    }
    
    return res;
}



void printMatrix(vector< vector<int> > m){
    
    if (m.size() == 0) {
        cout << "empty matrice" << endl;
        
        return;
    }
    
    int rows = m.size();
    int columns = m[0].size();
 
    
    for (int i = 0; i < rows; ++i){
        for (int j = 0; j < columns; ++j){
            
            cout << m[i][j] << " ";
        }
        cout << endl;
    }
    
}
