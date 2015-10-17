#include <iostream>
using namespace std;

int partition(int *A, int p, int q)
{
    int i = p;
    int x = A[p];
    for (int j = p + 1; j <= q; ++j)
    {
        if (A[j] <= x) {
            ++i;
            swap(A[i], A[j]);
        }
    }
    swap(A[p], A[i]);
    return i; //返回主元
}

int randomizedPartition(int *A, int p, int q)
{
    int i = rand() % (q - p) + p; //random随机生成区间主元
    swap(A[i], A[p]);
    return partition(A, p, q);
}

int randomizedSelect(int *A, int l, int r, int k)
{
    if (l == r) {  //边界的处理
        return A[l];
    }
    int q = randomizedPartition(A, l, r);
    int i = q - l + 1; //划分返回的主元
    if (i == k) {
        return A[q];
    }
    else if (i < k) {
        return randomizedSelect(A, q + 1, r, k - i);
    }
    else {
        return randomizedSelect(A, l, q - 1, k);
    }
    return INT16_MAX;
}

int main(void)
{
    int a[11] = {0, 1, 3, 11, 7, 2, 4, 6, 3, 9, 4};
    cout << randomizedSelect(a, 1, 10, 1) << endl;
}
