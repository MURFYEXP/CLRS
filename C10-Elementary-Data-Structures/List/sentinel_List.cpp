#include <iostream>
using namespace std;

/*哨兵元素基本上不能降低数据结构各种操作的渐进
 时间界，但可以降低常数因子*/
struct list
{
    int key;
    list *pre;
    list *next;
    list(int k): key(k) {}
};
list *nil; //哨兵(sentinel)元素,简化边界条件


//链表的搜索
list *listSearch(list *l, int k)
{
    //nil->next为头结点
    list *x = nil->next;
    while (x != nil && k != x->key){
        x = x->next;
    }
    return x;
}

//链表的头插入
void listInsert(list *l, list *x)
{
    //在更新head之前
    x->next = nil->next;   //x->next赋值
    x->pre = nil; //x->pre赋值
    
    //更新head
    nil->next->pre = x; //还需更新head->pre
    nil->next = x;  //更新head
}

//链表的删除
void listDelete(list *l, list *x)
{
    //更新中间的pre，next两个指针
    x->pre->next = x->next;
    x->next->pre = x->pre;
}

int main()
{
    nil = new list(-1);
    list* listnode1 = new list(1);
    list* listnode2 = new list(2);
    list* listnode3 = new list(3);
    
    nil->next = listnode1; nil->pre = listnode3;
    listnode1->next = listnode2; listnode2->pre = listnode1;
    listnode2->next = listnode3; listnode3->pre = listnode2;
    
    cout << "listSearch: " << listSearch(nil, 3)->key << endl;
    cout << "Before listDelete: " << listnode1->next->key << endl;
    listDelete(nil, listnode2);
    cout << "After listDelete: " << listnode1->next->key << endl;
}
