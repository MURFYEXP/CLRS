struct listNode
{
    int data;
    listNode *next;
};
listNode *list;

void buildList(listNode *l, int *A, int n)
{
    listNode *ptr;
    listNode *tail;
    l = new listNode;
    tail = l;    //tail直接赋值
    for (int i = 0; i < n; ++i) {
        ptr = new listNode;
        ptr->data = A[i];
        tail->next = ptr; //将尾节点的指针指向新节点
        tail = ptr;       //新节点为当前尾节点
    }
    list = l->next;       //全局变量list，防止栈退出后指针为空
    tail->next = NULL;    //当前链表结束
}

//直接返回节点指针即可，不再需定义全局变量
listNode *deleteHead(listNode *l)
{
    listNode *pHead;
    pHead = l->next;
    delete l;
    l = pHead; //下一个节点成为新的头节点
    cout << l << endl;
    return l;
}
