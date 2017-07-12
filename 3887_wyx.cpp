
#include <stdio.h>
#include <string.h>
#include <queue>
#include <iostream>
#include <algorithm>
const int N = 100000+5;
const int M = N << 2;
using namespace std;
 
inline int read()
{
    int x=0,f=1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
    while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
    return x*f;
}   
 
struct data
{
    int head[N];
    struct graph
    {
        int next,to;
        bool t;
        graph () {}
        graph (int _next,int _to,bool _t=0)
        :next(_next),to(_to),t(_t){}
    }edge[M];
 
    int m;
 
    inline void add(int x,int y,bool flag=0)
    {
        static int cnt = 0;
        edge[++cnt] = graph(head[x],y,flag);
        head[x] = cnt;
    }
 
    int stack[N],DFN[N],low[N],belong[N],size[N];
    bool in[N],vis[N];
    int cnt,top,scc;
 
    void tarjan(int x)
    {
        vis[x] = in[x] = 1;
        stack[++top] = x;DFN[x] = low[x] = ++cnt;
        for(int i=head[x];i;i=edge[i].next)
            if(!vis[edge[i].to])
            {
                tarjan(edge[i].to);
                low[x] = min(low[x],low[edge[i].to]);
            }
            else if(in[edge[i].to])
                low[x] = min(low[x],DFN[edge[i].to]);
        if(DFN[x] == low[x])
        {
            int now = -1;
            scc ++;
            while(now^x)
            {
                int tt;
                now = tt = stack[top--];
                in[tt] = false;
                belong[tt] = scc;
                size[scc] ++;
            }
        }
    }
 
    int n;
    void work1()
    {
        for(int i=1;i<=n;++i)
            if(!vis[i])
                tarjan(i);
    }
 
    int dis[N];
    int f[N],g[N];
    int val[N];
 
    void spfa(int x)
    {
        queue <int> q;
        memset(in,false,sizeof in);
        q.push(x); in[x] = 1; dis[x] = val[x];
        while(!q.empty())
        {
            int tt = q.front();q.pop();in[tt] = false;
            for(int i=head[tt];i;i=edge[i].next)
                if(dis[edge[i].to] < dis[tt] + val[edge[i].to] && edge[i].t)
                {
                    dis[edge[i].to] = dis[tt] + val[edge[i].to];
                    if(!in[edge[i].to])
                    {
                        in[edge[i].to] = 1;
                        q.push(edge[i].to);
                    }
                }
        }
        memcpy(f,dis,sizeof dis);
 
        memset(dis,0,sizeof dis);
        memset(in,false,sizeof in);
        q.push(x); in[x] = 1;dis[x] = val[x];
        while(!q.empty())
        {
            int tt = q.front();q.pop();in[tt] = false;
            for(int i=head[tt];i;i=edge[i].next)
                if(dis[edge[i].to] < dis[tt] + val[edge[i].to] && !edge[i].t)
                {
                    dis[edge[i].to] = dis[tt] + val[edge[i].to];
                    if(!in[edge[i].to])
                    {
                        in[edge[i].to] = 1;
                        q.push(edge[i].to);
                    }
                }
        }
        memcpy(g,dis,sizeof g);
    }
 
    void work2(int x)
    {
        int ans = 0;
        spfa(x);
 
        for(int t=1;t<=n;++t)
            for(int i=head[t];i;i=edge[i].next)
                if(!edge[i].t && f[t]!=0 && g[edge[i].to] != 0)
                    ans = max(ans,f[t]+g[edge[i].to]-val[x]);
        cout << ans << endl;
    }
 
    void init()
    {
        n = read(), m = read();
        for(int i=1;i<=m;++i)
        {
            int x = read(),y = read();
            add(x,y);
        }
        work1();
    }
}G1,G2;
 
void rebuild()
{
    G2.n = G1.scc;
    for(int t=1;t<=G1.n;++t)
        for(int i=G1.head[t];i;i=G1.edge[i].next)
            if(G1.belong[t] != G1.belong[G1.edge[i].to])
                G2.add(G1.belong[t],G1.belong[G1.edge[i].to],1),G2.add(G1.belong[G1.edge[i].to],G1.belong[t],0);
    for(int i=1;i<=G2.n;++i)
        G2.val[i] = G1.size[i];
    G2.work2(G1.belong[1]);
}
 
int main()
{
    G1.init(); 
    rebuild();
}
