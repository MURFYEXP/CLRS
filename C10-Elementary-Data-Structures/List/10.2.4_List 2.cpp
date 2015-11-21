//对k下手！！！每次迭代省去对x!=nil的判断
list *listSearch(list *l, int k)
{
    //nil->next为头结点
    list *x = nil->next;
    
    nil->key = k;
    while (k != x->key){  //修改 x != nil
        x = x->next;
    }
    if (x == nil) {
        return nullptr;
    }
    return x;
}
