
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define N 200000+5
#define M 400000+5
const int inf = 2100000000+5;
using namespace std;
 
int head[N],fa[N],top[N],w[N];
int from[N],val[N],depth[N],m,sz;
int u[N],v[N],dis[N],size[N],n,s;
bool mark[M],in[N];
 
char getc()
{
    static const int LEN = 1<<15;
    static char buf[LEN],*S=buf,*T=buf;
    if(S == T)
    {
        T = (S=buf)+fread(buf,1,LEN,stdin);
        if(S == T)return EOF;
    }
    return *S++;
}
   
int read()
{
    static char ch;
    static int D;
    while(!isdigit(ch=getc()));
    for(D=ch-'0'; isdigit(ch=getc());)
        D=(D<<3)+(D<<1)+(ch-'0');
    return D;
}
 
struct graph
{
    int next,to,val;
    graph () {}
    graph (int _next,int _to,int _val)
    :next(_next),to(_to),val(_val){}
}edge[M];
 
inline void add(int x,int y,int z)
{
    static int cnt = 0;
    edge[++cnt] = graph(head[x],y,z);
    head[x] = cnt;
    edge[++cnt] = graph(head[y],x,z);
    head[y] = cnt;
}
 
namespace Heap
{
    int h[N],tot;
    int pos[N];
    void up(int x)
    {
        if(x==1)
            return;
        while(h[x]<h[x>>1])
        {
            if(x==1)break;
            swap(h[x],h[x>>1]);
            swap(pos[x],pos[x>>1]);
            x>>=1;
        }
    }
    void push(int x,int y)
    {
        h[++tot]=x;
        pos[tot]=y;
        up(tot);
    }
    int pop()
    {
        swap(h[1],h[tot]);
        swap(pos[1],pos[tot--]);
        int i=1;
        while((((i<<1)<=tot)&&(h[i]>h[i<<1]))||(((i<<1)+1<=tot)&&(h[i]>h[(i<<1)+1])))
        {
            if((i<<1)+1>tot)
            {
                swap(h[i],h[i<<1]);
                swap(pos[i],pos[i<<1]);
                i<<=1;
            }
            else
            {
                int tmp=(h[i<<1]<h[(i<<1)+1])?(i<<1):((i<<1)+1);
                swap(h[i],h[tmp]);
                swap(pos[i],pos[tmp]);
                i=tmp;
            }               
        }
        return pos[tot+1];    
    }
    bool empty()
    {
        return tot == 0;
    }
}
 
void dij()
{
    for(int i=1;i<=n;++i)
        dis[i]=inf;
    dis[s]=0;
    Heap :: push(0,s);
    while(!Heap :: empty())
    {
        int now  = Heap :: pop();
        if(in[now])continue;
        in[now]=1;
        for(int i=head[now];i;i=edge[i].next)
        {
            if(dis[edge[i].to]>dis[now]+edge[i].val)
            {
                mark[from[edge[i].to]]=false;
                from[edge[i].to]=i;
                mark[i]=true;
                dis[edge[i].to]=dis[now]+edge[i].val;
                Heap :: push(dis[edge[i].to],edge[i].to);
            }
        }
    }
}
 
void DFS1(int x)
{
    size[x] = 1;
    for(int i=head[x] ; i; i=edge[i].next)
        if(edge[i].to!=fa[x] && mark[i])
        {
            depth[edge[i].to] = depth[x]+1;
            fa[edge[i].to] = x;
            DFS1(edge[i].to);
            size[x] += size[edge[i].to];
        }
}
 
void DFS2(int x,int chain)
{
    top[x] = chain;w[x] = ++sz;int k = 0;
    for(int i=head[x] ; i ;i=edge[i].next)
        if(edge[i].to!=fa[x]&&size[k]<size[edge[i].to] && mark[i])
            k = edge[i].to;
    if(!k)return;
    DFS2(k,chain);
    for(int i=head[x] ; i; i=edge[i].next)
        if(edge[i].to!=fa[x] && edge[i].to!=k && mark[i])
            DFS2(edge[i].to,edge[i].to);
}
 
int lca(int x,int y)
{
    while(top[x]!=top[y])
    {
        if(depth[top[x]] < depth[top[y]])
            swap(x,y);
        x=fa[top[x]];
    }
    return depth[x] < depth[y] ? x : y;
}
 
struct seg
{
    int l,r,mn,lazy;
}tr[M];
  
void build(int k,int l,int r)
{
    tr[k].l=l,tr[k].r=r,tr[k].lazy=tr[k].mn=inf;
    if(l==r)return ;
    int mid = (l+r)>>1;
    build(k<<1,l,mid);
    build(k<<1|1,mid+1,r);
}
  
inline void down(int k)
{
    if(tr[k].l==tr[k].r||tr[k].lazy==inf)
        return;
    int tmp=tr[k].lazy;
    tr[k].lazy=inf;
    tr[k<<1].lazy=min(tr[k<<1].lazy,tmp);
    tr[k<<1|1].lazy=min(tr[k<<1|1].lazy,tmp);
    tr[k<<1].mn=min(tr[k<<1].mn,tmp);
    tr[k<<1|1].mn=min(tr[k<<1|1].mn,tmp);
}
  
int ask(int k,int pos)
{
    down(k);
    if(tr[k].l==tr[k].r&&tr[k].l==pos)
        return tr[k].mn;
    int mid = (tr[k].l+tr[k].r)>>1;
    if(pos <= mid)
        return ask(k<<1,pos);
    else return ask(k<<1|1,pos);
}
  
void change(int k,int l,int r,int c)
{
    down(k);
    if(l==tr[k].l && r==tr[k].r)
    {
        tr[k].lazy = min(tr[k].lazy,c);
        if(l==r)
            tr[k].mn= min(tr[k].mn,c);
        return;
    }
    int mid = (tr[k].l+tr[k].r)>>1;
    if(r<=mid)
        change(k<<1,l,r,c);
    else if(l>mid)
        change(k<<1|1,l,r,c);
    else change(k<<1,l,mid,c),change(k<<1|1,mid+1,r,c);
}
 
void solvechange(int x,int y,int c)
{
    while(top[x]!=top[y])
    {
        if(depth[top[x]] < depth[top[y]])swap(x,y);
        change(1,w[top[x]],w[x],c);x=fa[top[x]];
    }
    if(depth[x]>depth[y])swap(x,y);
    if(w[x]!=w[y])
    change(1,w[x]+1,w[y],c);
}
  
int main()
{
    n=read(),m=read();
    s=1;
    for(int i=1;i<=m;++i)
    {
        u[i]=read(),v[i]=read(),val[i]=read();read();
        add(u[i],v[i],val[i]);
    }
    dij();
    DFS1(1);
    DFS2(1,1);
    build(1,1,n);
    for(int i=1;i<=m;++i)
    {
        int t=lca(u[i],v[i]);
        if(!mark[(i<<1)-1])solvechange(v[i],t,dis[u[i]]+dis[v[i]]+val[i]);
        if(!mark[i<<1])solvechange(u[i],t,dis[u[i]]+dis[v[i]]+val[i]);
    }
    for(int i=2;i<n;++i)
    {
        int tt=ask(1,w[i]);
        if(tt!=inf)
            printf("%d ",tt-dis[i]);
        else
            printf("-1 ");
    }
    int tt = ask(1,w[n]);
    if(tt!=inf)
    	cout<<tt-dis[n];
    else printf("-1");
}
 
