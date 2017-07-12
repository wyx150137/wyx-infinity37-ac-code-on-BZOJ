
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 50000+5;
const int M = N << 1;
const int lmt = 10;
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
	static int cnt = 0;
	edge[++cnt] = graph(head[x],y);
	head[x] = cnt;
	edge[++cnt] = graph(head[y],x);
	head[y] = cnt;
}

int fa[N];
int PP[N][lmt+1];
int sum[N][lmt+1];
int depth[N],size[N],top[N];
int pos[N];
int belong[N];
int a[N];

void DFS1(int x)
{
	size[x] = 1;
	for(int i=2;i<=lmt;++i)
		if(PP[fa[x]][i-1])
			PP[x][i] = PP[fa[x]][i-1];
	for(int i=1;i<=lmt;++i)
		sum[x][i] = sum[PP[x][i]][i] + a[x];
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to!=fa[x])
		{
			fa[edge[i].to] = x;
			depth[edge[i].to] = depth[x] + 1;
			PP[edge[i].to][1] = x;
			DFS1(edge[i].to);
			size[x] += size[edge[i].to];
		}
}

void DFS2(int x,int chain)
{
	static int cnt = 0;
	belong[pos[x] = ++cnt] = x;
	top[x] = chain;int k = 0;
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to!=fa[x] && size[k] < size[edge[i].to])
			k = edge[i].to;
	if(!k) return; DFS2(k,chain);
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to!=fa[x] && edge[i].to != k)
			DFS2(edge[i].to,edge[i].to);
}

int Lca(int x,int y)
{
	while(top[x] != top[y])
	{
		if(depth[top[x]] < depth[top[y]])swap(x,y);
		x = fa[top[x]];
	}
	return depth[x] < depth[y] ? x : y;
}

int up(int x,int y)
{
	while(depth[x] - depth[top[x]] < y)
	{
		y -= depth[x] - depth[top[x]] + 1;
		x = fa[top[x]] ;
	}
//	cout << belong[pos[x]-y] <<endl;
	return belong[pos[x] - y];
}

int Get(int x,int y,int v)
{
	if(v < lmt) return sum[x][v] - sum[y][v] + a[y];
	int ans = 0 , remain = 0 , t;
	while(top[x]!=top[y])
	{
		for(t = pos[x] - remain ; t >= pos[top[x]]; t -= v)
			ans += a[belong[t]];
		t += v;
		remain = v - ( t - pos[top[x]] + 1 );
		x = fa[top[x]];
	}

	for(t = pos[x] - remain;t>=pos[y]; t-= v)
		ans += a[belong[t]];
	return ans;

}

int calc(int x,int y,int v)
{
	int z = Lca(x,y);
	int ans = 0;
	int t = depth[x] - depth[z] - ( depth[x] - depth[z] )%v;
	t = up(x,t);
	ans = Get(x,t,v);
	if(y == z)
		return t == y ? ans : a[y];
	int t1 = v - (depth[t] - depth[z]);
	int t2 = depth[y] - depth[z] - t1;
	if(t2 < 0) return ans + a[y];
	int t3 = up(y,t2%v);
	int t4 = up(y,t2);
	ans += Get(t3,t4,v);
	return t2%v ? ans + a[y] : ans;
}

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x * f;
}

int b[N];

int main()
{
	int n = read();
	for(int i=1;i<=n;++i) a[i] = read();
	for(int i=1;i<n;++i)
	{
		int x = read(),y = read();
		add(x,y);
	}
	DFS1(1);
	DFS2(1,1);
/*	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=3;++j)
			cout << sum[i][j] << " ";
		puts("");
	}*/
	for(int i=1;i<=n;++i) b[i] = read();
	for(int i=1;i<n;++i){
		int x = read();
		printf("%d\n",calc(b[i],b[i+1],x));
	}
}

