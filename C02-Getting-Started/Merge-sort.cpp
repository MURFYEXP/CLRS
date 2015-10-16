#include <iostream>
#define watchMan 65532
using namespace std;

void createArray(int *A, int p, int n, int *B)
{
    for (int i = 0; i < n; ++i) {
        B[i] = A[p];
        ++p;
    }
    B[n] = watchMan;
}

void Merge(int *A, int p, int q, int r)
{
    int n1 = q - p + 1;
    int n2 = r - q;
    int Left[n1 + 1], Right[n2 + 1];
    createArray(A, p, n1, Left);
    createArray(A, q + 1, n2, Right);
    int i = 0, j = 0;
    //使用哨兵减少了每次空堆的判断
    for (int k = p; k <= r; ++k)
    {
        if (Left[i] <= Right[j])
        {
            A[k] = Left[i];
            ++i;
        }
        else
        {
            A[k] = Right[j];
            ++j;
        }
    }
}


void mergeSort(int *A, int p, int r)
{
    if (p >= r) {
        return;
    }
    int q = (r + p) / 2; //分割点
    mergeSort(A, p, q);
    mergeSort(A, q + 1 , r);
    Merge(A, p, q, r);
}


int main(void)
{
    int a[10] = {1, 3, 11, 7, 2, 4, 6, 3, 9, 4};
    mergeSort(a, 0, 9);
    for (int i = 0; i < 10; ++i) {
        cout << a[i] << endl;
    }
}

