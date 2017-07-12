
#include <vector>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 100000+5;
const int M = N << 2;
const int Maxm = 3804000;
int head[N],n,m,root[N];

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
	edge[++cnt] = graph(head[x],y); head[x] = cnt;
	edge[++cnt] = graph(head[y],x); head[y] = cnt;
}

int datahead[N];

struct dataedge
{
	int next,to;
	dataedge () {}
	dataedge (int _next,int _to)
	:next(_next),to(_to){}
}G[N];

inline void dataadd(int x,int y)
{
	static int cnt = 0;
	G[++cnt] = dataedge(datahead[x],y); datahead[x] = cnt;
}

int tr[Maxm],ls[Maxm],rs[Maxm],sz;

void change(int L,int R,int x,int &y,int pos,int val)
{
	y = ++sz; ls[y] = ls[x], rs[y] = rs[x] ; tr[y] = tr[x] + val;
	if(L == R) return ; int mid = (L+R) >> 1;
	if(pos <= mid) change(L,mid,ls[x],ls[y],pos,val);
	else change(mid+1,R,rs[x],rs[y],pos,val);
}

int ask(int L,int R,int x,int y,int k1,int k2,int k3,int k4)
{
	if(L == x  && R == y) return tr[k1] + tr[k2] - tr[k3] - tr[k4];
	int mid = (L+R) >> 1;
	if(y <= mid) return ask(L,mid,x,y,ls[k1],ls[k2],ls[k3],ls[k4]);
	else if(x > mid) return ask(mid+1,R,x,y,rs[k1],rs[k2],rs[k3],rs[k4]);
	else return ask(L,mid,x,mid,ls[k1],ls[k2],ls[k3],ls[k4]) + ask(mid+1,R,mid+1,y,rs[k1],rs[k2],rs[k3],rs[k4]);
}

int fa[N][18],depth[N],in[N],out[N];
vector <int> V[N];
int times;

void DFS1(int x)
{
	in[x] = ++times;
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to != fa[x][0])
		{
			fa[edge[i].to][0] = x;
			depth[edge[i].to] = depth[x] + 1;
			DFS1(edge[i].to);
		}
	out[x] = ++times;
}

void DFS2(int x)
{
	root[x] = root[fa[x][0]];
	for(int i=datahead[x];i;i=G[i].next)
	{
		change(1,n<<1,root[x],root[x],in[G[i].to],1);
		change(1,n<<1,root[x],root[x],out[G[i].to],-1);
	}
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to != fa[x][0])
			DFS2(edge[i].to);
}

inline int Lca(int x,int y)
{
	if(depth[x] < depth[y]) swap(x,y);
	int tt = depth[x] - depth[y];
	for(int i=17;~i;--i) if((1<<i)&tt) x = fa[x][i];  if(x == y) return x;
	for(int i=17;~i;--i) if(fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
	return fa[x][0];
}

struct data
{
	int x,y;
	bool operator < (const data &z)const
	{
		return x ^ z.x ? x < z.x : y < z.y;
	}
	bool operator == (const data &z)const
	{
		return x == z.x && y == z.y;
	}
}q[N];

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}


int main()
{
	n = read(), m = read();
	for(int i=1;i<n;++i) add(read(),read());
	for(int i=1;i<=m;++i)
	{
		q[i].x = read(), q[i].y = read();
		dataadd(q[i].x,q[i].y);
	}
	DFS1(1);DFS2(1);
	for(int j=1;j<=17;++j)
		for(int i=1;i<=n;++i)
			fa[i][j] = fa[fa[i][j-1]][j-1];
	typedef long long LL;
	LL ans = 0;
	for(int i=1;i<=m;++i)
	{
		int x = q[i].x, y = q[i].y , L = Lca(x,y);
		ans += ask(1,n<<1,in[L],in[x],root[x],root[y],root[L],root[fa[L][0]]);
		ans += ask(1,n<<1,in[L],in[y],root[x],root[y],root[L],root[fa[L][0]]);
		ans -= ask(1,n<<1,in[L],in[L],root[x],root[y],root[L],root[fa[L][0]]);
		ans --;
	}
	sort(q+1,q+m+1);
	for(int i=1;i<=m;)
	{
		int j = i + 1;
		for(;q[j] == q[i];j++);
		ans -= (LL)(j-i)*(j-i-1);
		i = j;
	}
	LL B=(LL)m*(m-1)>>1;
	cout << ans / __gcd(ans,B) << "/" << B / __gcd(ans,B);
}
