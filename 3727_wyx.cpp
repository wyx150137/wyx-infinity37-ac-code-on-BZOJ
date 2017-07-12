
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
const int N = 300000+5	;
const int M = 600000+5	;
typedef long long LL;

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
	static int cnt = 0;
	edge[++cnt] = graph(head[x],y);
	head[x] = cnt;
	edge[++cnt] = graph(head[y],x);
	head[y] = cnt;
}

int dis[N];
LL a[N],b[N];
int fa[N];

struct Lux
{
	LL a,b;
	Lux () {a=b=0;}
	Lux (LL _a,LL _b):a(_a),b(_b){}
}tmp[N],tmp2[N],tmpb1;
Lux operator + (const Lux &a,const Lux &b){return Lux(a.a+b.a,a.b+b.b);}
Lux operator - (const Lux &a,const Lux &b){return Lux(a.a-b.a,a.b-b.b);}
Lux operator * (const Lux &a,LL y) {return Lux(a.a*y,a.b*y);}

queue <int> q;

void DFS(int x,int val)
{
	q.push(x);dis[x] = val;
	while(!q.empty())
	{
		int tt = q.front();q.pop();
		for(int i=head[tt];i;i=edge[i].next)
			if(edge[i].to!=fa[tt])
			{
				fa[edge[i].to] = tt;
				dis[edge[i].to] = dis[tt] + 1;
				q.push(edge[i].to);
			}
	}
}

inline LL read()
{
	LL x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int main()
{
	int n = read();
	for(int i=1;i<n;++i)
	{
		int x = read() ,y = read();
		add(x,y);
	}
	for(int i=1;i<=n;++i)
		b[i] = read();
	fa[1] = 1;
	DFS(1,0);
	LL ans = 0;
	for(int i=2;i<=n;++i)
		tmp[i] = Lux(1,b[fa[i]]-b[i]);	

	for(int x=2;x<=n;++x)
	{
		tmp2[x] = tmp[x] ;
		for(int i=head[x];i;i=edge[i].next)
			if(edge[i].to!=fa[x])
				tmp2[x] = tmp2[x] - tmp[edge[i].to];
		tmpb1 = tmpb1 + tmp2[x]* dis[x];
	}
	
	ans = (2*b[1]-tmpb1.b)/tmpb1.a;
	a[1] = ans;
	for(int i=2;i<=n;++i)
	{
		a[i] = (tmp2[i].a*ans + tmp2[i].b)>>1;
		a[1] -= a[i];
	}
	for(int i=1;i<n;++i)
		printf("%lld ",a[i]);
	printf("%lld",a[n]);
}

