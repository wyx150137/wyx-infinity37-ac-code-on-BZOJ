
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define N 100000+5
#define M 400000+5
const int inf = 0x7fffff;
using namespace std;
 
int size[N],n;
int top[N],w[N],sz;
int depth[N],fa[N];
int last[N],head[N];
int val[N];
 
inline int read()
{
    int x=0,f=1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
    while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch - '0';ch = getchar();}
    return x*f;
}
 
struct graph
{
    int next,to;
    graph () {}
    graph (int _next,int _to)
    :next(_next),to(_to){}
}edge[M];
 
inline void add(int x,int y)
{
    static int cnt = 0;
    edge[++cnt] = graph(head[x],y);
    head[x] = cnt;
    edge[++cnt] = graph(head[y],x);
    head[y] = cnt;
}
 
void DFS1(int x)
{
    size[x] = 1;
    for(int i=head[x] ; i ; i=edge[i].next)
        if(edge[i].to!=fa[x])
        {
            depth[edge[i].to] = depth[x] +1;
            DFS1(edge[i].to);
            size[x] += size[edge[i].to];
        }
}
 
void DFS2(int x,int chain)
{
    top[x] = chain;w[x] = last[x] = ++sz;
    int k = 0;
    for(int i=head[x] ; i ; i=edge[i].next)
        if(edge[i].to!=fa[x] && size[k] < size[edge[i].to])
            k = edge[i].to;
    if(!k)return;
    DFS2(k,chain);last[x] = last[k];
    for(int i=head[x];i;i=edge[i].next)
        if(edge[i].to!=fa[x]&&edge[i].to!=k)
            DFS2(edge[i].to,edge[i].to),last[x] = last[edge[i].to];
}
 
int tr[M];
 
void change(int k,int l,int r,int pos,int x)
{
    if(l==r) {tr[k]=x;return;}
    int mid = (l+r)>>1;
    if(pos<=mid)change(k<<1,l,mid,pos,x);
    else change(k<<1|1,mid+1,r,pos,x);
    tr[k] = min(tr[k<<1],tr[k<<1|1]);
}
 
int ask(int k,int l,int r,int x,int y)
{
    if(x==l && r==y)return tr[k];
    int mid = (l+r)>>1;
    if(y<=mid)return ask(k<<1,l,mid,x,y);
    else if(x>mid)return ask(k<<1|1,mid+1,r,x,y);
    else return min(ask(k<<1,l,mid,x,mid),ask(k<<1|1,mid+1,r,mid+1,y));
}
 
int lca(int x,int y)
{
    while(top[x]!=top[y])
    {
        if(depth[top[x]] < depth[top[y]])swap(x,y);
        x=fa[top[x]];
    }
    return depth[x] < depth[y] ? x : y;
}
 
int main()
{
    n = read();
    int Q=read();
    int root = 0;
    memset(tr,0x3f,sizeof tr);
    for(int i=1;i<=n;++i)
    {
        int x=read(),y=read();
        if(!x) x = root = i;
        fa[i] = x;
        add(i,fa[i]);
        val[i] = y;
    }   
    DFS1(root);
    DFS2(root,root);
    for(int i=1;i<=n;++i)
        change(1,1,n,w[i],val[i]);
    while(Q--)
    {
        char ch[10];
        scanf("%s",ch);
        if(ch[0] == 'V')
        {   
            int x= read(),tt = read();
            change(1,1,n,w[x],tt);
        }
        else if(ch[0]=='E')     
            root = read();
        else
        {
            int x = read();
            if(x==root)
            {
                printf("%d\n",tr[1]);
                continue;
            }
            int tt = lca(x,root);
            if(tt^x)
                printf("%d\n",ask(1,1,n,w[x],last[x]));
            else
            {
                int k = 0;
                for(int i=head[x] ; i; i=edge[i].next)
                    if(w[root] >= w[edge[i].to] &&w[root] <= last[edge[i].to] && edge[i].to!=fa[x])
                        k = edge[i].to;
                int ans = inf;
                if(w[k] >= 2)
                    ans = min (ans,ask(1,1,n,1,w[k]-1));
                if(last[k] < n)
                    ans = min(ans,ask(1,1,n,last[k]+1,n));
                printf("%d\n",ans);
            }
        }   
    }
}
