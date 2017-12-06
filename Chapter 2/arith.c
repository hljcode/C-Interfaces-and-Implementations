#include"arith.h"
int Arith_max(int x,int y)
{
    return x>y?x:y;
}
int Arith_min(int x,int y)
{
    return x<y?x:y;
}
int Arith_div(int x,int y)
{
    if((-13/5==-2)&&x<0!=y<0)//division turncates toward 0 and x,y have different signs
        return x/y-1;
    else
        return x/y;
}
int Arith_mod(int x,int y)
{
    //(x/y)*y+x%y=x
    return x-y*Arith_div(x,y);
}
int Arith_floor(int x,int y)
{
    return Arith_div(x,y);
}
int Arith_ceiling(int x,int y)
{
    return Arith_div(x,y)+(x%y!=0);
}