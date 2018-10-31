//1
void deleteRange(SqList L, ElemType k1, ElemType k2)
{
    int start = 0, end = 0;
    for (int i = 0; i < L.length && !end; ++i)
        if (L.elem[i] > k1 && !start)
            start = i;
        else if (L.elem[i] >= k2)
            end = i;
    int size = L.length - end + start;
    while (end < L.length)
        L.elem[start++] = L.elem[end++];
    L.length = size;
}
//2
ListNode *createList(ElemType A[], int size)
{
    if (size <= 0)
        return nullptr;
    ListNode *head = malloc(sizeof(ListNode)), *cur = head;
    for (int i = 0; i < size; ++i)
    {
        ListNode *t = malloc(sizeof(ListNode));
        t->data = A[i];
        cur->next = t;
        cur = cur->next;
    }
    cur->next = nullptr;
    return head;
}
//3
void reverseInPlace(ElemType A[], int arraySize, int n)
{
    if (n > arraySize)
        n = arraySize;
    int i = 0, j = n - 1;
    while (i < j)
    {
        int t = A[i];
        A[i] = A[j];
        A[j] = t;
        ++i;
        --j;
    }
}