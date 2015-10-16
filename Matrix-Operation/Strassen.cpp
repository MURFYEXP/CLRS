//
//  main.cpp
//  CLRS
//
//  Created by mac on 9/14/15.
//  Copyright (c) 2015 mac. All rights reserved.
//

//
//  main.cpp
//  CLRS
//
//  Created by mac on 9/14/15.
//  Copyright (c) 2015 mac. All rights reserved.
//

#include <iostream>
#define N 100
int n;
int **matrixA;  int **matrixB;
int **matrix_a; int **matrix_b;
int **matrix_c; int **matrix_d;
int **matrix_e; int **matrix_f;
int **matrix_g; int **matrix_h;
using namespace std;

//二维数组的内存分配, 释放
http://www.cnblogs.com/bigshow/archive/2009/01/03/1367661.html
void test(int **a)
{
    //两维都未知
    int **b;
    b = new int *[100]; //分配指针数组
    for (int i = 0; i < 100; ++i) {
        b[i] = new int[100]; //分配每个指针所指向的数组
    }
    for (int i = 0; i < 100; ++i) {
        delete [] b[i];
    }
    delete b;
}

//template类型设计 二维数组用指针传参时，先分配内存
template <typename T>
void add(T** aMatrix, T **bMatrix, T **resultMatrix, int size)
{
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j){
            resultMatrix[i][j] = aMatrix[i][j] + bMatrix[i][j];
        }
    }
}

template <typename T>
void sub(T** aMatrix, T **bMatrix, T **resultMatrix, int size)
{
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j){
            resultMatrix[i][j] = aMatrix[i][j] - bMatrix[i][j];
        }
    }
}

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

void splitMatrix(int n0)
{
    int n = n0 / 2;  //结构相同则考虑组合重构
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j) {
            matrix_a[i][j] = matrixA[i][j];
            matrix_b[i][j] = matrixA[i + n][j];
            matrix_c[i][j] = matrixA[i][j + n];
            matrix_d[i][j] = matrixA[i + n][j + n];
            matrix_e[i][j] = matrixB[i][j];
            matrix_f[i][j] = matrixB[i + n][j];
            matrix_g[i][j] = matrixB[i][j + n];
            matrix_h[i][j] = matrixB[i + n][j + n];
        }
    }
}

//二维数组内存空间的分配 + 二维数组怎样做实参
void Strassen(int n0, int **aMatrix, int **bMatrix, int **cMatrix)
{
    if (n0 == 1) {
        return;
    }
    
    if (n0 < 64) {
        multi(aMatrix,  bMatrix, cMatrix, n0);
    }
    else {  //该死的else
        
        int n = n0 / 2;  //局部变量最好与全局变量相同
        
        int **r;  int **s;
        int **t;  int **u;
        int **r1; int **r2;
        int **u1; int **u2;
        
        int **P7;
        int **P1;  int **P2;
        int **P3;  int **P4;
        int **P5;  int **P6;
        int **matrix_B1; int **matrix_A2;
        int **matrix_A3; int **matrix_B4;
        int **matrix_A5; int **matrix_B5;
        int **matrix_A6; int **matrix_B6;
        int **matrix_A7; int **matrix_B7;
        
        matrix_A2 = new int *[n];
        r = new int *[n];   s = new int *[n];
        t = new int *[n];   u = new int *[n];
        r1 = new int *[n];  r2 = new int *[n];
        u1 = new int *[n];  u2 = new int *[n];
        P6 = new int *[n];
        P7 = new int *[n];  P1 = new int *[n];
        P2 = new int *[n];  P3 = new int *[n];
        P4 = new int *[n];  P5 = new int *[n];
        matrix_B1 = new int *[n];
        matrix_A3 = new int *[n];  matrix_B4 = new int *[n];
        matrix_A5 = new int *[n];  matrix_B5 = new int *[n];
        matrix_A6 = new int *[n];  matrix_B6 = new int *[n];
        matrix_A7 = new int *[n];  matrix_B7 = new int *[n];
        
        for (int i = 0; i < n; ++i) {
            r[i] = new int[n];   s[i] = new int[n];
            t[i] = new int[n];   u[i] = new int[n];
            r1[i] = new int[n];  r2[i] = new int[n];
            u1[i] = new int[n];  u2[i] = new int[n];
            P6[i] = new int[n];
            P7[i] = new int[n];  P1[i] = new int[n];
            P2[i] = new int[n];  P3[i] = new int[n];
            P4[i] = new int[n];  P5[i] = new int[n];
            matrix_B1[i] = new int[n];  matrix_A2[i] = new int[n];
            matrix_A3[i] = new int[n];  matrix_B4[i] = new int[n];
            matrix_A5[i] = new int[n];  matrix_B5[i] = new int[n];
            matrix_A6[i] = new int[n];  matrix_B6[i] = new int[n];
            matrix_A7[i] = new int[n];  matrix_B7[i] = new int[n];
        }
        splitMatrix(n0);
        
        add(matrix_f,  matrix_h, matrix_B1, n);
        add(matrix_a,  matrix_b, matrix_A2, n);
        add(matrix_c,  matrix_d, matrix_A3, n);
        add(matrix_g,  matrix_e, matrix_B4, n);
        add(matrix_a,  matrix_d, matrix_A5, n);
        add(matrix_e,  matrix_h, matrix_B5, n);
        add(matrix_b,  matrix_d, matrix_A6, n);
        add(matrix_g,  matrix_h, matrix_B6, n);
        add(matrix_a,  matrix_c, matrix_A7, n);
        add(matrix_e,  matrix_f, matrix_B7, n);
        
        
        Strassen(n, (int **)matrix_a,  (int **)matrix_B1, (int **)P1);
        Strassen(n, (int **)matrix_A2, (int **)matrix_h,  (int **)P2);
        Strassen(n, (int **)matrix_A3, (int **)matrix_e,  (int **)P3);
        Strassen(n, (int **)matrix_d,  (int **)matrix_B4, (int **)P4);
        Strassen(n, (int **)matrix_A5, (int **)matrix_B5, (int **)P5);
        Strassen(n, (int **)matrix_A6, (int **)matrix_B6, (int **)P6);
        Strassen(n, (int **)matrix_A7, (int **)matrix_B7, (int **)P7);
        
        // multi((int **)aMatrix,  (int **)bMatrix, (int **)cMatrix, n0);  //每次递归调用只需乘一次
        
        add((int **)P1,  (int **)P2, (int **)s,  n);
        add((int **)P3,  (int **)P4, (int **)t,  n);
        add((int **)P5,  (int **)P4, (int **)r1, n);
        sub((int **)P2,  (int **)P6, (int **)r2, n);
        sub((int **)r1,  (int **)r2, (int **)r,  n);
        add((int **)P5,  (int **)P1, (int **)u1, n);
        sub((int **)P3,  (int **)P7, (int **)u2, n);
        sub((int **)u1,  (int **)u2, (int **)u,  n);
        
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j) {
                cMatrix[i][j] = r[i][j];
                cMatrix[i + n][j] = s[i][j];
                cMatrix[i][j + n] = t[i][j];
                cMatrix[i + n][j + n] = u[i][j];
            }
        }
        
        for (int i = 0; i < n; ++i) {
            delete [] r[i];   delete [] s[i];
            delete [] t[i];   delete [] u[i];
            delete [] r1[i];  delete [] r2[i];
            delete [] u1[i];  delete [] u2[i];
            delete [] P6[i];
            
            delete [] P7[i];  delete [] P1[i];
            delete [] P2[i];  delete [] P3[i];
            delete [] P4[i];  delete [] P5[i];
            /*
             delete [] matrix_B1[i];  delete [] matrix_A2;
             delete [] matrix_A3[i];  delete [] matrix_B4;
             delete [] matrix_A5[i];  delete [] matrix_B5;
             delete [] matrix_A6[i];  delete [] matrix_B6;
             delete [] matrix_A7[i];  delete [] matrix_B7;
             */
        }
        
        delete r;   delete s;
        delete t;   delete u;
        delete r1;  delete r2;
        delete u1;  delete u2;
        delete P6;
        delete P1;  delete P2;
        delete P3;  delete P4;
        delete P5;  delete P7;
        /*
         delete matrix_B1; // delete matrix_A2;
         delete matrix_A3;  delete matrix_B4;
         delete matrix_A5;  delete matrix_B5;
         delete matrix_A6;  delete matrix_B6;
         delete matrix_A7;  delete matrix_B7;
         */
    }
}

