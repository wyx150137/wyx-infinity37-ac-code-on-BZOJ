
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 105;
const int M = 505;
struct E
{
	int next,to;
}edge[N],e[N];
int h1[N],h2[N],tot1,tot2,ind[N];
void add1(int x,int y)
{
	edge[++tot1].to = y;
	edge[tot1].next = h1[x];
	h1[x] = tot1;
}
void add2(int x,int y)
{
	ind[y]++;
	e[++tot2].to = y;
	e[tot2].next = h2[x];
	h2[x] = tot2;
}
int dep[N],low[N],dfn,stack[N],top,scc,id[N],W[N],V[N];
int w[N],v[N],n,m;
bool ins[N],vis[N];
void tarjan(int x)
{
	vis[x] = true;
	low[x] = dep[x] = ++dfn;
	stack[++top] = x;
	ins[x] = true;
	for(int i = h1[x];i;i = edge[i].next)
	{
		if(!vis[edge[i].to])
			{tarjan(edge[i].to);low[x] = min(low[x],low[edge[i].to]);}
		else if(ins[edge[i].to])
			low[x] = min(low[x],dep[edge[i].to]);
	}
	if(low[x]==dep[x])
	{
		scc++;
		int tmp;
		do{
			tmp = stack[top--];
			ins[tmp] = false;
			id[tmp] = scc;
			W[scc]+=w[tmp],V[scc]+=v[tmp];
		}while(tmp!=x);
	}
}
bool map[N][N];
void rebuild()
{
	for(int i = 1;i<= n;i++)
		for(int j = h1[i];j;j = edge[j].next)
			if(id[i]!=id[edge[j].to]&&!map[id[i]][id[edge[j].to]])
			{
				add2(id[i],id[edge[j].to]);
				map[id[i]][id[edge[j].to]] = true;
			}
}
int f[N][M];
void dp(int x,int fa)
{
	if(W[x]<=m)f[x][W[x]] = V[x];
	for(int i = h2[x];i;i = e[i].next)
		if(e[i].to!=fa)
			dp(e[i].to,x);
	for(int i = h2[x];i;i = e[i].next)
		for(int j = m;j>=0;j--)
			for(int k = 0;k<= j;k++)
				if(f[x][j-k]!=-1&&f[e[i].to][k]!=-1)
					f[x][j] = max(f[x][j],f[x][j-k]+f[e[i].to][k]);
}
int main()
{
	int x;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)scanf("%d",&w[i]);
	for(int i = 1;i<= n;i++)scanf("%d",&v[i]);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d",&x);
		if(x==0)continue;
		add1(x,i);
	}

	for(int i = 1;i<= n;i++)
		if(!vis[i])
			tarjan(i);
	//printf("warning\n");
	rebuild();
	int root = 0;
	for(int i = 1;i<= scc;i++)
		if(ind[i]==0)
			add2(root,i);
	memset(f,-1,sizeof(f));
	int ans = 0;
	dp(root,-1);
	for(int i = m;i>=0;i--)
		ans = max(f[root][i],ans);
	printf("%d\n",ans);
	return 0;
}
