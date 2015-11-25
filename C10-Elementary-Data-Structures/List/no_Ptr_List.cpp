#include <iostream>
using namespace std;
#define MAX 10
#define emptyList -1

int Free = 0; //初始化为0
typedef int list_t;
list_t Array[MAX * 3];//使用typedef，好的重命名，程序得到更好的扩展性
#define KEY(i)  Array[i] //使用宏定义，程序得到更好的扩展性
#define NEXT(i) Array[i + 1]
#define PRE(i)  Array[i + 2]

void initArrayNext() //初始化next链表，从左往右(最简方式)
{
    for (int i = 0; i < (MAX - 1) * 3; i += 3)
    {
        NEXT(i) = i + 3;
    }
    NEXT(MAX * 3 - 2) = -1; //边界的处理
}

int allocateObject()
{
    if (Free == -1) //边界的处理
    {
        cout << "out of space" << endl;
        return -1;
    }
    else
    {
        int x = Free;
        Free = NEXT(x);
        return x; //返回插入位置
    }
}

void freeObject(int x)
{
    NEXT(x) = Free; //x插入自由链表头位置
    Free = x; //更新自由链表头
}

list_t cons(list_t list , list_t key) //类似于序对的闭包
{
    //在list链表上黏上一个新对象
    list_t newOjt = allocateObject();
    KEY(newOjt) = key;  //更新新对象的key
    PRE(newOjt) = list; //更新新对象的pre
    NEXT(newOjt) = -1;  //下一个黏上一个的对象位置未知
    
    if (list != emptyList) {
        NEXT(list) = newOjt; //更新list的next就为新对象
    }
    return newOjt;
}

void listDelet(int x) //第i个元素的x为3 * i
{
    if (PRE(x) != emptyList)
    {
        NEXT(PRE(x)) = NEXT(x);
    }
    if (NEXT(x) != emptyList)
    {
        PRE(NEXT(x)) = PRE(x);
    }
}

int main()
{
    initArrayNext();
    list_t new_list = cons(emptyList, 100);
    new_list = cons(new_list, 99);
    new_list = cons(new_list, 98);
    new_list = cons(new_list, 97);
    new_list = cons(new_list, 96);
    listDelet(3);
}