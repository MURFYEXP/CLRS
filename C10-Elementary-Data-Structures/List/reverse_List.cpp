struct list
{
    int key;
    list *next;
};

list *reverseList(list* head)
{
    list *tmp = head;
    list *pre = nullptr; //原list结点的pre结点
    while (tmp != nullptr)
    {
        tmp->next = pre; //next结点reverse，指向pre
        pre = tmp;       //更新pre，pre为当前tmp
        tmp = tmp->next; //更新tmp
    }
    return pre; //返回新list的头结点
}
