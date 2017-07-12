
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define N 600+5
#define M 90000
int n,m,fa[N];
int head[N];
inline int read()
{
    int x = 0, f = 1; char ch = getchar();
    while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
    return x * f;
}
struct graph
{
    int from,to,val;
    bool operator<(const graph &z)const
    {return val<z.val;}
    void  r()
    {from=read(),to=read(),val=read();}
}edge[M];
int getfa(int x)
{ return(fa[x]^x?fa[x]=getfa(fa[x]):fa[x]); }
void init()
{   
    for(int i=1;i<=2*n;++i)
        fa[i]=i;
}
int main()
{
    n=read();m=read();
    printf("%d ",n-1);
    for(int i=1;i<=m;++i)
        edge[i].r();
    sort(edge+1,edge+m+1);
    int max_val=0;
    init();
    for(int i=1,j=n;j>1;++i)
    {
        int f1=getfa(edge[i].from),f2=getfa(edge[i].to);
        if(f1^f2)
            max_val=edge[i].val,fa[f1]=f2,--j;
    }
    cout<<max_val;
}
