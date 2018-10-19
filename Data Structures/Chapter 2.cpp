void deleteRange(sqList L, elemType k1, elemType k2)
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
listNode *createList(elemType A[], int size)
{
    if (size <= 0)
        return nullptr;
    listNode *head = new listNode, *cur = head;
    head->next = nullptr;
    for (int i = 0; i < size; ++i)
    {
        listNode *t = new listNode;
        t->data = A[i];
        cur->next = t;
        cur = cur->next;
    }
    cur->next = nullptr;
    return head;
}
//3
void reverseInPlace(elemType A[], int arraySize, int n)
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