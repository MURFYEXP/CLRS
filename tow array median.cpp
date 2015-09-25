#include <iostream>
#define N 10
using namespace std;

int findMedian(int *A, int *B, int p, int q, int n)
{
    if (p > q) //递归出口
    {
        return -1;  //A数组中查找median失败返回-1
    }
    int k = (p + q) / 2;
    int m = A[k];
    if ((k == n) && (m <= B[1])) {
        return m;
    }
    if ((k < n) && (B[n - k] <= m) &&
        (m <= B[n - k + 1])) {
        return m;
    }
    if (m < B[n - k]) { //二分查找正确的median位置k
        findMedian(A, B, k - 1, q, n);
    }
    if (B[n - k + 1] < m) {
        findMedian(A, B, p, k + 1, n);
    }
    return -1; //同上
}

int towArrayMedian(int *A, int *B)
{
    int median;
    median = findMedian(A, B, 1, N, N);
    if (median == -1) { //换数组B重新查找
        median = findMedian(B, A, 1, N, N);
    }
    return median;
}

int main(void)
{
    int median;
    int a[11] = {0, 1, 23, 24, 30, 32, 100, 101, 102, 105, 120};
    int b[11] = {0, 3, 20, 29, 30, 42, 90, 104, 110, 115, 126};
    //两已排序数组O（lgn）查找两数组合并后的中位数
    median = towArrayMedian(&a[1], &b[1]);
    cout << median << endl;
}

