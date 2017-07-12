
#include <cmath>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
typedef long double ld;
const double eps = 1e-13;
const int N = 500+5;
const int M = N*N;
using namespace std;

int head[N];

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

ld a[N][N];

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int deg[N];
ld G[M];

int main()
{
	int n = read(), m = read();
	for(int i=1;i<=m;++i)
	{
		int x = read(),y = read();
		add(x,y); deg[x]++,deg[y] ++;
	}
	--n;a[1][n+1] = -1.0;
	for(int x=1;x<=n;++x)
	{
		a[x][x] = -1.0;
		for(int i=head[x];i;i=edge[i].next)
			if(edge[i].to!=n+1)
				a[x][edge[i].to] = 1.0/deg[edge[i].to];
	}
	for(int i=1;i<=n;++i)
	{
		int tt = i;
		for(int j=i;j<=n;++j)
			if(fabs(a[j][i]) > eps) tt = j;
		for(int j=1;j<=n+1;++j) swap(a[i][j],a[tt][j]);
		for(int j=1;j<=n;++j)
			if(j!=i && fabs(a[j][i]) > eps)
			{
				ld t = a[j][i] / a[i][i];
				for(int k=1;k<=n+1;++k)
					a[j][k] -= a[i][k] * t;
			}
	}
	for(int i=1;i<=n;++i) a[i][i] = a[i][n+1] / a[i][i];
	for(int i=2;edge[i].to;i+=2)
	{
		int tt1 = edge[i].to,tt2 = edge[i^1].to;
		G[i>>1]  = a[tt1][tt1]/deg[tt1] + a[tt2][tt2]/deg[tt2];
	}
	sort(G+1,G+m+1);
	ld ans = 0;
	for(int i=1,val=m;i<=m;++i,val--) ans += (ld)val * G[i];
	printf("%.3lf",(double)ans);
}
