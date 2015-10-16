#include <iostream>
using namespace std;

bool is_odd(int n)
{
    if ((n % 2) == 1) {
        return true;
    }
    return false;
}

int result = 0;
bool isFind = false;
int findMax(int *a, int left, int right)
{
    int midVal = 0;
    int size = right - left + 1;
    bool isOdd = is_odd(size);
    if (isOdd == true){
        midVal = left + ((size + 1) / 2) - 1;
    }
    else
    {
        midVal = left + ((size) / 2) - 1;
    }
    //递归出口
    if ((a[midVal - 1] < a[midVal]) && (a[midVal] > a[midVal + 1])) {
        result = a[midVal];
        return result;
    }
    if ((a[midVal - 1] < a[midVal]) && (a[midVal] < a[midVal + 1])) {
        findMax(a, midVal, right);
    }
    else if ((a[midVal - 1] > a[midVal]) && (a[midVal] > a[midVal + 1]))
    {
        findMax(a, left, midVal);
    }
    return -1;
}

int main(int argc, const char * argv[])
{
    int a[11] = {0, 1, 2, 3, 4, 6, 9, 11, 2, 1, 0};
    findMax(&a[1], 1, 10);  //这样传数组形参没问题
    cout << result << endl;
}
