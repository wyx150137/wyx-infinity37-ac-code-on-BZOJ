
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define min(a,b) ((a)<(b)?(a):(b))
#define N 100000+5
#define M 200000+5
using namespace std;
int size[N],n,a[N],head[N];
long long f[N],g[N];
struct graph
{
    int next,to;
    long long val;
    graph () {}
    graph (int _next,int _to,long long _val)
    :next(_next),to(_to),val(_val){}
}edge[M];
bool flag=false;
long long ans=0x3f3f3f3f3f3fll;
inline void add(int x,int y,long long val)
{
    static int cnt = 0;
    edge[++cnt]=graph(head[x],y,val);
    head[x]=cnt;
    edge[++cnt]=graph(head[y],x,val);
    head[y]=cnt;
}
inline int read()
{
    int x = 0, f = 1; char ch = getchar();
    while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
    return x * f;
}
long long sum;
void DFS(int x,int fa)
{
    size[x]=a[x];
    f[x]=0;
    for(int i=head[x];i;i=edge[i].next)
        if(edge[i].to^fa)
        {
            DFS(edge[i].to,x);
            size[x]+=size[edge[i].to];
            f[x]+=(long long)size[edge[i].to]*edge[i].val+f[edge[i].to];
        }
}
void reDFS(int x,int fa,int val)
{
    if(x!=1)
        g[x]=g[fa]+(sum-2*size[x])*(val);
    else
        g[x]=f[x];
    for(int i=head[x];i;i=edge[i].next)
        if(edge[i].to^fa)
            reDFS(edge[i].to,x,edge[i].val);
}
int main()
{   
    //freopen("meet.in", "r", stdin);
    //freopen("meet.out", "w", stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
        a[i]=read();
    for(int i=1;i<n;++i)
    {
        int tmp1=read(),tmp2=read(),tmp3=read();
        add(tmp1,tmp2,tmp3);
    }
    DFS(1,-1);
    ans=f[1];
    sum=size[1];
    reDFS(1,-1,0);
    sort(g+1,g+n+1);
    ans=g[1];
    cout<<ans;
}
 
