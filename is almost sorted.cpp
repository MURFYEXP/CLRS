/* if the list A is sorted, the algorithm always returns true;
 if the list A is not 90% sorted, the algorithm always returns false
 with probability at least 2/3;
 */
#include <iostream>
using namespace std;

int binarySearch(int *A, int left, int right, int key)
{
    int slot = 0;
    if (left > right) { //递归出口
        return slot;
    }
    if (left == right) {
        return left;
    }
    int mid = ((left + right) / 2) + 1;  //mid向上取整
    if (key == A[mid]) {
        return mid;
    }
    if (key < A[mid]) {
        return binarySearch(A, left, mid - 1, key); //直接返回，防止返回slot
    }
    if (key > A[mid]){
        return binarySearch(A, mid, right, key); //同上
    }
    return slot;
}

bool isAlmostSorted(int *A, int n, int k)
{
    //传入的k为定值。k为 lg(1/3)/lg(0.9).向上取整为11
    for (int r = 0; r <= k; ++r) {
        int i = (rand() % n) + 1; //加上区间首位，防止得到的随机为0
        int j = binarySearch(A, 1, n, A[i]);
        if (i != j) {
            return false;
        }
    }
    return true;
}

int main(void)
{
    bool result;
    int a[12] = {0, 1, 2, 3, 4, 6, 12, 7, 8, 15, 10, 11};
    //数组从下标1开始
    result = isAlmostSorted(a, 11, 11);
    cout << result << endl;
}