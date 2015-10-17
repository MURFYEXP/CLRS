#include <iostream>
#define lchild(x) ((x) << 1)     //外面加括号
#define rchild(x) (lchild(x) | 1)
int heapSize = 10;
using namespace std;

void maxHeapify(int *A, int i)
{
    int largest = 0;
    int l = lchild(i);
    int r = rchild(i);
    if (l <= heapSize && A[i] <= A[l]) {
        largest = l;
    }
    else {
        largest = i;
    }
    //A[r]与当前最大值比较
    if (r <= heapSize && A[largest] <= A[r]) {
        largest = r;
    }
    if (largest != i) {
        swap(A[i], A[largest]);
        maxHeapify(A, largest);
    }
}

void buildHeap(int *A)
{
    int n = heapSize / 2;
    for (int i = n; i > 0; --i) {
        maxHeapify(A, i);
    }
}

//最大优先队列
int heapMaxNum(int *A)
{
    return A[1];
}

//提取队列中最大元素
int heapExtractMax(int *A)
{
    if (heapSize < 1) { //边界处理
        cout << "heap underflow" << endl;
        exit(-1);
    }
    int max = A[1];
    A[1] = A[heapSize - 1];
    heapSize -= 1;    //从队列中排除此元素
    maxHeapify(A, 1); //调整最大堆
    return max;
}

//将元素i增加到k
void heapIncreaseKey(int *A, int i, int key)
{
    if (key <= A[i]) {
        cout << "new key is smaller than current key" << endl;
        exit(-1);
    }
    A[i] = key;
    //不断地与父母比，如果大，则调整位置, i > 1
    while (i > 1 && A[i / 2] < A[i]) {
        swap(A[i], A[i / 2]);
        i = i / 2;
    }
}

//插入元素
void maxHeapInsert(int *A, int key)
{
    heapSize += 1;
    A[heapSize] = -25536; //堆末增加1位，然后将其值增加key
    heapIncreaseKey(A, heapSize, 20);
}

//删除元素
void heapDelet(int *A, int i)
{
    A[i] = A[heapSize];
    heapSize -= 1;  //最后元素替换，然后进行堆调整
    maxHeapify(A, i);
}

int main(void)
{
    int a[11] = {0, 1, 3, 1, 7, 2, 4, 6, 3, 9, 4};
    buildHeap(a);
    cout << heapExtractMax(a) << endl;
}
