
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int inf = 0x3f3f3f3f;
const int N = 200000 + 5;
const int M = N << 1;
const int Maxn = 1000000+5;
using namespace std;

int head[N],n;

struct graph
{
	int next,to,val;
	graph () {}
	graph (int _next,int _to,int _val)
	:next(_next),to(_to),val(_val){}
}edge[M];

inline void add(int x,int y,int z)
{
	static int cnt = 0;
	edge[++cnt] = graph(head[x],y,z);
	head[x] = cnt;
	edge[++cnt] = graph(head[y],x,z);
	head[y] = cnt;
}

int T[Maxn],dis[N],F[N],k,root;
int size[N],depth[N],sum;
bool vis[N];

void DFS1(int x,int fa)
{
	size[x] = 1, F[x] = 0;
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to != fa && !vis[edge[i].to])
		{
			DFS1(edge[i].to,x);
			size[x] += size[edge[i].to];
			F[x] = max(F[x],size[edge[i].to]);
		}
	F[x] = max(F[x],sum - size[x]);
	root = F[x] < F[root] ? x : root;
}

int ans = inf;

void DFS2(int x,int fa)
{
	if(dis[x] <= k) ans = min(ans,depth[x] + T[k - dis[x]]);
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to != fa && !vis[edge[i].to])
		{
			depth[edge[i].to] = depth[x] + 1;
			dis[edge[i].to] = dis[x] + edge[i].val;
			DFS2(edge[i].to,x);
		}
}

void init(int x,int fa,int opt)
{
	if(dis[x] <= k)
	{
		if(opt) T[dis[x]] = min(T[dis[x]],depth[x]);
		else T[dis[x]] = inf;
	}
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to != fa && !vis[edge[i].to])
			init(edge[i].to,x,opt);
}

void solve(int x)
{
	vis[x] = 1; T[0] = 0;
	for(int i=head[x];i;i=edge[i].next)
		if(!vis[edge[i].to])
		{
			depth[edge[i].to] = 1;
			dis[edge[i].to] = edge[i].val;
			DFS2(edge[i].to,x);
			init(edge[i].to,x,1);
		}
	for(int i=head[x];i;i=edge[i].next)
		if(!vis[edge[i].to])
			init(edge[i].to,x,0);
	for(int i=head[x];i;i=edge[i].next)
		if(!vis[edge[i].to])
		{
			sum = size[edge[i].to],root = 0;
			DFS1(edge[i].to,x);
			solve(root);
		}
}

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int main()
{
	n = read(), k = read();
	for(int i=1;i<=k;++i) T[i] = n;
	for(int i=1,x,y,z;i<n;++i)
	{
		x = read() + 1, y = read() + 1, z = read();
		add(x,y,z);
	}
	sum = n ; F[0] = inf;
	root = 0;
	DFS1(1,1);
//	cout << root << endl;
	solve(root);
	printf("%d\n" , ans < n ? ans : -1);
}
