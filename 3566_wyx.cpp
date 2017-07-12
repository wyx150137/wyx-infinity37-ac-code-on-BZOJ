
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 500000+5;
const int M = N << 1;
const double eps = 1e-7;
using namespace std;

int head[N];

struct graph
{
	int next,to;
	double val;
	graph () {}
	graph (int _next,int _to,double _val)
	:next(_next),to(_to),val(_val){}	
}edge[M];

inline void add(int x,int y,double z)
{
	static int cnt = 0;
	edge[++cnt] = graph(head[x],y,z);
	head[x] = cnt;
	edge[++cnt] = graph(head[y],x,z);
	head[y] = cnt;
}

double F[N][2];

void DFS1(int x,int fa)
{
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to != fa)
			{
				DFS1(edge[i].to,x);
				F[x][0] *= (F[edge[i].to][0] + (1.0-F[edge[i].to][0])*(1.0-edge[i].val));
			}
}

void DFS2(int x,int fa)
{
	double tmp1,tmp2;
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to != fa)
		{	
			tmp2 = (F[edge[i].to][0] + (1.0-F[edge[i].to][0])*(1.0-edge[i].val));
			tmp1 = tmp2 < eps ? 0 : F[x][0]/tmp2*F[x][1];
			F[edge[i].to][1] = tmp1 + (1.0-tmp1)*(1.0-edge[i].val);
			DFS2(edge[i].to,x);
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
	int n = read(),tt;

	for(int i=1;i<n;++i){
		int x = read(), y = read(), z = read();
		add(x,y,0.01*z);
	}

	for(int i=1;i<=n;++i)
	{
		tt = read();
		F[i][0] = 1.0-0.01*tt;
	}
	DFS1(1,-1); F[1][1] = 1; DFS2(1,-1);
	double ans = 0.0;
	for(int i=1;i<=n;++i) ans += 1.0-F[i][0]*F[i][1];
	printf("%.6lf",ans);
}
