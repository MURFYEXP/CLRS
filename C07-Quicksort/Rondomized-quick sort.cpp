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

int randomizedPartition(int *A, int p, int q)
{
    int i = rand() % (q - p) + p; //random随机生成区间主元
    swap(A[i], A[p]);
    return partition(A, p, q);
}

void randomizedQuickSort(int *A, int p, int r)
{
    int q;
    if (p < r) {
        q = randomizedPartition(A, p, r);
        randomizedQuickSort(A, p, q - 1);
        randomizedQuickSort(A, q + 1, r);
    }
}

int main(void)
{
    int a[10] = {1, 3, 11, 7, 2, 4, 6, 3, 9, 4};
    randomizedQuickSort(a, 0, 9);
    for (int i = 0; i < 10; ++i) {
        cout << a[i] << endl;
    }
}

