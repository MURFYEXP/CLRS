#include <iostream>
using namespace std;

//改变的是形参的值，应该传内存地址
void exchange(int *a, int *b)
{
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

int partition(int *A, int p, int q)
{
    int i = p;
    int x = A[p];
    for (int j = p + 1; j <= q; ++j)
    {
        if (A[j] <= x) {
            ++i;
            exchange(&A[i], &A[j]);
        }
    }
    exchange(&A[p], &A[i]);
    return i; //返回主元
}

void quickSort(int *A, int p, int r)
{
    /*
     if (q <= p) {
     return;   //有返回值时，写成if形式
     }*/
    int q;
    if (p < r) {
        q = partition(A, p, r);
        quickSort(A, p, q - 1);
        quickSort(A, q + 1, r);
    }
}

int main(void)
{
    int a[10] = {1, 3, 11, 7, 2, 4, 6, 3, 9, 4};
    quickSort(a, 0, 9);
    for (int i = 0; i < 10; ++i) {
        cout << a[i] << endl;
    }
}

