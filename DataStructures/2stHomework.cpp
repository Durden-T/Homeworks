//2
bool pushS1(Stack &s, ElemType val)
{
    if (s.top1 == s.top2 + 1)
        return failed;
    *s.top1++ = val;
    return success;
}

bool pushS2(Stack &s, ElemType val)
{
    if (s.top1 == s.top2 + 1)
        return failed;
    *s.top2-- = val;
    return success;
}

ElemType popS1(Stack &s, ElemType val)
{
    if (s.top1 == s.base)
        return failed;
    return *--s.top1;
}

ElemType popS2(Stack &s, ElemType val)
{
    if (s.top2 == s.base + s.stackSize - 1)
        return failed;
    return *++s.top2;
}

//3
//rear length
bool isFull(Queue &q)
{
    return q.length == MAXQSIZE;
}

bool enQueue(Queue &q, ElemType val)
{
    if (isFull(q))
        return failed;
    if (q.rear == q.base + MAXQSIZE)
        q.rear = q.base;
    *q.rear++ = val;
    ++q.length;
    return success;
}

int deQueue(Queue &q)
{
    if (q.length == EMPTY)
        return failed;
    ElemType ans;
    if (q.rear - q.base < q.length)
        ans = *(q.base + MAXQSIZE - Q.length + 1);
    else
        ans = *(q.rear - q.length);
    --q.length;
    return ans;
}