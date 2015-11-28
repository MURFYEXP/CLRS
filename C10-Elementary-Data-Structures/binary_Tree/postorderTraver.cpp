#include <iostream>
#include <stack>
#include <vector>
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

vector<int> postorderTraversal(treeNode* root)
{
    vector<int> v;
    stack<treeNode*> stacks;
    stacks.push(root);
    
    while(!stacks.empty())
    {
        root = stacks.top();
        stacks.pop(); //父结点出栈，递归返回上一层
        v.push_back(root->data);
        
        //子结点入栈，递归进入下一层
        if(root->left)
        {
            stacks.push(root->left);
        }
        if(root->right)
        {
            stacks.push(root->right);
        }
    }
    //后序遍历，父节点最后输出，反转向量v
    reverse(v.begin(), v.end());
    return v;
}

int main()
{
    treeNode *root = new treeNode(1);
    treeNode *node1 = new treeNode(2);
    treeNode *node2 = new treeNode(3);
    treeNode *node3 = new treeNode(4);
    treeNode *node4 = new treeNode(5);
    treeNode *node5 = new treeNode(6);
    treeNode *node6 = new treeNode(7);
    
    root->left = node1; root->right = node2;
    node1->left = node3; node2->right = node4;
    node3->right = node6; node2->left = node5;
    
    vector<int> v = postorderTraversal(root);
    for (int i = 0; i < v.size(); ++i)
    {
        cout << v[i] << endl;
    }
}