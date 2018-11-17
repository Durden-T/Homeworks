GList copyGLists(GList L)
{
    if (!L)
        return nullptr;
    auto t = new GLNode;
    if ((t->tag = L->tag) == ATOM)
        t->atom = L->atom;
    else
    {
        t->ptr.hp = copyGLists(L->ptr.hp);
        t->ptr.tp = copyGLists(L->ptr.tp);
    }
    return t;
}