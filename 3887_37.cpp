
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
const int M = 1e5+5;
int n,m;
struct E
{
	int next,to;
};
struct G
{
	E e[M];
	int head[N],tot;
	void add(int x,int y)
	{
		e[++tot].to = y;
		e[tot].next = head[x];
		head[x] = tot;
	}
}g,g1,gf;
bool ret[N];
bool vis[N],ins[N];
int dep[N],low[N],stack[N],bel[N],top,dfn,scc,val[N];
void tarjan(int x)
{
	vis[x] = ins[x] = true;
	stack[++top] =x;
	dep[x] = low[x] = ++dfn;
	for(int i = g.head[x];i;i = g.e[i].next)
	{
		int u = g.e[i].to;
		if(!vis[u])
		{tarjan(u);low[x] = min(low[x],low[u]);}
		else if(ins[u])
		{low[x] = min(low[x],dep[u]);}
	}
	if(dep[x]==low[x])
	{
		scc++;
		int tmp;
		do{
			tmp = stack[top--];
			ins[tmp] = false;
			bel[tmp] = scc;
			val[scc]++;
		}while(tmp!=x);
	}
}
void rebuild()
{
	for(int i = 1;i<= n;i++)
		for(int j = g.head[i];j;j= g.e[j].next)
		{
			int u = g.e[j].to;
			if(bel[i]!=bel[u])
			{
				g1.add(bel[i],bel[u]);
				if(i==1)ret[bel[u]] = true;
				gf.add(bel[u],bel[i]);
			}
		}
}
int dis[2][N];
bool v[N];
queue<int>Q;
void spfa(int s)
{
	memset(dis,-1,sizeof(dis));
	dis[0][s] = val[s];
	Q.push(s);
	v[s] = true;
	while(!Q.empty())
	{
		int x = Q.front();
		Q.pop();
		v[x]= false;
		for(int i = g1.head[x];i;i = g1.e[i].next)
		{
			int u = g1.e[i].to;
			if(dis[0][x]+val[u]>dis[0][u])
			{
				dis[0][u] = dis[0][x]+val[u];
				if(!v[u])
				{
					Q.push(u);
					v[u] = true;
				}
			}
		}
	}
	Q.push(s);
	v[s] = true;
	dis[1][s] = val[s];
	while(!Q.empty())
	{
		int x= Q.front();
		Q.pop();
		v[x] = false;
		for(int i = gf.head[x];i;i=gf.e[i].next)
		{
			int u = gf.e[i].to;
			if(dis[1][x]+val[u]>dis[1][u])
			{
				dis[1][u] = dis[1][x]+val[u];
				if(!v[u])
				{
					Q.push(u);
					v[u] = true;
				}
			}
		}
	}
}
int main()
{
	//freopen("wander.in","r",stdin);
	//freopen("wander.out","w",stdout);
	int x,y;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d",&x,&y);
		g.add(x,y);
	}
	for(int i = 1;i<= n;i++)
		if(!vis[i])
			tarjan(i);
	rebuild();
	spfa(bel[1]);
	int ans = 0;
	for(int i = 1;i<= n;i++)
		for(int j = g.head[i];j;j= g.e[j].next)
		{
			int u = g.e[j].to;
			if(bel[i]!=bel[u])
				if(dis[0][bel[u]]!=-1&&dis[1][bel[i]]!=-1)
					ans = max(ans,dis[0][bel[u]]+dis[1][bel[i]]-val[bel[1]]);
		}
	printf("%d\n",ans);
	return 0;
}
