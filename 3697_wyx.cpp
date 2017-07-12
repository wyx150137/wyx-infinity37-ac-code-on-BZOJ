
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 100000+5;
const int M = N << 1;
const int base = N -5 ;
typedef long long LL;
using namespace std;

int head[N],root;
int dis[N],depth[N];
bool vis[N];

struct graph
{
	int next,to,val;
	graph () {}
	graph (int _next,int _to,int _val)
	:next(_next),to(_to),val(_val){}
}edge[M];

LL F[N<<1][2];
LL G[N<<1][2];

inline void add(int x,int y,int z)
{
	z = z == 0 ? -1 : 1;
	static int cnt = 0;
	edge[++cnt] = graph(head[x],y,z); head[x] = cnt;
	edge[++cnt] = graph(head[y],x,z); head[y] = cnt;
}

int size[N],f[N];
int  sum;

void DFS1(int x,int fa)
{
	size[x] = 1, f[x] = 0;
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to != fa && !vis[edge[i].to])
		{
			DFS1(edge[i].to,x);
			size[x] += size[edge[i].to];
			f[x] = max(f[x],size[edge[i].to]);
		}
	f[x] = max(f[x],sum - size[x]);
	root = f[root] < f[x] ? root : x;
}

LL ans = 0;

LL t[N<<1];
int Max;

void DFS2(int x,int fa)
{
	if(t[dis[x]+base]) G[dis[x]+base][1] ++;
	else  G[dis[x]+base][0] ++;
	Max = max(Max,depth[x]);
	t[dis[x] + base] ++;
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to != fa && !vis[edge[i].to])
		{
			dis[edge[i].to] = dis[x] + edge[i].val;
			depth[edge[i].to] = depth[x] + 1;
			DFS2(edge[i].to,x);
		}
	t[dis[x]+base]--;
}

void solve(int x)
{
	F[0+base][0] = 1;
	vis[x] = 1;depth[x] = 0; dis[x] = 0;
	for(int i=head[x];i;i=edge[i].next)
		if(!vis[edge[i].to])
		{
			dis[edge[i].to] = dis[x] + edge[i].val; 
			depth[edge[i].to] = depth[x] + 1;
			Max = 0;  DFS2(edge[i].to,x); 
			ans += (F[0+base][0]-1) * G[0+base][0];
			for(int j = -Max; j <= Max; ++j)
				ans += F[j+base][1] * G[-j+base][0] + F[j+base][0] * G[-j+base][1] + F[j+base][1] * G[-j+base][1];
			for(int j = -Max; j <= Max; ++j)
				F[j+base][1] += G[j+base][1], F[j+base][0] += G[j+base][0] , G[j+base][1] = G[j+base][0] = 0;
		}
	for(int i = -sum; i <= sum; ++i ) F[i+base][1] = F[i+base][0] = 0;

	for(int i=head[x];i;i=edge[i].next)
		if(!vis[edge[i].to])
		{
			root = 0;
			sum = size[edge[i].to];
			DFS1(edge[i].to,x);
			solve(root);
		}
}

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0'; ch = getchar();}
	return x*f;
}

int main()	
{
	int n = read ();
	for(int i=1;i<n;++i)
	{
		int x = read(), y = read(), z = read();
		add(x,y,z);
	}
	f[0] = 0x3f3f3f3f; sum = n ; root = 0;
	DFS1(1,1);
	solve(root);
	cout << ans << endl;
}

