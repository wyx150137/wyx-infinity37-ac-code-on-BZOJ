
#include <queue>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 30000+5;
const int M = (60000+5)<<1;
using namespace std;

int head[N];
bool vis[N];

struct data
{
	int from,to,val;
	bool operator < (const data &z)const
	{
		return from ^ z.from ? from < z.from : to > z.to;
	}
}E[M];

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int K;

struct graph
{
	int head[N];
	int depth[N];
	int cnt;
	struct tmp
	{
		int next,to,val;
		tmp () {}
		tmp (int _next,int _to,int _val)
		:next(_next),to(_to),val(_val){}
	}edge[M];
	
	inline void add(int x,int y,int z)
	{
		edge[++cnt] = tmp(head[x],y,z); head[x] = cnt;
	}
	
	int dis[N];
	bool in[N];
	
	void spfa(){
		queue <int> q;
		memset(dis,0x3f,sizeof dis); dis[1] = 0; q.push(1);
		while(!q.empty())
		{
			int tt = q.front(); q.pop(); in[tt] = false;
			for(int i=head[tt];i;i=edge[i].next)
				if(dis[edge[i].to] > dis[tt] + edge[i].val)
				{
					dis[edge[i].to] = dis[tt] + edge[i].val;
					if(!in[edge[i].to])
					{
						in[edge[i].to] = 1;
						q.push(edge[i].to);
					}
				}
		}
	}
	
	int size[N],f[N];
	int root,sum;
	
	void DFS1(int x,int fa)
	{
		size[x] = 1, f[x] = 0;
		for(int i=head[x];i;i=edge[i].next)
			if(edge[i].to != fa && !in[edge[i].to])
			{
				DFS1(edge[i].to,x);
				size[x] += size[edge[i].to];
				f[x] = max(f[x],size[edge[i].to]);
			}
		f[x] = max(f[x],sum - size[x]);
		root = f[root] < f[x] ? root : x;
	}
	
	int G[N][2],F[N][2];
	
	int Max;
	
	void DFS2(int x,int fa)
	{
		if(depth[x] > K) return; 
		Max = max(Max,depth[x]);
		if(F[depth[x]][0] < dis[x]) F[depth[x]][0] = dis[x] , F[depth[x]][1] = 1;
		else if(F[depth[x]][0] == dis[x]) F[depth[x]][1] ++;
		for(int i=head[x]; i ;i = edge[i].next)
			if(edge[i].to != fa && !in[edge[i].to])
			{
				depth[edge[i].to] = depth[x] + 1;
				dis[edge[i].to] = dis[x] + edge[i].val;
				DFS2(edge[i].to,x);
			}
	}
	
	int ans1, ans2;
	
	void solve(int x)
	{
		dis[x] = depth[x] = 0; 
		int mx = 0; in[x] = 1;
		G[0][1] = 1;
		for(int i=head[x];i;i=edge[i].next)
			if(!in[edge[i].to])
			{
				depth[edge[i].to] = depth[x] + 1; Max = 0;
				dis[edge[i].to] = dis[x] + edge[i].val;
				DFS2(edge[i].to,x); 
				mx = max(Max,mx);
				for(int j=0;j<=Max;++j)
				{
					if(ans1 < F[j][0] + G[K-j][0]) ans1 = F[j][0] + G[K-j][0] , ans2 = F[j][1] * G[K-j][1];
					else if(ans1 == F[j][0] + G[K-j][0]) ans2 += F[j][1] * G[K-j][1];
				}
				for(int j=0;j<=Max;++j)
				{
					if(G[j][0] < F[j][0]) G[j][0] = F[j][0], G[j][1] = F[j][1];
					else if(G[j][0] == F[j][0]) G[j][1] += F[j][1];
					F[j][0] = F[j][1] = 0;
				}
			}
		for(int j=0;j<=mx;++j) G[j][0] = G[j][1] = 0;
		for(int i=head[x];i;i=edge[i].next)
			if(!in[edge[i].to])
			{
				sum = size[edge[i].to];
				root = 0;
				DFS1(edge[i].to,x);
				solve(root);
			}
	}

	void init(int x)
	{
		root = 0; f[0] = 0x3f3f3f3f; sum = x;
		DFS1(1,1); 
		solve(root);
		cout << ans1 << " " << ans2 << endl;
	}
}G1,G2;

void DFS3(int x)
{
	vis[x] = 1;
	for(int i=G1.head[x];i;i=G1.edge[i].next)
		if(!vis[G1.edge[i].to] && G1.dis[G1.edge[i].to] == G1.dis[x] + G1.edge[i].val)
		{
			G2.add(x,G1.edge[i].to,G1.edge[i].val);
			G2.add(G1.edge[i].to,x,G1.edge[i].val);
			DFS3(G1.edge[i].to);
		}
}

int main()
{
	int n = read(), m = read(); K = read() -1 ;
	for(int i=1;i<=m;++i) E[i].from = read(),E[i].to = read(), E[i].val = read();
	for(int i=1;i<=m;++i) E[i+m] = E[i], swap(E[i+m].from,E[i+m].to); m <<= 1; sort(E+1,E+m+1);
	for(int i=1;i<=m;++i) G1.add(E[i].from,E[i].to,E[i].val);
	G1.spfa(); 
	DFS3(1); 
	G2.init(n);
}
