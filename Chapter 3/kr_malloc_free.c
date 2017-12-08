typedef double Align;
union Head
{
    struct Head
    {
        struct Head *next;
        int size;
    }s;
    Align ch;
};
typedef union Head Head;
Head freep=NULL;
Head base;
void* malloc(int nbytes)
{
    int size=(nbytes+sizeof(Head)-1)/sizeof(Head)+1;
    Head *prevp,*p;
    if((prevp=freep)==NULL)
    {
        base.s.size=0;
        base.s.next=freep=prevp=&base;
    }
    for(p=prevp->s.next;;prevp=p,p=p->s.next)
    {
        if(p->s.size>=size)
        {
            if(p->s.size==size)
                prevp->s.next=p->s.next;
            else
            {
                p->s.size-=size;
                p+=p->s.size;
                p->s.size=size;
            }
            freep=prevp;
            return (void*)(p+1);
        }
        if(p==freep)
            if((p=morecore(size))==NULL)
                return NULL;

    }
}
#define MINIMAL 1024
void* morecore(int size)
{
    char *cp;
    Head *up;
    if(size<MINIMAL)
        size=MINIMAL;
    cp=sbrk(sizeof(Head)*size);
    if(cp==(char*)-1)
        return NULL;
    up=(Head*)cp;
    up->s.size=size;
    free((void*)(up+1));
    return freep;
}
void free(void *pt)
{
    Head *bp=(Head*)pt-1;
    Head *p;
    for(p=freep;!(bp>p&&bp<p->s.next);p=p->s.next)
        if(p>=p->s.next&&(bp>p||bp<p->s.next))
            break;
    if(bp+bp->s.size==p->s.next)
    {
        bp->s.size+=p->s.next->s.size;
        bp->s.next=p->s.next->s.next;
    }
    else
        bp->s.next=p->s.next;
    if(p+p->s.size==bp)
    {
        p->s.size+=bp->s.size;
        p->s.next=bp->s.next;
    }
    else
        p->s.next=bp;
    freep=p;
}
