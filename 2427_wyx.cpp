
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define N 1000+5
#define M 5000+5
using namespace std;
int head[N],last[N];
int n , m;
int f[N][N];

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

struct graph
{
	int next,to;
	graph () {}
	graph (int _next,int _to)
	:next(_next),to(_to){}
}edge[M],tmp[M];

inline void addfir(int x,int y)
{
	static int tt = 0;
	tmp[++tt] = graph(last[x],y);
	last[x] = tt;
}

bool vis[N];

inline void addsec(int x,int y)
{
	static int cnt = 0;vis[y] = 1;
	edge[++cnt] = graph(head[x],y);
	head[x] = cnt;
}

int scc;
int stack[N],top,belong[N];
int depth,dfn[N],low[N];
int v[N],w[N],sv[N],sw[N];
bool in[N];


void tarjan(int x)
{
	low[x] = dfn[x] = ++depth;
	stack[++top] = x; in[x] = 1;
	for(int i=last[x];i;i=tmp[i].next)
		if(!dfn[tmp[i].to])
			tarjan(tmp[i].to),low[x] = min(low[x],low[tmp[i].to]);
		else if(in[tmp[i].to]) 
			low[x] = min(low[x],dfn[tmp[i].to]);
	int now = 0;
	if(low[x] == dfn[x])
	{
		scc ++ ;
		while(now ^ x)
		{
			now = stack[top --];
			in[now] = 0;
			belong[now] = scc;
			sv[scc] += v[now],sw[scc] += w[now];
		}
	}
	return;
}

void rebuild()
{
	for(int i=1;i<=n;++i)
		for(int j=last[i];j;j=tmp[j].next)
			if(belong[i]!=belong[tmp[j].to])
				addsec(belong[i],belong[tmp[j].to]);
}

void DFS(int x)
{
	for(int i=head[x];i;i=edge[i].next)
	{
		DFS(edge[i].to);
		for(int j = m - sw[x] ; j>=0 ;--j)
			for(int k = 0; k <= j ; ++k)
				f[x][j] = max(f[x][j],f[x][k] + f[edge[i].to][j-k]);
	}
	for(int j = m ; j>=0 ; --j)
		if(j >= sw[x])f[x][j] = f[x][j-sw[x]] + sv[x];
		else f[x][j] = 0;
}

int main()
{
	n = read() , m = read();
	for(int i=1;i<=n;++i)w[i] = read();
	for(int i=1;i<=n;++i)v[i] = read();
	for(int i=1;i<=n;++i){
		int x = read();
		if(x) addfir(x,i);
	} 
	for(int i=1;i<=n;++i)
		if(!dfn[i])
			tarjan(i);
	rebuild();
	int root = scc + 1;
	for(int i=1;i<=scc;++i)
		if(!vis[i])addsec(root,i);
	DFS(root);
	cout<<f[root][m];
}
