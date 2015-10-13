#include <iostream>
#include <math.h>
using namespace std;

/*概念性，含义最好看经典书的解释，次之博客
 int *a = new int;
 delete a; //delete后，a变成没有定义。但仍存放了它之前所指对象的地址，但该对象已不存在
 a = 0;    //trick
 */

int partition(int *A, int p, int q, int x)
{
    int i; //for语句外定义i
    for (i = p; i < q; ++i){
        if (A[i] == x)  break;
    }
    swap(A[i], A[p]);  //区间内交换
    i = p;
    //int x = A[p];
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

int findMedian(int arr[], int n)
{
    sort(arr, arr+n);
    return arr[n/2];  //返回下中位数
}

//查找数组第k大元素
int select(int *A, int l, int r, int k)
{
    int n = r - l + 1;
    if (k > 0 && k <= n) { //递归条件
        int i, groupNum;  //对n个元素进行分组
        groupNum = floor(n / 5);
        int median[(n + 4) / 5]; //分组,从下标0开始
        for (i = 0; i < groupNum; ++i) {
            median[i] = findMedian(A + l + i * 5, 5);
        }
        if ((i * 5) < n) { //最后一组元素
            median[i] = findMedian(A + l + i * 5, n % 5);
            ++i;  //i即median数组的长度
        }
        //用select递归继续对median数组寻找中位数
        int medOFmed = (i == 1) ? median[0] : select(median, 0, i - 1, i / 2);
        //对输入数组进行划分
        int p = partition(A, l, r, medOFmed);
        if (p - l == k - 1) { //第k大元素
            return A[p];
        }
        if (p - l > k - 1) {
            return select(A, l, p - 1, k); //小区间的第k位，直接返回，否则返回INT_MAX
        }
        else { //大区间的第k - p + l - 1位
            return select(A, p + 1, r, k - p + l - 1);
        }
    }
    return INT_MAX;
}

int main(void)
{
    int k = 3;
    int a[11] = {6, 10, 5, 2, 16, 14, 1, 4, 8, 9, 12};
    cout << "K'th smallest element is " << select(a, 0, 10, k) << endl;
}
