
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define inf 0x3f3f3f
#define min(a,b) ((a)<(b)?(a):(b))
#define N 10000+5
#define M 20000+5
using namespace std;
int head[N],f[N],g[N],h[N],n;
struct graph 
{   
    int next,to;
    graph () {}
    graph (int _next,int _to)
    :next(_next),to(_to){}
}edge[M];
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0' || ch>'9'){if(ch=='-1')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
    return x*f;
}
inline void add(int x,int y)
{
    static int cnt = 0;
    edge[++cnt]=graph(head[x],y);
    head[x]=cnt;
    edge[++cnt]=graph(head[y],x);
    head[y]=cnt;
}
void DFS(int x,int fa)
{
    f[x]=1;g[x]=0;
    int MIN=inf;
    for(int i=head[x];i;i=edge[i].next)
        if(edge[i].to ^ fa)
        {
            DFS(edge[i].to,x);
            f[x]+=min(f[edge[i].to],min(g[edge[i].to],h[edge[i].to]));
            g[x]+=min(f[edge[i].to],g[edge[i].to]);
            MIN=min(MIN,f[edge[i].to]-min(f[edge[i].to],g[edge[i].to]));
            h[x]+=g[edge[i].to];
        }
    g[x]+=MIN;
}
int main()
{
    cin>>n;
    for(int i=1;i<n;++i)
    {
        int tmp1=read(),tmp2=read();
        add(tmp1,tmp2);
    }
    DFS(1,-1);
    cout<<min(f[1],g[1]);
}
