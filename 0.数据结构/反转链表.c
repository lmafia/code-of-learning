typedef struct list_node
{
    int data;
    struct list_node *next;
}list_node, *list;

ListNode *reverse_list(ListNode *pHead)
{
    if(!pHead) /*空结点传入*/
        return NULL;

    if(!pHead->next) /*只有一个结点传入*/
        return pHead;

                     /*多个结点传入*/
    ListNode *p_rhead = NULL; /*来指向反转链表*/
    ListNode *p_node = pHead; /*当前结点*/
    ListNode *p_pre = NULL; /*前驱结点*/
    while(p_node != NULL)
    {
        ListNode *p_next = p_node->next; /*先把后继保存了*/
        if(p_next == NULL)          /*走到旧链表的最后一个结点，作为新的头结点*/
            p_rhead = p_node;
        p_node->next = p_pre;        /*当前结点的后继指向前驱*/
        p_pre = p_node;              /*当前结点作为前驱保存起来，给下次用*/
        p_node = p_next;             /*把当前结点移到后继结点*/
    }
    return p_rhead;
}

ListNode *reverse_list2(ListNode *pHead)
{
	if(pHead == NULL || pHead->next == NULL)
		return pHead;
	ListNode *p_now = pHead;
	ListNode *re_pHead = NULL;
	while(p_now != NULL)
	{
		ListNode *p_next = p_now->next;
		p_now->next = re_pHead;
		re_pHead = p_now;
		p_now = p_next;
	}
	return re_pHead;
}

ListNode *reverse_list3(ListNode *pHead)
{
	if(pHead == NULL || pHead->next == NULL)
		return pHead;
	ListNode *re_pHead = reverse_list3(pHead->next);
	pHead->next->next = pHead;
	pHead->next = NULL;
	return re_pHead;
}