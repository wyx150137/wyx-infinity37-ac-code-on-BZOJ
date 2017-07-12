
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define N 250000+10
#define M 500000+10
typedef long long LL;
const LL inf = 1ll<<50;
using namespace std;

inline LL read()
{
	LL x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

bool ban[N];
int head[N],last[N],n;
LL f[N];

struct graph
{
	int next,to;
	LL val;
	graph () {}
	graph (int _next,int _to,LL _val =0)
	:next(_next),to(_to),val(_val){}
}edge[M],tmp[M];

inline void add(int x,int y,LL z)
{
	static int cnt = 0;
	edge[++cnt] = graph(head[x],y,z);
	head[x] = cnt;
	edge[++cnt] = graph(head[y],x,z);
	head[y] = cnt;
}

int fa[N][21];
int depth[N];
LL mn[N];
int V[N];

void DFS(int x)
{
	static int kk = 0;
	V[x] = ++kk;
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to!=fa[x][0])
		{
			fa[edge[i].to][0] = x;
			depth[edge[i].to] = depth[x] + 1;
			mn[edge[i].to] = min(mn[x],edge[i].val);
 			DFS(edge[i].to);
		}
}

void init()
{
	for(int j=1;j<=20;++j)
		for(int i=1;i<=n;++i)
			fa[i][j] = fa[fa[i][j-1]][j-1];
	return;
}

int LCA(int x,int y)
{
	if(depth[x] < depth[y])swap(x,y);
	int tt = depth[x] - depth[y];
	for(int i=20;i>=0;--i)
		if((1<<i)&tt)
			x = fa[x][i];
	if(x==y)return x;
	for(int i=20;i>=0;--i)
		if(fa[x][i]!=fa[y][i])
			x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}

void DFS2(int x)
{
	f[x] = mn[x];
	LL sum = 0;
	for(int i=last[x];i;i=tmp[i].next)
	{
		DFS2(tmp[i].to);
		sum += f[tmp[i].to];
	}
	if(sum && !ban[x])
		f[x] = min(f[x],sum);	
	last[x] = 0;
}

bool cmp(int a, int b)
{
	return V[a] < V[b];
}

int h[N];
int stack[N],top;

int cc;

inline void addsec(int x,int y)
{
	tmp[++cc] = graph(last[x],y);
	last[x] = cc;
}

void solve()
{
	cc = 0;
	int k = read();
	for(int i=1;i<=k;++i)
		h[i] = read() , ban[h[i]] = 1;
	sort(h+1,h+k+1,cmp);
	top = 0;
	for(int i=1;i<=k;++i)
	{
		if(!top){stack[++top] = h[i];continue;}
		int tt = LCA(stack[top],h[i]);
		while(V[tt] < V[stack[top]])
		{
			if(V[tt] >= V[stack[top-1]])
			{
				addsec(tt,stack[top]);
				if(stack[--top]!=tt)
					stack[++top] = tt;
				break;
			}
			addsec(stack[top-1],stack[top]);
			top --;
		}
		stack[++top] = h[i];
	}
	while(top > 1)
		addsec(stack[top-1],stack[top]),top--;
	DFS2(stack[1]);
	printf("%lld\n",f[stack[1]]);
	for(int i=1;i<=k;++i)
		ban[h[i]] = 0;
}

int main()
{
    n = read();mn[1] = inf;
	for(int i=1;i<n;++i)
	{
		int x = read() , y = read() ;LL z = read();
		add(x,y,z);
	}
	DFS(1);
	init();
	int m = read();
	for(int i=1;i<=m;++i)
		solve();
}