template<typename T>
void FillMatrix( T** MatrixA, T** MatrixB, int length)
{
    for(int row = 0; row < length; row++)
    {
        for(int column = 0; column < length; column++)
        {
            MatrixB[row][column] = (MatrixA[row][column] = rand() %5);
        }
    }
}

template<typename T>
void PrintMatrix(T **MatrixA,int MatrixSize)
{
    cout<<endl;
    for(int row = 0; row<MatrixSize; row++)
    {
        for(int column = 0; column<MatrixSize; column++)
        {
            cout<<MatrixA[row][column]<<"\t";
            if ((column+1)%((MatrixSize)) == 0)
                cout<<endl;
        }
    }
    cout<<endl;
}

int main(void)
{
    cin >> n;
    
    int **matrixC;
    matrixC  = new int *[n];
    matrixA  = new int *[n]; matrixB  = new int *[n];
    matrix_a = new int *[n]; matrix_b = new int *[n];
    matrix_c = new int *[n]; matrix_d = new int *[n];
    matrix_e = new int *[n]; matrix_f = new int *[n];
    matrix_g = new int *[n]; matrix_h = new int *[n];
    for (int i = 0; i < n; ++i) {
        matrixA[i]  = new int[n];
        matrixB[i]  = new int[n];   matrixC[i]  = new int[n];
        matrix_a[i] = new int[n];   matrix_b[i] = new int[n];
        matrix_c[i] = new int[n];   matrix_d[i] = new int[n];
        matrix_e[i] = new int[n];   matrix_f[i] = new int[n];
        matrix_g[i] = new int[n];   matrix_h[i] = new int[n];
    }
    
    FillMatrix(matrixA, matrixB, n);
    Strassen(n, matrixA, matrixB, matrixC);
    PrintMatrix(matrixC, n);
    for (int i = 0; i < n; ++i) {
        delete [] matrixA[i];
        delete [] matrixB[i];    delete [] matrixC[i];
        delete [] matrix_a[i];   delete [] matrix_b[i];
        delete [] matrix_c[i];   delete [] matrix_d[i];
        delete [] matrix_e[i];   delete [] matrix_f[i];
        delete [] matrix_g[i];   delete [] matrix_h[i];
    }
    delete matrixC;
    delete matrixA;    delete matrixB;
    delete matrix_a;   delete matrix_b;
    delete matrix_c;   delete matrix_d;
    delete matrix_e;   delete matrix_f;
    delete matrix_g;   delete matrix_h;
}

