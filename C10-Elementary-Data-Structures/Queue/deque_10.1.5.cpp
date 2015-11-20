#include <iostream>
#include <cassert>
using namespace std;

struct Deque
{
    int *data; //定义为指针
    int length;
    int left; //两“指针”位置均不插入元素
    int right; //length的长度包括right和left
    Deque(int size): left(1), right(1), length(size + 2){
        //根据双端队列的大小，动态分配内存空间
        data = new int(size + 2);
    };
};

//判断双端队列是否为空
bool Deque_Empty(Deque &D)
{
	if(D.left == D.right)
		return true;
	return false;
}

//相对于单向队列的实现，提取子函数
int pre(Deque &d ,int pos)
{
    if (pos == 1) {  //循环向右
        return d.length;
    }
    return pos - 1;
}

int next(Deque &d ,int pos)
{
    if (pos == d.length) { //循环向左
        return 1;
    }
    return pos + 1;
}

//形参为引用形式,左插
void Deque_Left_Insert(Deque &d, int x)
{
    int tmp = pre(d, d.left);
    //先判断更新后left值，如果溢出，则报错不再插入
    if (tmp == d.right) {
        cout << "error: overflow" << endl;
        return;
    }
    d.data[d.left] = x; //左插入队列
    if (d.left == d.right) { //队列为空时，更新right值
        d.right += 1;
    }
    d.left = tmp; //更新left值
}

//右插,原理类似同上
void Deque_Right_Insert(Deque &d, int x) //形参为引用形式
{
    int tmp = next(d, d.right);
    //先判断更新后right值，如果溢出，则报错不再插入
    if (tmp == d.left) {
        cout << "error: overflow" << endl;
        return;
    }
    d.data[d.right] = x; //右插入队列
    if (d.left == d.right) { //队列为空时，更新left值
        d.left = d.length;
    }
    d.right = tmp; //更新right值
}

//左删
int Deque_Left_Delete(Deque &d)
{
    if (Deque_Empty(d)) { //报错处理
        cout << "error: underflow" << endl;
        return -1;
    }
    d.left = next(d, d.left);
    int x = d.data[d.left]; //left出队列
    //边界情况：当d.left前进一步等于d.right时，队列中只有一个元素
    if(next(d, d.left) == d.right) {
		d.right = d.left; //让d.right = d.left，再删除，则报下溢出
    }
    return x;
}

//右删
int Deque_Right_Delete(Deque &d)
{
    if (Deque_Empty(d)) { //报错处理
        cout << "error: underflow" << endl;
        return -1;
    }
    d.right = pre(d, d.right);
    int x = d.data[d.right]; //right出队列
    //边界情况：当d.left前进一步等于d.right时，队列中只有一个元素
    if(next(d, d.left) == d.right) {
		d.left = d.right; //让d.left = d.right，再删除，则报下溢出
    }
    return x;
}

//从队列头到队列尾输出
void Print(Deque& d)
{
    int i;
    if(d.left <= d.right)
    {
        //right处不能插入元素
        for(i = d.left + 1; i < d.right; i++)
            cout << d.data[i] << ' ';
        cout << endl;
    }
    //因为循环的原因，right可能在left的前面
    else
    {
        for(i = d.left + 1; i <= d.length; i++)
            cout << d.data[i] << ' ';
        for(i = 1; i < d.right; i++) //同上
            cout << d.data[i] << ' ';
        cout << endl;
    }
}

int main()
{
    Deque de(5);
    Deque_Left_Insert(de, 1);
    Deque_Left_Insert(de, 2);
    Deque_Right_Insert(de, 3);
    Deque_Right_Insert(de, 4);
    Deque_Right_Insert(de, 5);
    Deque_Right_Delete(de);
    Deque_Left_Delete(de);
    Deque_Right_Delete(de);
    Deque_Right_Delete(de);
    Print(de);
}