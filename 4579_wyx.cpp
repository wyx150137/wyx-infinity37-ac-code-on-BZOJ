
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 200000+5;
const int M = N << 1;
using namespace std;
 
int fa[N];
int rank[N];
int stack[N];
bool vis[N];
 
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
  
int find(int x)
{
    int top = 0;
    while(fa[x]!=x)
    {
        stack[++top] = x;
        x=fa[x];
    }
    while(top)
        fa[stack[top--]] = x;
    return x;
}
 
void Union(int x,int y)
{
    int fx = find(x),fy = find(y);
    if(rank[fx] <= rank[fy])
    {
        fa[fx] = fy;
        if(rank[fx] == rank[fy]) rank[fy] ++;
    }
    else fa[fy] = fx;
}
 
int head[N];
 
struct graph
{
    int next,to;
    graph () {}
    graph (int _next,int _to)
    :next(_next),to(_to){}
}edge[M];
 
inline void add(int x,int y){
    static int cnt = 0;
    edge[++cnt] = graph(head[x],y);
    head[x] = cnt;
    edge[++cnt] = graph(head[y],x);
    head[y] = cnt;
}
 
int ask[N];
 
int main()
{
    int n = read(), m = read();
    for(int i=1;i<=m;++i)
    {
        int x = read(), y = read();
        add(x,y);
    }
    for(int i=1;i<=n;++i) fa[i] = i; 
    int q = n;
    for(int i=1;i<=q;++i) ask[i] = read();
    int tt = 0 ;
    for(int i=q;i>=1;--i)
    {
        tt ++;
        vis[ask[i]] = 1;
        int tmp = ask[i];
        for(int j=head[tmp];j;j=edge[j].next)
            if(vis[edge[j].to])
            {
                int fx = find(tmp),fy = find(edge[j].to);
                if(fx == fy) continue;
                tt --,Union(fx,fy);
            }
        ask[i] = tt == 1;
    }
 
    for(int i=1;i<=q;++i)
        printf("%s\n",ask[i]>0 ? "YES" : "NO");
}
 
