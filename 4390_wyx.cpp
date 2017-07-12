
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#define N 50000+5
#define M 200000+5
using namespace std;
int head[N],size[N],top[N];
int cha[N],depth[N],fa[N];
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
    int next,to;
    graph () {}
    graph (int _next,int _to)
    :next(_next),to(_to){}
}edge[M];
inline void add(int x,int y)
{
    static int cnt = 0;
    edge[++cnt] = graph(head[x],y);
    head[x]=cnt;
    edge[++cnt] = graph(head[y],x);
    head[y]=cnt;
}
void DFS1(int x)
{
    size[x]=1;
    for(int i=head[x];i;i=edge[i].next)
        if(edge[i].to!=fa[x])
        {
            depth[edge[i].to]=depth[x]+1;
            fa[edge[i].to]=x;
            DFS1(edge[i].to);
            size[x]+=size[edge[i].to];
        }
}
void DFS2(int x,int chain)
{
    top[x]=chain;
    int k = 0;
    for(int i=head[x];i;i=edge[i].next)
        if(edge[i].to!=fa[x]&&size[k]<size[edge[i].to])
            k=edge[i].to;
    if(!k)return;
    DFS2(k,chain);
    for(int i=head[x];i;i=edge[i].next)
        if(edge[i].to!=fa[x]&&edge[i].to!=k)
            DFS2(edge[i].to,edge[i].to);
}
int lca(int x,int y)
{
    while(top[x]!=top[y])
    {
        if(depth[top[x]]<depth[top[y]])swap(x,y);
        x=fa[top[x]];
    }
    return depth[x]<depth[y]?x:y;
}
int ans;
void Getans(int x)
{
    for(int i=head[x];i;i=edge[i].next)
        if(edge[i].to!=fa[x])
        {
            Getans(edge[i].to);
            cha[x]+=cha[edge[i].to];
            ans = max(ans,cha[edge[i].to]);
        }   
}
int main()
{
    int n=read(),k=read();
    for(int i=1;i<n;++i)
    {
        int x=read(),y=read();
        add(x,y);
    }
    DFS1(1);
    DFS2(1,1);
    for(int i=1;i<=k;++i)
    {
        int x=read(),y=read();
        int tt = lca(x,y);
        cha[x]++,cha[y]++,cha[tt]--,cha[fa[tt]]--;
    }
    add(0,1);
    Getans(0);
    cout<<ans;
}
