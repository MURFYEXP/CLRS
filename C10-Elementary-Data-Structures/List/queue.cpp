#include <iostream>
#include <cassert>
#define MAX 4
using namespace std;

struct Queue
{
    int data[MAX + 2]; //数组应多分配一个空间
    int length;
    int head; //头
    int tail; //尾，新元素入队尾, length的长度包括tail
    Queue(): head(1), tail(1), length(MAX + 1) {};
};

bool queueEmpty(Queue *q)
{
    /*
     if ((q->head == q->tail) == 1) {
     return true; //q->head == q->tail时就成立
     }*/
    //头尾都为1时，队列为空
    if (q->head == q->tail) {
        return true;
    }
    return false;
}

void enQueue(Queue *q, int x)
{
    int tmp = 0;
    //先判断更新后tail值，如果溢出，则报错不再插入
    if (q->tail == q->length) { //插入成为队列最后一个元素
        tmp = 1; //第二圈，重头开始插入
    }
    else {
        tmp = q->tail + 1;
    }
    //q->head等于q->tail + 1，上溢
    if (tmp == q->head) { //报错处理
        cout << "error: overflow" << endl;
        return; //q->tail位置不能插入元素，直接跳出
    }
    q->data[q->tail] = x; //队尾入队列
    q->tail = tmp; //更新tail值
}

int deQueue(Queue *q)
{
    if (queueEmpty(q)) { //报错处理
        cout << "error: underflow" << endl;
        return -1;
    }
    int x = q->data[q->head]; //头出队列
    if (q->head == q->length) { //出队列，此时队列仅最后一个元素
        q->head = 1;  //头部重置为1
    }
    else {
        q->head += 1; //防止头部后面的元素整体前移，提高效率，头部后移一位
    }
    return x;
}

//从队列头到队列尾输出
void Print(Queue q)
{
    int i;
    if(q.tail >= q.head)
    {
        //tail处不能插入元素
        for(i = q.head; i < q.tail; i++)
            cout << q.data[i] << ' ';
        cout << endl;
    }
    //因为循环的原因，队列尾可能在队列头的前面
    else
    {
        for(i = q.head; i <= q.length; i++)
            cout << q.data[i] << ' ';
        for(i = 1; i < q.tail; i++) //同上
            cout << q.data[i] << ' ';
        cout << endl;
    }
}

int main()
{
    Queue q;
    
    enQueue(&q, 6);
    enQueue(&q, 7);
    enQueue(&q, 8);
    enQueue(&q, 9);
    
    deQueue(&q);
    deQueue(&q);
    deQueue(&q);
    Print(q);
}