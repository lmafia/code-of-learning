/**
*  名称：查找二叉树
*  性质:当二叉树非空
*  1.非空左子树的所有键值小于其根结点的键值
*  2.非空右子树的所有键值大于其根结点的键值
*  3.左右子树都是二叉搜索树
**/

/**
* Find x：找目标值x
* 从根节点开始，如果为空就返回NULL，
* 若非空，就和x比较：
* 1.x小于当前根结点键值,往左子树找
* 2.x大于当前根结点键值,往右子树找
* 3.x等于当前键值,则搜索完成
**/
position_t find(elem_t x, bin_tree bst)
{
    while(bst)
    {
        if(x < bst->data)
            bst = bst->left_child;
        else if(x > bst->data)
            bst = bst->right_child;
        else
            return bst;
    }
    return NULL;
}

/**
*Find_min：找最小元素
* 根据查找树的结构,最小元素一定在最左的分支的最左结点
**/
position_t find_min(bin_tree bst)/*一直搜索直到找到最左结点*/
{
/*递归方法*/
//    if(!bst) /*空树就返回NULL*/
//        return NULL;
//    else if (!bst->left_child) /*是最左分支的最左结点就结束并返回*/
//        return bst;
//    else
//        return find_min(bst->left_child);/*还有左子树就继续搜索*/
/*迭代方法*/
    if(!bst)
        return NULL;
    while(bst->left_child)
    {
        bst = bst->left_child;
    }
    return bst;
}


/**
*Find_max:找最大元素
* 根据查找树的结构,最大元素一定在最右的分支的最右结点
**/
position_t find_max(bin_tree bst) /*一直搜索直到找到最右结点*/
{
/*递归方法*/
//    if(!bst) /*空树就返回NULL*/
//        return NULL;
//    else if (!bst->right_child) /*是最右分支的最右结点就结束并返回*/
//        return bst;
//    else
//        return find_min(bst->right_child);/*还有右子树就继续搜索*/
/*迭代方法*/
    if(!bst)
        return NULL;
    while(bst->right_child)
    {
        bst = bst->right_child;
    }
    return bst;
}

/**
* insert:要按照搜索树的规则,插入元素
* 可以在find函数基础上修改
**/
bin_tree insert(elem_t item, bin_tree bst)
{
    if(!bst) /*树为空或者说一个结点的不存在，那就要插入一个元素，因为要插入只能作为叶子*/
             /*其实二叉搜索树是不唯一，其实一样的数据，按照不同的插入顺序会导致形成不同的树*/
    {
        bst = (bin_tree)malloc(sizeof(struct tree_node));/**/
        bst->data = item;
        bst->left_child = bst->right_child = NULL;
    }
    else /*不为空，肯定要按照规则插入，那么就需要递归查找添加*/
    {
        if(item < bst->data) /*插入左子树*/
            bst->left_child = insert(item, bst->left_child);
        else /*插入到右子树*/
            bst->right_child = insert(item, bst->right_child);
    }
    return bst;
}

/**
* delete:根据规则删除结点。分为2种情况：
* 1.结点只有一棵子树,就把唯一的子结点代替自己
* 2.结点有2棵子树的。要用右子树的最小元素或者左子树的最大元素代替自己
**/
bin_tree delete(elem_t item, bin_tree bst)
{
    position_t tmp;
    if(!bst)
        printf("null\n");
    else if (item < bst->data) /*与find一样,递归搜索要删的结点*/
        bst->left_child = delete(item, bst->left_child);
    else if (item > bst->data)
        bst->right_child = delete(item, bst->right_child);
    else /*找到目标结点了*/
    {
        if(bst->left_child && bst->right_child) /*结点的左右子树都不为空*/
        {
            tmp = find_min(bst->right_child); /*找到右子树中最小的，btw:这里也可以找到左子树中最大的*/
            bst->data = tmp->data;            /*把上面搜到的值填充要删的结点*/
            bst->right_child = delete(bst->data, bst->right);/*把右子树最小的结点删除掉，*/
                                                           /*右子树中最小的结点一定只有右子树没有左子树的*/
        }
        else/*存在空子树*/
        {
            tmp = bst;
            if(!bst->left_child) /*左子树为空，即1.右子树不为空，就把右子代替自己*/
                                /*                2.右子树为空，就说明是目标结点是叶子，把NULL填充也一样*/
                bst = bst->right;
            else if(!bst->right_child)/*上同*/
                bst = bst->left_child;
        }
        free(tmp);
    }
    return bst;
}
