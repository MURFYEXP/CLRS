#include <iostream>
using namespace std;

struct treeNode
{
    int value;
    treeNode *parent;
    treeNode *left, *right; //struct内也使用构造函数
    treeNode(int x): value(x), parent(NULL),
    left(NULL), right(NULL) {}
};
treeNode *root;

//中序遍历二叉查找树
void inOrderTreeWalk(treeNode *x)
{
    if (x != NULL) { //递归出口
        inOrderTreeWalk(x->left);
        cout << x->value << endl;
        inOrderTreeWalk(x->right);
    }
}

//查找,递归版
treeNode *treeSearch(treeNode *x, int k)
{
    if (x == NULL || x->value == k) { //递归出口
        return x;
    }
    if (x->value < k) {
        return treeSearch(x->right, k);
    }
    else return treeSearch(x->left, k);
}

//查找,迭代版
treeNode *iterativeTreeSearch(treeNode *x, int k)
{
    //不为null且value不为k
    while (x != NULL && x->value != k) {
        if (x->value < k) {
            x = x->right;
        }
        else x = x->left;
    }
    return x;
}

//返回最小元素
treeNode *treeMiniMum(treeNode *x)
{
    //x->left为null，找到叶结点
    while (x->left != NULL) {
        x = x->left;
    }
    return x;
}

//返回最大元素
treeNode *treeMaxMum(treeNode *x)
{
    while (x->right != NULL) {
        x = x->right;
    }
    return x;
}

//插入,插入到某叶节点上
void treeInsert(treeNode *z)
{
    treeNode *x = root;
    treeNode *y = NULL;
    while (x != NULL) { //寻找合适的位置
        y = x; //y用来记录位置
        if (z->value > x->value) {
            x = x->right;
        }
        else x = x->left;
    }
    z->parent = y; //结点z插入查找树
    if (y == NULL) {
        root = z; //边界情况，查找树为空树
    }
    else if (z->value > y->value)
    {
        y->right = z;
    }
    else {
        y->left = z;
    }
}

//后继
treeNode *treeSuccessor(treeNode *x)
{
    if (x->right != NULL) { //x拥有右结点
        return treeMiniMum(x->right); //右子树最左结点
    }
    treeNode *y = x->parent;
    //x为y的右结点，从x向上查找，只到成为某结点的左结点
    while (y != NULL && x == y->right) { //x没有右结点
        x = y; //更新x， 更新y
        y = y->parent;
    }
    return y;
}

//删除,3种情况的组织
treeNode *treeDelete(treeNode *z)
{
    treeNode *y, *x;
    //y为要删除的元素，x为y的孩子，y最多一个孩子
    if (z->left == NULL || z->right == NULL) {
        y = z; //z最多一个孩子，删除z
    }
    else {
        y = treeSuccessor(z); //两孩子，删除z的后继
    }
    //修改y的父结点，和x的指针，删除y结点
    if (y->left != NULL) {
        x = y->left;
    }
    else {
        x = y->right;
    }
    if (x != NULL) { //x不为null，修改xde父结点
        x->parent = y->parent;
    }
    //修改y的父节点,使用指针时，提醒null的边界判断
    if (y->parent == NULL) { //y为根结点时
        root = x; //定义全局变量root根结点
    }
    //情况a，x可能为null
    else if (y == y->parent->left) {
        y->parent->left = x;
    }
    else {
        y->parent->right = x;
    }
    if (y != z) { //y是z的后继，关键字替换
        z->value = y->value;
    }
    return y; //返回删除的结点
}

int main(void)
{
    treeNode *n0 = new treeNode(5);
    treeNode *n1 = new treeNode(3);
    treeNode *n2 = new treeNode(7);
    treeNode *n3 = new treeNode(2);
    treeNode *n4 = new treeNode(5);
    treeNode *n5 = new treeNode(8);
    
    root = n0;
    n0->left   = n1; n0->right  = n2;
    n1->parent = n0; n5->parent = n2;
    n1->left   = n3; n1->right  = n4;
    n2->parent = n0; n2->right  = n5;
    n3->parent = n1; n4->parent = n1;
    
    cout << "InOrder: " << endl;
    inOrderTreeWalk(n0);
    cout << endl;
    
    cout << "Insert: " << endl;
    treeNode *n6 = new treeNode(10);
    treeInsert(n6);
    inOrderTreeWalk(n0);
    cout << endl;
    
    cout << "After delete: " << endl;
    treeDelete(n5);
    inOrderTreeWalk(n0);
    cout << endl;
    
    cout << "Find it: " << treeSearch(n0, 2)->value << endl;
    cout << "Tree MaxMum: "    << treeMaxMum(n0)->value << endl;
    cout << "Tree MiniMum: "   << treeMiniMum(n0)->value << endl;
    cout << "It's successor: " << treeSuccessor(n0)->value << endl;
    cout << "Iterative find it: " << iterativeTreeSearch(n0, 2)->value << endl;
}
