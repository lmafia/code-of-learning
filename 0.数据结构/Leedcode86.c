
if (head == NULL)
{
    return NULL;
}
if (head->next == NULL)
{
    return head;
}
struct ListNode* pNode = head;
struct ListNode* pLarge = NULL;
struct ListNode* pLow = NULL;
struct ListNode* pPre = NULL;
struct ListNode* tail = NULL;
struct ListNode* Ltail = NULL;

while (pNode != NULL )
{
    struct ListNode *pNext = pNode->next;
    if (pNode->val < x)
    {
        if (pLow == NULL)
        {
            pLow = pNode;
            tail = pLow;
            tail->next = NULL;
            pNode = pNext;
        }
        else
        {
            if (pPre)
            {
                pPre->next = pNext;
            }
            tail->next = pNode;
            tail = pNode;
            tail->next = NULL;
            pNode = pNext;
        }

    }
    else
    {
        if (pLarge == NULL)
        {
            pLarge = pNode;
        }
        pPre = pNode;

        pNode = pNext;
        Ltail = pNode;
    }
}
Ltail->next = NULL;
if (pLow == NULL)
{
    return pLarge;
}
tail->next = pLarge;
return pLow;

