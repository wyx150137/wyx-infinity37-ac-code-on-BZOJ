
#include <queue>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
 
const int inf = 0x3f3f3f3f;
const int N = 40000+5;
const int M = 400000+5;
 
using namespace std;
 
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
   
inline int read()
{
    static char ch;
    static int D;
    while(!isdigit(ch=getc()));
    for(D=ch-'0'; isdigit(ch=getc());)
        D=(D<<3)+(D<<1)+(ch-'0');
    return D;
}
 
using namespace Heap;
 
struct graph
{
    int head[N],n,m;
 
    struct data
    {
        int next, to, val,from;
        data() {}
        data(int _next, int _to, int _val,int _from)
        : next(_next), to(_to), val(_val),from(_from) {}
    } edge[M];
 
    inline void add(int x, int y, int z)
    {
        static int cnt = 0;
        edge[++cnt] = data(head[x], y, z,x);
        head[x] = cnt;
    }
 
 
    int dis[N];
    bool in[N];
    int s,t;
 
    void dij()
    {
        memset(dis,0x3f,sizeof dis);
        dis[s]=0;
        push(0,s);
        while(!empty())
        {
            int now  = pop();
 
            if(in[now])continue;
            in[now]=1;
            for(int i=head[now];i;i=edge[i].next)
            {
                if(dis[edge[i].to]>dis[now]+edge[i].val)
                {
                    dis[edge[i].to]=dis[now]+edge[i].val;
                    push(dis[edge[i].to],edge[i].to);
                }
            }
        }
    }
 
    int pre[N];
    bool vis[N];
 
    void BFS()
    {
        queue <int> q;
        for(int i=head[s];i;i=edge[i].next)
            if(dis[edge[i].to] == edge[i].val)
                pre[edge[i].to] = edge[i].to,q.push(edge[i].to),vis[edge[i].to] = 1;
        while(!q.empty())
        {
            int tt = q.front();q.pop();
            for(int i=head[tt];i;i=edge[i].next)
                if(dis[edge[i].to] == dis[tt] + edge[i].val)
                {
                    pre[edge[i].to] = pre[tt];
                    if(!vis[edge[i].to])
                    {
                        vis[edge[i].to] = 1;
                        q.push(edge[i].to);
                    }
                }
        }
    }
 
}G1,G2;
 
int main()
{
    int n = read(), m = read();
    G1.n = n;
    G1.m = m;
    register int i = 1;
    for(i=1;i<=m;++i)
    {
        int x = read(),y = read();
        int z = read();
        G1.add(x,y,z);
        z = read();
        G1.add(y,x,z);
    }
 
    int tt = m << 1,x,y,val;
    const int T = n + 1;
    G1.s = G2.s = 1;
    G1.dij();G1.BFS();
 
    for(i=1;i<=tt;i++)
    {
        x = G1.edge[i].from, y = G1.edge[i].to, val = G1.edge[i].val;
        if(y==1){if(G1.pre[x] != x) G2.add(1,T,val+G1.dis[x]); else G2.add(x,T,val);continue;}
        if(x==1){if(G1.pre[y] != y) G2.add(x,y,val);continue;}
        if(G1.pre[x]!=G1.pre[y]) G2.add(1,y,G1.dis[x]+val);
        else G2.add(x,y,val);
    }
     
    G2.dij();
     
    printf("%d\n",G2.dis[T] == inf ? -1 : G2.dis[T]);
}
