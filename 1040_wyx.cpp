
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 2000000+5;
const int M = N << 1;
typedef long long LL;
using namespace std;

int head[N];
LL f[N],g[N];
bool vis[N],v[N];

struct graph
{
	int next,to;
	graph () {}
	graph (int _next,int _to)
	:next(_next),to(_to){}
}edge[M];

inline void add(int x,int y)
{
	static int cnt = 1;
	edge[++cnt] = graph(head[x],y);
	head[x] = cnt;
	edge[++cnt] = graph(head[y],x);
	head[y] = cnt;
}

LL ban,w[N];
int in[N];
int re,n,m,root;

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

void find(int x,int fa)
{
	for(int i=head[x];i;i=edge[i].next)
		if(!in[edge[i].to])
		{
			in[edge[i].to] = 1;
			find(edge[i].to,x);
		}
		else if(edge[i].to!=fa)
			re = x,ban=i,root = edge[i].to,ban = i;
}

void DFS1(int x)
{
	g[x] = 0,f[x] = w[x];
	for(int i=head[x];i;i=edge[i].next)
		if( i!=ban && (i^1)!=ban && !vis[edge[i].to])
		{
			vis[edge[i].to] = 1;
			DFS1(edge[i].to);
			f[x] += g[edge[i].to];
			g[x] += max(g[edge[i].to],f[edge[i].to]);
		}
}

void DFS2(int x)
{
	g[x] = 0,f[x] = w[x];
	for(int i=head[x];i;i=edge[i].next)
		if(i!=ban && (i^1)!=ban && !v[edge[i].to])
		{
			v[edge[i].to] = 1;
			DFS2(edge[i].to);
			f[x] += g[edge[i].to];
			if(edge[i].to == re)
				g[x] += g[edge[i].to];
			else g[x] += max(g[edge[i].to],f[edge[i].to]);  
		} 
}

int main()
{
	n = read();
	for(int i=1;i<=n;++i)
	{
		w[i] = read();
		int tmp = read();
		add(i,tmp);
	}
	LL ans = 0;
	for(int i=1;i<=n;++i)
		if(!in[i])
		{
			LL tmp = 0;
			in[i] = 1,root = -1;
			find(i,-1);
			vis[root] = 1;
			DFS1(root);
			tmp = g[root];
			v[root] = 1;
			DFS2(root);
			tmp = max(tmp,max(f[root],g[root]));
			ans += tmp;
		//	cout<<root<<" " <<tmp<<endl;
		}
	cout<<ans<<endl;
}
