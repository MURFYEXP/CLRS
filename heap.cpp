#include <iostream>
#define lchild(x) ((x) << 1)     //外面加括号
#define rchild(x) (lchild(x) | 1)
int size;
using namespace std;

void maxHeapify(int *A, int i)
{
    int largest = 0;
    int l = lchild(i);
    int r = rchild(i);
    if (l <= size && A[i] <= A[l]) {
        largest = l;
    }
    else {
        largest = i;
    }
    //A[r]与当前最大值比较
    if (r <= size && A[largest] <= A[r]) {
        largest = r;
    }
    if (largest != i) {
        swap(A[i], A[largest]);
        maxHeapify(A, largest);
    }
}

void buildHeap(int *A)
{
    int n = size / 2;
    for (int i = n; i > 0; --i) {
        maxHeapify(A, i);
    }
}

void heapSort(int *A)
{
    buildHeap(A);    //建堆
    // int n = size; 必须使用全局变量size，其值影响maxHeapify函数
    while (size > 1) {  //终止条件，至少两个数比较
        swap(A[1], A[size]);
        size -= 1;
        maxHeapify(A, 1);
    }
}

int main(void)
{
    size = 10;
    int a[11] = {0, 14, 10, 6, 2, 16, 7, 1, 4, 8, 9};
    heapSort(a);
    for (int i = 1; i < 11; ++i) {
        cout << a[i] << endl;
    }
}