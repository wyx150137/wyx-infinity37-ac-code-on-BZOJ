
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int S = 1<<10;
const int N = 1005;
const int M = 6005;
const int P = 15;
const int INF = 0x3f3f3f3f;
struct E
{int next,to,val;}e[M];
int head[N],tot,cnt,n,m,p;
void add(int x,int y,int f)
{
    e[++tot].to = y;
    e[tot].next = head[x];
    e[tot].val = f;
    head[x] = tot;
    e[++tot].to = x;
    e[tot].next = head[y];
    e[tot].val = f;
    head[y] = tot;
}
struct Point{int c,d;}po[P];
bool cmp(Point a,Point b){return a.c<b.c;}
int dis[S][N];
int g[S];
int Q[65540];
unsigned short l,r;
bool v[N];
void spfa(int dis[])
{
    while(l!=r)
    {
        int x = Q[l];
        l++;
        v[x] = false;
        for(int i = head[x];i;i = e[i].next)
        {
            if(dis[x]+e[i].val<dis[e[i].to])
            {
                dis[e[i].to] = dis[x]+e[i].val;
                if(!v[e[i].to])
                {
                    v[e[i].to] = true;
                    Q[r++] = e[i].to;
                }
            }
        }
    }
}
int DP()
{
    l = 1,r = 1;
    for(int i = 1;i<1<<cnt;i++)
    {
        //memset(v,0,sizeof(v));
        for(int j = 1;j<= n;j++)
        {
            for(int k = i&(i-1);k;k = (k-1)&i)
                dis[i][j] = min(dis[k][j]+dis[i^k][j],dis[i][j]);
            if(dis[i][j]!=INF){Q[r++] = j;v[j] = true;}
        }
        spfa(dis[i]);
    }
    int ans = INF;
    for(int i = 1;i<= n;i++)
        ans = min(ans,dis[(1<<cnt)-1][i]);
    return ans;
}
int main()
{
    int x,y,z;
    scanf("%d%d%d",&n,&m,&p);
    for(int i = 1;i<= m;i++)
    {
        scanf("%d%d%d",&x,&y,&z);
        add(x,y,z);
    }
    for(int i = 1;i<= p;i++)
        scanf("%d%d",&po[i].c,&po[i].d);
    int col = 0;
    int true_col[20]={};
    sort(po+1,po+p+1,cmp);
    for(int i=1;i<=p;i++)
    {
        if(i==1||po[i].c!=po[i-1].c)
            ++col;
        true_col[i]=col;
    }
    for(int i=1;i<=p;i++)
        po[i].c = true_col[i];
    memset(g,0x3f,sizeof(g));
    int end = 1<<col;
    for(int i = 0;i<end;i++)
    {
        cnt = 0;
        for(int j = 1;j<= p;j++)
            if(i&(1<<(po[j].c-1)))
                cnt++;
        memset(dis,0x3f,sizeof(dis[0][0])*N*(1<<cnt));
        cnt = 0;
        for(int j = 1;j<= p;j++)
            if(i&(1<<(po[j].c-1)))
                dis[1<<cnt++][po[j].d] = 0;
        g[i] = DP();
    }
    for(int i=1;i<end;i++)
        for(int j=i&(i-1);j;j = (j-1)&i)
            g[i]=min(g[i],g[j]+g[i^j]);
    printf("%d\n",g[(1<<col)-1]);
    return 0;
}
