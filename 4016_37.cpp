
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 3e4+5;
const int M = 6e4+5;
struct E
{int next,to,val;};
bool v[N],used[N];
int dis[N],f[N],size[N],dep[N],ft[N];
int F[N][2],G[N][2];
int sum,root,n,m,K,ans1,ans2;
struct Gragh
{
    E e[M<<1];
    int head[N],tot;
    void add(int x,int y,int f)
    {
        e[++tot].to = y;
        e[tot].next = head[x];
        e[tot].val = f;
        head[x] = tot;
    }
    void spfa(int s)
    {
        queue<int>Q;
        memset(dis,0x3f,sizeof(dis));
        memset(v,0,sizeof(v));
        dis[s] = 0,v[s] = true;
        Q.push(s);
        while(!Q.empty())
        {
            int x = Q.front();
            Q.pop();
            v[x] = false;
            for(int i = head[x];i;i = e[i].next)
                if(dis[x]+e[i].val<dis[e[i].to])
                {
                    dis[e[i].to] = dis[x]+e[i].val;
                    if(!v[e[i].to])
                    {
                        Q.push(e[i].to);
                        v[e[i].to] = true;
                    }
                }
        }
    }
    void get_root(int x,int fa)
    {   
        size[x] = 1;f[x] = 0;
        for(int i = head[x];i;i = e[i].next)
            if(!used[e[i].to]&&e[i].to!=fa)
            {
                get_root(e[i].to,x);
                f[x] = max(f[x],size[e[i].to]);
                size[x]+=size[e[i].to];
            }
        f[x] = max(f[x],sum-size[x]);
        if(f[x]<=f[root])root = x;
    }
    void calc(int x)
    {
        queue<int>Q;
        for(int i = 0;i<= K;i++)
            G[i][0] = G[i][1] = F[i][0] = F[i][1] = 0;
        F[0][1] = 1;
        dep[x] = 0,dis[x] = 0;
        for(int i = head[x];i;i = e[i].next)
        {
            if(used[e[i].to])continue;
            dep[e[i].to] = dep[x]+1;dis[e[i].to] = e[i].val;
            ft[e[i].to] = x;
            Q.push(e[i].to);
            while(!Q.empty())
            {
                int tp = Q.front();
                Q.pop();
                if(dep[tp]>K)continue;
                if(dis[tp]>G[dep[tp]][0])
                    G[dep[tp]][0] = dis[tp],G[dep[tp]][1] = 0;
                if(G[dep[tp]][0]==dis[tp])G[dep[tp]][1]++;
                for(int j = head[tp];j;j = e[j].next)
                    if(e[j].to!=ft[tp]&&!used[e[j].to])
                    {
                        ft[e[j].to] = tp;
                        dep[e[j].to] = dep[tp]+1;
                        dis[e[j].to] = dis[tp]+e[j].val;
                        Q.push(e[j].to);
                    }
            }
            for(int j = 0;j<= K;j++)
            {
                if(F[K-j][0]+G[j][0]>ans1)
                    {ans1 = F[K-j][0]+G[j][0];ans2 = F[K-j][1]*G[j][1];}
                else if(F[K-j][0]+G[j][0]==ans1)
                    {ans2+=F[K-j][1]*G[j][1];}
            }
            for(int j = 0;j<= K;j++)
            {
                if(G[j][0]>F[j][0]){F[j][0] = G[j][0],F[j][1] = G[j][1];}
                else if(G[j][0]==F[j][0]){F[j][1]+=G[j][1];}
                G[j][0] = G[j][1] = 0;
            }
        }
    }
    void work(int x,int S)
    {
        calc(x);
        used[x] = true;
        for(int i = head[x];i;i= e[i].next)
            if(!used[e[i].to])
            {
                root = 0;
                sum= size[e[i].to];
                if(size[e[i].to]>size[x])size[e[i].to]=S-size[e[i].to];
                if(sum>=K)get_root(e[i].to,0);
                work(root,size[e[i].to]);
            }
    }
    void dis_edge()
    {
        for(int i = 1;i<= n;i++)
            for(int j = head[i];j;j = e[j].next)
                if(i<=e[j].to)
                    printf("%d %d %d\n",i,e[j].to,e[j].val);
    }
}g,t;
void rebuild(int x)
{
    v[x] = true;
    for(int i = g.head[x];i;i = g.e[i].next)
    {
        int to = g.e[i].to;
        if(!v[to]&&dis[x]+g.e[i].val==dis[to])
        {
            t.add(x,to,g.e[i].val),t.add(to,x,g.e[i].val);
            rebuild(to);
        }
    }
}
struct Edge
{int u,v,w;}edge[M<<1];
bool cmp(const Edge &a,const Edge &b)
{
    if(a.u==b.u)
        return a.v>b.v;
    return a.u<b.u;
}
int main()
{
    scanf("%d%d%d",&n,&m,&K);
    K--;
    for(int i=1;i<= m;i++)
    {
        scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].w);
        edge[i+m] = edge[i];
        swap(edge[i].u,edge[i].v);
    }
    sort(edge+1,edge+2*m+1,cmp);
    for(int i = 1;i<= 2*m;i++)
        g.add(edge[i].u,edge[i].v,edge[i].w);
    g.spfa(1);
    memset(v,0,sizeof(v));
    rebuild(1);
    //t.dis_edge();
    f[0] = sum= n;
    t.get_root(1,0);
    t.work(root,sum);
    printf("%d %d\n",ans1,ans2);
    return 0;
}
