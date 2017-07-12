
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
struct M
{
    int next,to;
}edge[50005];
int head[50005],tot,cnt,zn,z[50005],dep[50005],low[50005],n,m;
bool in[10005],v[10005];
void add(int x,int y)
{
    edge[++tot].to = y;
    edge[tot].next = head[x];
    head[x] = tot;
}
int pn,t[10005],ln[10005],lnn[10005];
void tarjan(int x)
{
    v[x] = true;
    z[++zn] = x;
    in[x] = true;
    dep[x] = low[x] = ++cnt;
    for(int i = head[x];i;i=edge[i].next)
    {
        if(!v[edge[i].to])
            {tarjan(edge[i].to);low[x] = min(low[x],low[edge[i].to]);}
        else if(in[edge[i].to])
            {low[x] = min(low[x],dep[edge[i].to]);}
    }
    if(dep[x]==low[x])
    {
        pn++;
        int tmp;
        do
        {
            tmp = z[zn--];
            in[tmp] = false;
            ln[tmp] = pn;
            lnn[pn]++;
        }while(tmp!=x);
    }
    return ;
}
void dfs(int x)
{
    if(x==n+1)return ;
    for(int i = head[x];i;i = edge[i].next)
    {
        if(ln[x]!=ln[edge[i].to])
            t[ln[x]]++;
    }
    dfs(x+1);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i = 1;i<= m;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        add(x,y);
    }
    for(int i = 1;i<= n;i++)
        if(!v[i])tarjan(i);
    dfs(1);
    int ans = 0,tmp = 0;
    for(int i = 1;i<= pn;i++)
    {
        if(t[i]==0)
        {
            if(ans)
            {
                ans = 0;
                break;
            }
            ans=lnn[i]; 
        }
    }
    printf("%d",ans);
    return 0;
}
