//接口设计应该要简单干净
class queue
{
    stack<int> s1;
    stack<int> s2;

public:
    void push(int x)
    {
        s1.push(x); //尾入队列
    }
    
    void pop()
    {
        peek(); //头出队列
        s2.pop();
    }
    
    void peek()
    {
        if (s2.empty())
        {
            transit();
        }
    }
    
    //将s1栈中元素出栈依次入s2中
    void transit()
    {
        while (!s1.empty())
        {
            s2.push(s1.top());
            s1.pop();
        }
    }
};