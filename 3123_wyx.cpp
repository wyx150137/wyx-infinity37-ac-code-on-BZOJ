
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 80000+5;
const int M = N << 1;
const int Maxm = 32*17*N;
using namespace std;

int head[N],tot,size[N];
int tr[Maxm],ls[Maxm],rs[Maxm];
int depth[N],fa[N][18],val[N];
int root[N],q[N],a[N],T[N],F[N];

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

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int sz;

void insert(int L,int R,int x,int &y,int pos)
{
	y = ++sz; ls[y] = ls[x],rs[y] = rs[x]; tr[y] = tr[x] + 1;
	if(L==R) return;
	int mid = (L+R) >> 1;
	if(pos <= mid)insert(L,mid,ls[x],ls[y],pos);
	else insert(mid+1,R,rs[x],rs[y],pos);
}

int ask(int L,int R,int k1,int k2,int k3,int k4,int pos)
{
	if(L==R) return T[L];
	int mid = (L+R) >> 1;
	if(tr[ls[k3]]+tr[ls[k4]]-tr[ls[k1]]-tr[ls[k2]] >= pos)return ask(L,mid,ls[k1],ls[k2],ls[k3],ls[k4],pos);
	else return  ask(mid+1,R,rs[k1],rs[k2],rs[k3],rs[k4],pos-(tr[ls[k3]]+tr[ls[k4]]-tr[ls[k1]]-tr[ls[k2]]));
}

int Lca(int x,int y)
{
	if(depth[x] < depth[y]) swap(x,y);
	int tt = depth[x] - depth[y];
	for(int i=17;~i;--i)
		if((1<<i) & tt) x = fa[x][i];
	if(x == y) return x;
	for(int i=17;~i;--i)
		if(fa[x][i] != fa[y][i])
			x = fa[x][i], y = fa[y][i];
	return fa[x][0];
}

void init(int x)
{
	for(int j=1;j<=17;++j)
		fa[x][j] = fa[fa[x][j-1]][j-1];
}

void DFS(int x)
{
	int l = 1, r = 0;
	q[++r] = x;
	while(l<=r)
	{
		int tt = q[l++]; 
		init(tt);
		insert(1,tot,root[fa[tt][0]],root[tt],a[tt]);
		for(int i=head[tt];i;i=edge[i].next)
			if(edge[i].to != fa[tt][0])
			{
				fa[edge[i].to][0] = tt;
				depth[edge[i].to] = depth[tt]  + 1;
				q[++r] = edge[i].to;
			}
	}
}

inline int find(int x)
{
	return F[x] ^ x ? F[x] = find(F[x]) : F[x];
}

int testcase;

int main()
{
	cin >> testcase;
	int n = read(), m = read(), q = read();
	for(int i=1;i<=n;++i) a[i] = T[i] = read();
	sort(T+1,T+n+1);
	for(int i=1;i<=n;++i) if(T[i] != T[i-1]) T[++tot] = T[i];
	for(int i=1;i<=n;++i) a[i] = lower_bound(T+1,T+tot+1,a[i]) - T;
	for(int i=1;i<=n;++i) size[F[i] = i] = 1;
	for(int i=1;i<=m;++i)
	{
		int x = read(), y = read(); add(x,y);
		int fx = find(x), fy = find(y);
		if(fx != fy)
		{
			if(size[fx] < size[fy]) swap(fx,fy);
			size[fx] += size[fy]; F[fy] = fx;
		}
	}
	for(int i=1;i<=n;++i)
		if(!root[i])
			DFS(i);
	char str[10];
	int lastans = 0;
	for(int i=1;i<=q;++i)
	{
		scanf("%s",str);
		if(str[0] == 'Q')
		{
			int x = read() ^ lastans, y = read()^lastans, K = read()^lastans;
			int tmp1 = Lca(x,y) , tmp2 = fa[tmp1][0];
			printf("%d\n",lastans = ask(1,tot,root[tmp1],root[tmp2],root[x],root[y],K));
		}
		else
		{
			int x = read()^lastans, y = read()^lastans;
			int fx = find(x), fy = find(y);
			add(x,y);
			if(size[fx] < size[fy])
				swap(fx,fy),swap(x,y);
			F[fy] = fx, size[fx] += size[fy];
			fa[y][0] = x; depth[y] = depth[x] + 1;
			DFS(y);
		}
	}
}
