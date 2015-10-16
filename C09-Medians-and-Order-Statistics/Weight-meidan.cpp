#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

struct node
{
	int value;
	float weight;
};

int partition(node *A, int p, int q, int x)
{
    int i; //for语句外定义i
    for (i = p; i < q; ++i){
        if (A[i].value == x)  break;
    }
    swap(A[i], A[p]);  //区间内交换
    i = p;
    //int x = A[p];
    for (int j = p + 1; j <= q; ++j)
    {
        if (A[j].value <= x) {
            ++i;
            swap(A[i], A[j]);
        }
    }
    swap(A[p], A[i]);
    return i; //返回主元
}

int findMedian(node arr[], int n)
{
    int* newArr = new int[n];
    //将node数组中元素的value值用newArry储存用于sort排序
    for (int i = 0; i < n; ++i) {
        newArr[i] = arr[i].value;
    }
    sort(newArr, newArr + n);
    return newArr[n / 2];  //返回下中位数
}

int x_k;
//查找数组第k大元素
int select(node *A, int l, int r, int k)
{
    int n = r - l + 1;
    if (k > 0 && k <= n) { //递归条件
        int i, groupNum;  //对n个元素进行分组
        groupNum = floor(n / 5);
        node median[(n + 4) / 5]; //分组,从下标0开始
        for (i = 0; i < groupNum; ++i) {
            median[i].value = findMedian(A + l + i * 5, 5);
        }
        if ((i * 5) < n) { //最后一组元素
            median[i].value = findMedian(A + l + i * 5, n % 5);
            ++i;  //i即median数组的长度
        }
        //继续对median数组寻找中位数
        int medOFmed = (i == 1) ? median[0].value : select(median, 0, i - 1, i / 2);
        //对输入数组进行划分
        int p = partition(A, l, r, medOFmed);
        if (p - l == k - 1) { //第k大元素
            x_k = p;
            return A[p].value;
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

//小数据测试，如爆栈则一般为递归条件处理有问题,重构时，保留原文件
int weightedMedian(node *A, int l, int r, float w_k)
{
    int len = r - l + 1;
    float w_b = 0;  //沉重的一击
    if (len == 1) {
        return A[0].value; //返回第一个元素
    }
    else if (len == 2) {
        if (A[0].weight >= A[1].weight) {
            return A[0].value;
        }
        return A[1].value;
    }
    else {
        select(A, l, r, len / 2);  //上面已保证K值大于0
        vector<node> v1; vector<node> v2;
        for (int i = l; i <= r; ++i) {
            if (A[i].value <= A[x_k].value) {
                v1.push_back(A[i]);
            }
            else {
                v2.push_back(A[i]);
            }
        }
        node *left  = new node[v1.size()];
        node *right = new node[v2.size()];
        for (int i = 0; i < v1.size(); ++i) {
            w_b += v1[i].weight;
            left[i] = v1[i];
        }
        for (int i = 0; i < v2.size(); ++i) {
            right[i] = v2[i];
        }
        if (w_k + w_b > 0.5) { //关注左侧
            return weightedMedian(left, 0, v1.size() - 1, w_k);
        }
        else {
            return weightedMedian(right, 0, v2.size() - 1, w_b);
        }
    }
    return INT_MAX;
}

int main(void)
{
    node a[8];
    a[0].value = 5;  a[0].weight = 0.09;
    a[1].value = 10; a[1].weight = 0.13;
    a[2].value = 2;  a[2].weight = 0.11;
    a[3].value = 6;  a[3].weight = 0.02;
    a[4].value = 16; a[4].weight = 0.17;
    a[5].value = 11; a[5].weight = 0.04;
    a[6].value = 9;  a[6].weight = 0.24;
    a[7].value = 12; a[7].weight = 0.2;
    cout << "Weighted Median element is " << weightedMedian(a, 0, 7, 0) << endl;
}
