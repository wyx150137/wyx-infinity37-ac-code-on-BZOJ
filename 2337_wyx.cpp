
#include <cmath>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 200+5;
const int M = 20000+5;
const double eps = 1e-13;
typedef long double ld;
using namespace std;

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int head[N];
int deg[N],n,m;

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
	head[x] = cnt; deg[x] ++;
}

ld a[N][N];

void solve()
{
	for(int i=1;i<=n;++i)
	{
		int tt = i;
		for(int j=i;j<=n;++j)
			if(fabs(a[j][i]) > eps) tt = j;
		for(int j=1;j<=n+1;++j)
			swap(a[i][j],a[tt][j]);
		for(int j=1;j<=n;++j)
			if(fabs(a[j][i]) > eps && j != i)
			{
				ld t = a[j][i] / a[i][i];
				for(int k=1;k<=n+1;++k)
					a[j][k] -= a[i][k]*t;
			}
	}
}

int main()
{
	n = read(), m = read();
	for(int i=1;i<=m;++i)
	{
		int x = read(), y = read(), z = read();
		if(x!=y)
		{
			add(x,y,z);
			add(y,x,z);
		}
		else
			add(x,y,z);
	}

	ld ans = 0.0;
	for(int i=0;i<=30;++i)
	{
		memset(a,0,sizeof a);
		for(int x=1;x<n;++x)
		{
			a[x][x] = 1.0;
			for(int j=head[x];j;j=edge[j].next)
				if((edge[j].val)&(1<<i))
					a[x][edge[j].to] += 1.0/deg[x],a[x][n+1] += 1.0/deg[x];
				else
					a[x][edge[j].to] -= 1.0/deg[x];
		}
		a[n][n] = 1.0;
		solve();
		ans += (a[1][n+1]/a[1][1]) * (1<<i);
	}
	printf("%.3lf\n",(double)(ans));
}
