class stack
{
    queue<int> q1;
    queue<int> q2; //q1,q2交替pop为空队列
    
public:
    void push(int x)  //入栈: 在有元素的队列中，继续尾插入
    {
        if (!q1.empty())
        {
            q1.push(x);
        }
        else
        {
            q2.push(x);
        }
    }
    
    void pop() //出栈: 在有元素的队列中，从头出队列，尾插入到空队列中，留最后一个元素pop
    {
        if (!q1.empty())
        {
            while (!q1.empty())
            {
                if (q1.size() > 1)
                {
                    q2.push(q1.front()); //最后一个元素不在push
                }
                q1.pop();
            }
        }
        else
        {
            while (!q2.empty())
            {
                if (q2.size() > 1)
                {
                    q1.push(q2.front()); //最后一个元素不在push
                }
                q2.pop();
            }
        }
    }
    
    
};
