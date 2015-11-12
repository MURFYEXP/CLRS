//迭代版返回T中第i小结点
treeNode *OS_Slect1(treeNode *x, int i)
{
    int r = x->left->size + 1; //小于等于r的结点
    while (r != i && x != NULL) {
        if (i < r) { //x的左孩子
            x = x->left;
        }
        else { //x的右孩子
            x = x->right;
            i = i - r;
        }
    }
    return x;
}

//递归版确定一个元素的秩
int OS_Rank1(treeNode *T, treeNode *x)
{
    int r = T->left->size + 1;
    if (T == x) {
        return r;
    }
    //递归向下查找（迭代版向上直到root结点），直到找到x结点
    else if (T->value > x->value)
    {
        return OS_Rank1(T->left, x);
    }
    else
    {
        //递归一次计算一次此状态的rank值
        return r + OS_Rank1(T->right, x);
    }
}