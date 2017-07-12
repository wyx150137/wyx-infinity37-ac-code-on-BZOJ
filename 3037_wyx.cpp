
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define N 1000000+5
#define M 1000000+5
const int inf = 0x7fffff;
using namespace std;
typedef long long LL;

inline LL read()
{
	LL x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int head[N],fa[N];
int f[N],g[N];
LL ans;

struct graph
{
	int next,to;
	graph () {}
	graph (int _next,int _to)
	:next(_next),to(_to){}	
}edge[M];

inline void add(int x,int y)
{
	static int cnt = 0;
	edge[++cnt] = graph(head[x],y);
	head[x] = cnt;
}

bool ban[N],vis[N];
int root;

int find(int x)
{
	vis[x] = 1;
	return vis[fa[x]] ? x : find(fa[x]);
}

void DFS(int x)
{
	vis[x] = 1,f[x] = 1,g[x] = 0;
	int tmp = inf;
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to!=root)
		{
			DFS(edge[i].to);
			g[x] += min(f[edge[i].to],g[edge[i].to]);
			f[x] += min(f[edge[i].to],g[edge[i].to]);
			tmp = min(tmp,f[edge[i].to]-g[edge[i].to]);
		}
	if(!ban[x])
		g[x] += max(0,tmp);
}

int main()
{
	int n;
	cin>>n;

	for(int i=1;i<=n;++i)
	{
		fa[i] = read();
		add(fa[i],i);
	}

	for(int i=1;i<=n;++i)
		if(!vis[i])
		{
			int x = find(i);
			ban[fa[root = x]] = true;
			DFS(x);int tmp = f[x];
			ban[fa[x]] = false;
			DFS(x);tmp = min(tmp,g[x]);
			ans += tmp;
		}
	cout<<n-ans;
}
