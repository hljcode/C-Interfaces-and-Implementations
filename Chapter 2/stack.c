#include"stack.h"
#include"mem.h"
#include"assert.h"
#define T Stack_T
struct T
{
    int count;
    struct elem{
        void *x;
        struct elem *link;
    }*head;
};
T Stack_new(void)
{
    T stk;
    New(stk);
    stk->count=0;
    stk->head=NULL;
    return stk;
}
int Stack_empty(T stk)
{
    assert(stk);
    return stk->count==0;
}
void Stack_push(T stk,void *x)
{
    assert(stk);
    struct elem* t;
    New(t);
    t->x=x;
    t->link=stk->head;
    stk->count++;
    stk->head=t;
}
void* Stack_pop(T stk)
{
    assert(stk);
    assert(stk->count);
    void *s;
    struct ele* t;
    t=stk->head;
    stk->head=t->link;
    s=t->x;
    stk->count--;
    Free(t);
    return s;
}
void Stack_free(T *stk)
{
    assert(stk&&*stk);
    struct elm *u,*s;
    u=(*stk)->head;
    while(u)
    {
        s=u->link;
        Free(u);
        u=s;
    }
    Free(*stk);
}