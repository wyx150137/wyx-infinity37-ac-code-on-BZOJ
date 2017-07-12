
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e6+100;
const int M = 1e6+100;
const int INF = 36500;
struct E
{int next,to;};
bool v[N],ins[N],tag[N];
int stack[N],dep[N],low[N],dfn,bel[N],scc,top;
int ind[N],f[N];
queue<int>Q;
struct G
{
	int head[N],tot;
	E e[N];
	void add(int x,int y)
	{
		e[++tot].to = y;
		e[tot].next = head[x];
		head[x] = tot;
	}	
	void tarjan(int x)
	{
		v[x] = ins[x] = true;
		stack[++top] = x;
		dep[x] = low[x] = ++dfn;
		for(int i = head[x];i;i = e[i].next)
		{
			if(!v[e[i].to])
				{tarjan(e[i].to);low[x] = min(low[x],low[e[i].to]);}
			else if(ins[e[i].to])
				{low[x] = min(low[x],dep[e[i].to]);}
		}
		if(dep[x]==low[x])
		{
			scc++;
			int tmp = -1;
			do
			{
				tmp = stack[top--];
				ins[tmp] = false;
				bel[tmp] = scc;
			}while(tmp!=x);
		}
	}
	void topo(int n)
	{
		f[bel[n+1]] = 1;
		if(tag[bel[n+1]])f[bel[n+1]]+=INF;
		for(int i = 1;i<= scc;i++)
			if(ind[i]==0)
				Q.push(i);
		while(!Q.empty())
		{
			int x = Q.front();
			Q.pop();
			for(int i = head[x];i;i = e[i].next)
			{
				f[e[i].to]+=f[x];
				if(f[e[i].to]>INF)f[e[i].to]=INF+1;
				if(!--ind[e[i].to])
				{
					if(tag[e[i].to]&&f[e[i].to]>0)f[e[i].to] = INF+1;
					Q.push(e[i].to);
				}
			}
		}
	}
}g1,g2;
void rebuild(int n)
{
	for(int i = 1;i<= n+1;i++)
	{
		for(int j = g1.head[i];j;j = g1.e[j].next)
		{
			int u = i,t = g1.e[j].to;
			if(bel[u]==bel[t]){tag[bel[u]] = true;continue;}
			g2.add(bel[u],bel[t]);
			ind[bel[t]]++;
		}
	}
}
int main()
{
	int n,m,x,y;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d",&x,&y);
		g1.add(y,x);
	}
	for(int i = 1;i<= n+1;i++)
		if(!v[i])
			g1.tarjan(i);
	rebuild(n);
	g2.topo(n);
	int maxn = 0;
	for(int i = 1;i<= n;i++)
		if(f[bel[i]]>maxn)
			maxn = f[bel[i]];
	if(maxn>36500)printf("zawsze\n");
	else printf("%d\n",maxn);
	top = 0;
	for(int i = 1;i<= n;i++)
		if(f[bel[i]]==maxn)
			stack[++top] = i;
	printf("%d\n",top);
	for(int i = 1;i<= top;i++)
		printf("%d ",stack[i]);
	printf("\n");
	return 0;
}
