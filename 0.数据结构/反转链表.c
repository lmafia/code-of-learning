typedef struct list_node
{
    int data;
    struct list_node *next;
}list_node, *list;

list reverse_list(list phead)
{
    if(!phead) /*空结点传入*/
        return NULL;

    if(!phead->next) /*只有一个结点传入*/
        return phead;

                     /*多个结点传入*/
    list p_rhead = NULL; /*来指向反转链表*/
    list p_node = phead; /*当前结点*/
    list p_pre = NULL; /*前驱结点*/
    while(p_node != NULL)
    {
        list p_next = p_node->next; /*先把后继保存了*/
        if(p_next == NULL)          /*走到旧链表的最后一个结点，作为新的头结点*/
            p_rhead = p_node;
        p_node->next = p_pre;        /*当前结点的后继指向前驱*/
        p_pre = p_node;              /*当前结点作为前驱保存起来，给下次用*/
        p_node = p_next;             /*把当前结点移到后继结点*/
    }
    return p_rhead;
}
