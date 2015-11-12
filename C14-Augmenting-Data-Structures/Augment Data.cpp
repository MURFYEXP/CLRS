#include <iostream>
using namespace std;

enum color_t { //使用枚举表示结点颜色
    RED = 0,
    BLACK = 1
};

struct treeNode
{
    int value;
    int size;
    color_t color;
    treeNode *parent;
    treeNode *left, *right;
    //struct内也使用构造函数
    treeNode() {}
    treeNode(int x): value(x), parent(NULL),
    left(NULL), right(NULL) {}
};
treeNode *root;
treeNode *nil;

//中序遍历二叉查找树
void inOrderTreeWalk(treeNode *x)
{
    if (x == NULL) { //添加
        return;
    }
    if (x != nil) { //递归出口
        inOrderTreeWalk(x->left);
        cout << x->value << endl;
        inOrderTreeWalk(x->right);
        //后序得到树中结点的size
        x->size = x->left->size + x->right->size + 1;
    }
}

//左旋,只改变指针
/*--------------------------
 |    x              y
 |   / \    ==>     / \
 |   a  y          x   c
 |     / \        / \
 |     b  c      a   b
 ---------------------------*/
treeNode * leftRotate(treeNode *T, treeNode *x)
{
    treeNode *y = x->right;
    //首先把儿子送过去安定好
    x->right = y->left;   //你是我儿子
    y->left->parent = x;  //我是你爹
    
    //自己过去，听新妈的安排安顿下来
    y->parent = x->parent;
    if (x->parent == nil) { //x为根结点
        root = y; //更新root
    }
    else if (x == x->parent->left) {
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }
    
    //上位，快叫爸爸
    y->left = x;   //你是我儿子
    x->parent = y; //我是你爹
    
    y->size = x->size;
    x->size = x->left->size + x->right->size + 1;
    return root;
}

//二、右旋
/*--------------------------
 |    x              y
 |   / \    <==     / \
 |   a  y          x   c
 |     / \        / \
 |     b  c      a   b
 ---------------------------*/
treeNode *rightRotate(treeNode *T, treeNode *x)
{
    treeNode *y = x->left; //改动！！！
    //首先把儿子送过去安定好
    x->left = y->right;   //你是我儿子 改动！！！
    y->right->parent = x;  //我是你爹
    
    //自己过去，听新妈的安排安顿下来
    y->parent = x->parent;
    if (x->parent == nil) { //x为根结点
        root = y; //更新root
    }
    else if (x == x->parent->left) {
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }
    
    //上位，快叫爸爸
    y->right = x;   //你是我儿子  改动！！！
    x->parent = y;  //我是你爹
    
    y->size = x->size;
    x->size = x->left->size + x->right->size + 1;
    return root;
}

