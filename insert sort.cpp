#include <iostream>
int size;
using namespace std;

void insertionSort(int *A)
{
    for (int j = 2; j <= size; ++j) {
        int key = A[j];
        int i = j - 1;   //i为j的前一位
        while (i > 0 && A[i] > key) {
            A[i + 1] = A[i]; //向后移一位
            i -= 1;
        }
        A[i + 1] = key; //A[j]插入前面合适的位置
    }
}

int main(void)
{
    size = 10;
    int a[11] = {0, 14, 10, 6, 2, 16, 7, 1, 4, 8, 9};
    insertionSort(a);
    for (int i = 1; i < 11; ++i) {
        cout << a[i] << endl;
    }
}