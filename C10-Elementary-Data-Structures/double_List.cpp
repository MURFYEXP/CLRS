#include <iostream>
using namespace std;

struct list
{
    int key;
    list *pre;
    list *next;
    list(int k): key(k) {}
};
list *head;

//链表的搜索
list *listSearch(list *l, int k)
{
    list *x = head;
    while (x != nullptr && k != x->key){
        x = x->next;
    }
    return x;
}

//链表的头插入
void listInsert(list *l, list *x)
{
    //在更新head之前
    x->next = head;   //x->next赋值
    x->pre = nullptr; //x->pre赋值
    
    //更新head
    if (head != nullptr) { //链表不为空时
        head->pre = x; //还需更新head->pre
    }
    head = x;  //更新head
}

//链表的删除
void listDelete(list *l, list *x)
{
    //更新中间的pre，next两个指针
    if (x->pre != nullptr)
    {
        //判断是否为空指针，x为头结点时
        x->pre->next = x->next;
    }
    else
    {
        head = x->next; //x为头结点时更新head指针
    }
    if (x->next != nullptr)
    {
        //判断是否为空指针，x为尾结点时
        x->next->pre = x->pre;
    }
}

int main()
{
    head = new list(1); //分配内存空间
    list* listnode1 = new list(2);
    list* listnode2 = new list(3);
    list* listnode3 = new list(4);
    head->next = listnode1; listnode1->pre = head;
    listnode1->next = listnode2; listnode2->pre = listnode1;
    listnode2->next = listnode3; listnode3->pre = listnode2;
    
    cout << "listSearch: " << listSearch(head, 3)->key << endl;
    cout << "Before listDelete: " << head->next->key << endl;
    listDelete(head, listnode1);
    cout << "After listDelete: " << head->next->key << endl;
}