void rbInsertFixup(treeNode *T, treeNode *z)
{
    //当z的父结点为红时，进入结点
    while (z->parent->color == RED)
    {
        //确定p[z]是左孩子还是右孩子,左孩子时
        if (z->parent == z->parent->parent->left)
        {
            treeNode *y = z->parent->parent->right;
            if (y->color == RED)
            {
                //情况1, 2-3-4树：左右红链接，翻转改变颜色 对应==》 红黑树：z的叔叔结点颜色为红
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED; //z的祖父颜色一定为黑，由黑变红
                z = z->parent->parent; // 红链上移 z的祖父为新的z,跳出
            }
            //情况2, 2-3-4树：出现右红链接，左旋转 对应==》 红黑树：z的叔叔结点颜色为黑,z为右孩子
            else
            {
                if (z == z->parent->right)
                {
                    z = z->parent;    //z的位置上移一位
                    leftRotate(T, z); //z的位置下降一位
                }
                //情况3, 2-3-4树：出现两个左红链接，右旋+翻转改变颜色操作 对应==》 红黑树： z的叔叔结点颜色为黑,z为左孩子
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(T, z->parent->parent);
            }
        }
        //p[z]是右孩子时，left与right互换即可，原理同上
        else
        {
            treeNode *y = z->parent->parent->left;
            if (y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->left)
                {
                    z = z->parent;
                    rightRotate(T, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(T, z->parent->parent);
            }
        }
    }
    //循环迭代后，根结点颜色可能为红
    root->color = BLACK;  //改动！！！！
}

//插入,三种情况
void rbTreeInsert(treeNode *T, treeNode *z)
{
    treeNode *x = root;
    treeNode *y = nil;
    while (x != nil) { //寻找合适的位置
        y = x; //y用来记录位置
        if (z->value > x->value) {
            x = x->right;
        }
        else x = x->left;
    }
    z->parent = y; //结点z插入查找树
    if (y == nil) {
        root = z; //边界情况，查找树为空树
    }
    else if (z->value > y->value)
    {
        y->right = z;
    }
    else {
        y->left = z;
    }
    z->left  = nil; //设置插入元素
    z->right = nil;
    z->color = RED; //将z结点着色为红结点
    
    rbInsertFixup(T, z); //调整红黑树结构
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

//后继
treeNode *treeSuccessor(treeNode *x)
{
    if (x->right != nil) { //x拥有右结点
        return treeMiniMum(x->right); //右子树最左结点
    }
    treeNode *y = x->parent;
    //x为y的右结点，从x向上查找，只到成为某结点的左结点
    while (y != nil && x == y->right) { //x没有右结点
        x = y; //更新x， 更新y
        y = y->parent;
    }
    return y;
}

void rbDeleteFixup(treeNode *T, treeNode *x)
{
    //当x不为根结点，且x的颜色为黑时，进入循环
    while (x != root && x->color == BLACK)
    {
        if (x == x->parent->left)
        {
            treeNode *w = x->parent->right;
            //情况1，w结点为红结点
            if (w->color == RED) {
                w->color = BLACK; //w结点由红变黑
                x->parent->color = RED;  //x->parent->color一定为黑!!!
                leftRotate(T, x->parent); //这事我管不了，将情况1转换成2，3，4作处理，并不能解决实质性问题
                w = x->parent->right; //由于左旋转，结构的变化，更新w
            }
            //情况2，w结点的孩子全为黑，指针上移，无旋转，循环唯一重复的地方，移置红结点后，找到替死鬼，将其变黑，恢复原状，即可退出
            if (w->left->color == BLACK &&
                w->right->color == BLACK)
            {
                //要使左右黑高度相同，左子树黑高度，要么+1，要么-1
                w->color = RED; //w结点由黑变红，如果由1到2，循环结束
                x = x->parent; //x上移一位
            }
            //情况3，w结点的右孩子为黑结点，左孩子为红色，将情况3转换成4作处理，改变下就可以用一个操作了，想想都高效，不用麻烦自己搞了
            else
            {
                if(w->right->color == BLACK)
                {
                    w->left->color = BLACK; //w与左孩子颜色交换，黑变红
                    w->color = RED; //这事我管不了，红黑黑情况1，并不能解决实质性问题
                    rightRotate(T, w);
                    w = x->parent->right; //由于右旋转，结构的变化，更新w
                }
                //情况4，w结点的右孩子是红色的
                w->color = x->parent->color; //w要成为新的子树的根，与原根颜色一致，则保证了旋转变化后，左右子树的黑高度，叔变成了母亲的颜色
                x->parent->color = BLACK; //使左子树的黑高度+1，成功恢复，母亲很生气，气黑了脸
                w->right->color = BLACK; //保证右孩子的黑高度，报复叔，让他儿子也变黑了
                leftRotate(T, x->parent); // 叔怒了，左旋自己上位了
                x = root; //最后结束整个游戏
            }
        }
        else //left与right互换即可，原理同上
        {
            treeNode *w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(T, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK &&
                w->left->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if(w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(T, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(T, x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}

//删除,3种情况的组织
treeNode *rbTreeDelete(treeNode *T, treeNode *z)
{
    treeNode *y, *x;
    //y为要删除的元素，x为y的孩子，y最多一个孩子
    if (z->left == nil || z->right == nil) {
        y = z; //z最多一个孩子，删除z
    }
    else {
        y = treeSuccessor(z); //两孩子，删除z的后继
    }
    //修改y的父结点，和x的指针，删除y结点
    if (y->left != nil) {
        x = y->left;
    }
    else {
        x = y->right;
    }
    x->parent = y->parent; //x可以是哨兵
    //修改y的父节点,使用指针时，提醒null的边界判断
    if (y->parent == nil) { //y为根结点时
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
    if (y->color == BLACK) { //删除的是黑结点
        rbDeleteFixup(T, x); //调整树结构
    }
    return y; //返回删除的结点
}

//返回T中第i小结点
treeNode *OS_Slect(treeNode *x, int i)
{
    int r = x->left->size + 1; //小于等于r的结点
    if (r == i) {
        return x;
    }
    else if (i < r) { //x的左孩子
        return OS_Slect(x->left, i);
    }
    else { //x的右孩子
        return OS_Slect(x->right, i - r);
    }
}

//确定一个元素的秩
int OS_Rank(treeNode *T, treeNode *x)
{
    int r = x->left->size + 1;
    treeNode *y = x;
    while (y != root) {
        if (y == y->parent->right) {
            r = r + y->parent->left->size + 1;
        }
        y = y->parent;
    }
    return r;
}

int main(void)
{
    treeNode *n0 = new treeNode(1);
    treeNode *n1 = new treeNode(5);
    treeNode *n2 = new treeNode(9);
    treeNode *n3 = new treeNode(15);
    treeNode *n4 = new treeNode(18);
    treeNode *n5 = new treeNode(22);
    treeNode *t = new treeNode; //指针t打酱油，可以去掉
    treeNode *nill = new treeNode(-1);
    nill->size = 0; //nill结点size为0
    nil = nill; root = nil;  //设置nil哨兵 root应初始化为nil，且root会在函数里改动。
    nil->color = BLACK; //新增
    
    rbTreeInsert(t, n0);
    rbTreeInsert(t, n1);
    rbTreeInsert(t, n2);
    rbTreeInsert(t, n3);
    rbTreeInsert(t, n4);
    rbTreeInsert(t, n5);
    cout << "After Insert: " << endl;
    inOrderTreeWalk(root);
    cout << "Tree Size: " << root->size << endl;
    cout << "The 4th Node: " << OS_Slect(root, 4)->value << endl;
    cout << "The n3's Rank: " << OS_Rank(t, n3)<< endl;
}




