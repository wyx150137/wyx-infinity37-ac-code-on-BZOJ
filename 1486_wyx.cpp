
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define N 10000+5
#define M 50000+5
#define eps 1e-9
using namespace std;

int head[N],n,m;
bool vis[N];
double dis[N];
bool flag;

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
	double val;
	double deval;
	graph () {}
	graph (int _next,int _to,double _val)
	:next(_next),to(_to),val(_val){}
}edge[M];

inline void add(int x,int y,double z)
{
	static int cnt = 0;
	edge[++cnt] = graph(head[x],y,z);
	head[x] = cnt;
}

void build(double mid)
{
	for(int i=1;i<=m;++i)
		edge[i].deval = edge[i].val - mid;
}

void spfa(int x)
{
	vis[x] =true;
	for(int i=head[x];i;i=edge[i].next)
		if(dis[edge[i].to] > dis[x] + edge[i].deval)
		{
			if(vis[edge[i].to]){flag=true;return;}
			dis[edge[i].to] = dis[x] + edge[i].deval;
			spfa(edge[i].to);
		}
	vis[x]=false;
}

bool check(double mid)
{
	build(mid);
	memset(vis,false,sizeof vis);
	memset(dis,0,sizeof dis);
	flag = false;
	for(int i=1;i<=n;++i)
	{
		spfa(i);
		if(flag)return true;
	}
	return flag;
}

int main()
{
	n = read(),m=read();
	double tmp;
	for(int i=1;i<=m;++i)
	{
		int x=read(),y=read();
		scanf("%lf",&tmp);
		add(x,y,tmp);
	}
	double l = -1e7;
	double r = 1e7;
	while(r-l>eps)
	{
		double mid = (l+r)/2;
		if(check(mid))r=mid;
		else l = mid;
	}
	printf("%.8lf\n",l);
}
