#include <iostream>
#define N 10
int c[15];
int length;
using namespace std;

void countSort(int *A, int *B, int k)
{
    for (int i = 0; i <= k; ++i) {
        c[i] = 0;
    }
    //数组传参求长度
    cout  << length << endl;
    for (int j = 0; j < length; ++j) {
        ++c[A[j]];
    }
    for (int i = 1; i <= k; ++i) {
        c[i] = c[i] + c[i - 1];
    }
    for (int j = 0; j < length; ++j) {
        B[c[A[j]] - 1] = A[j]; //数组以0开头，下标应为位置-1
        --c[A[j]];  //重复元素位置向前移一位
    }
}

int main(void)
{
    int a[N] = {1, 3, 0, 7, 11, 2, 0, 7, 6, 8};
    int b[N];
    length = 10; //主函数内给全局变量赋值
    //cout  << length << endl;
    countSort(a, b, 15);
    for (int i = 0; i < 10; ++i) {
        cout << b[i] << endl;
    }
}
