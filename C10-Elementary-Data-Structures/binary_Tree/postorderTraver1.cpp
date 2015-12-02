void PostOrder_Nonrecursive1(BiTree T)  // 后序遍历的非递归
{
    stack<BiTree> S;
    BiTree curr = T ;           // 指向当前要检查的节点
    BiTree previsited = NULL;    // 指向前一个被访问的节点
    while(curr != NULL || !S.empty())  // 栈空时结束
    {
        while(curr != NULL)            // 一直向左走直到为空
        {
            S.push(curr);
            curr = curr->lchild;
        }
        curr = S.top();
        // 当前节点的右孩子如果为空或者已经被访问，则访问当前节点
        if(curr->rchild == NULL || curr->rchild == previsited)
        {
            cout<<curr->data<<"  ";
            previsited = curr;
            S.pop();
            curr = NULL;
        }
        else
            curr = curr->rchild;      // 否则访问右孩子
    }
}