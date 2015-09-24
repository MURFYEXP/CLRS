#include <iostream>
using namespace std;

template <typename T>
void multi(T** aMatrix, T **bMatrix, T **resultMatrix, int size)
{
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            resultMatrix[i][j] = 0;
            for (int k = 0; k < size; ++k){
                resultMatrix[i][j] += aMatrix[i][k] * bMatrix[k][j];
            }
        }
    }
}

int **matrix;
int **matrixR0;
int **matrixR1;
void FiboNum(int n)
{
    if (n < 1) {
        return;
    }
    int half = n / 2;
    FiboNum(half);
    multi(matrix, matrix, matrixR0, 2);
    //二维数组的复制memcmp
    //memcpy(matrix, matrixR0, sizeof(matrixR0));
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            matrix[i][j] = matrixR0[i][j];
        }
    }
    if (n % 2)
    {
        multi(matrix, matrixR1, matrixR0, 2);
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                matrix[i][j] = matrixR0[i][j];
            }
        }
        
    }
}

int main(void)
{
    int n;
    long result;
    cin >> n;
    matrixR1 = new int*[2];
    matrixR0 = new int*[2];
    matrix = new int*[2];
    for (int i = 0; i < 2; ++i) {
        matrix[i] = new int[2];
        matrixR0[i] = new int[2];
        matrixR1[i] = new int[2];
    }
    matrix[0][0] = 1;  matrix[0][1] = 0;
    matrix[1][0] = 0;  matrix[1][1] = 1;
    matrixR1[0][0] = 1;  matrixR1[0][1] = 1;
    matrixR1[1][0] = 1;  matrixR1[1][1] = 0;
    if (n == 0) {
        result = 0;
    }
    if (n == 1) {
        result = 1;
    }
    else{
        FiboNum(n);
        result = matrixR0[1][0];
    }
    cout << result << endl;
    for (int i = 0; i < 2; ++i) {
        delete [] matrix[i];
        delete [] matrixR0[i];
        delete [] matrixR1[i];
    }
    delete matrix;
    delete matrixR0;
    delete matrixR1;
}

