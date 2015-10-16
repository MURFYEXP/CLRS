#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

struct cmp{
    bool operator() (ListNode *n1, ListNode *n2){
        return n1->val >= n2->val;
    }
};

class Solution {
public:
    //引用很好使，得到新链表，返回头指针
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        //使用优先队列，最小堆,队列存指针解决next的替补问题
        priority_queue<ListNode*, vector<ListNode*>, cmp> qs;
        
        for(int i = 0;i < lists.size();i++)
            if(lists[i]) //引用地址不为null，push
                qs.push(lists[i]);
        if(qs.empty()) return NULL;
        //定义head，backup
        ListNode * head(qs.top()), *backup(head);
        
        while(!qs.empty())
        {
            ListNode *node = qs.top();
            qs.pop();
            if(node->next) qs.push(node->next);
            //head的next为优先队列队首
            head->next = qs.top();
            head = head->next;
        }
        head->next = NULL; //链表结束
        
        return backup; //返回头指针
    }
};

int main()
{
    Solution s;
    
    ListNode *n1 = new ListNode(1);
    ListNode *n2 = new ListNode(2);
    ListNode *n3 = new ListNode(3);
    ListNode *n4 = new ListNode(4);
    ListNode *n5 = new ListNode(10);
    n1->next = n2;
    n2->next = n3;
    n3->next = n4;
    n4->next = n5;
    
    ListNode *n6 = new ListNode(4);
    ListNode *n7 = new ListNode(6);
    ListNode *n8 = new ListNode(7);
    ListNode *n9 = new ListNode(8);
    ListNode *n10 = new ListNode(9);
    n6->next = n7;
    n7->next = n8;
    n8->next = n9;
    n9->next = n10;
    
    //初始链表头指针入容器v1
    vector<ListNode*> v1;
    v1.push_back(n1);
    v1.push_back(n6);
    
    ListNode *head = s.mergeKLists(v1);
    while(head)
    {
        cout << head->val << endl;
        head = head->next;
    }
    return 0;
}