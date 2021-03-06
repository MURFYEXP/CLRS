#include <iostream>
#include <stack>
using namespace std;

struct treeNode
{
    int data;
    treeNode *left;
    treeNode *right;
    treeNode(int data): data(data)
    {
        //新结点的左右孩子必须初始化为空
        left = nullptr;
        right = nullptr;
    }
};

void inorderTraversal(treeNode* root)
{
    stack< treeNode* > s;
    treeNode *p = root;
    //使用指针，必备工作之判断是否为空
    while(p || !s.empty())
    {
        {
            //相对于if，continue组合，使用while循环可减少p与s的一次判断
            while(p != nullptr)
            {
                s.push(p);
                p = p->left;
            }
            
            p = s.top();
            s.pop();
            cout << p->data << endl;
            p = p->right; //p的右孩子不为空，则循环一轮上述操作
        }
    }
}

int main()
{
    treeNode *root = new treeNode(1);
    treeNode *node1 = new treeNode(2);
    treeNode *node2 = new treeNode(3);
    treeNode *node3 = new treeNode(4);
    treeNode *node4 = new treeNode(5);
    
    root->left = node1; root->right = node2;
    node1->left = node3; node2->right = node4;
    inorderTraversal(root);
}