#include <iostream>
#include <cassert>
#define MAX 10
using namespace std;

struct Stack
{
    int data[MAX];
    int top;  //栈顶
};

bool stackEmpty(Stack *s)
{
    if (s->top == 0) {
        return true;
    }
    return false;
}

void push(Stack *s, int x)
{
    if (s->top == MAX) {
        cout << "overflow" << endl;
        assert(0); //assert报错，停止进程
    }
    s->top += 1;
    s->data[s->top] = x;
}

int pop(Stack *s)
{
    if (stackEmpty(s)) {
        cout << "underflow" << endl;
        assert(0); //assert报错，停止进程
    }
    s->top -= 1;
    return s->data[s->top + 1];
}

int main()
{
    Stack sta;
    sta.top = 0;
    cout << stackEmpty(&sta) << endl;
    
    push(&sta, 6);
    push(&sta, 7);
    
    pop(&sta);
    pop(&sta);
}