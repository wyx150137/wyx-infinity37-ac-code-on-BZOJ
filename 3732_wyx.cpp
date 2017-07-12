
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 15000+5;
const int M = N << 2;
using namespace std;

struct non_dir_graph
{
	int from,to,val;
	bool operator < (const non_dir_graph &z)const{
		return val < z.val;
	}
}tmp[M];

int F[N],rank[N];

int find(int x)
{
	return F[x]^x?F[x]=find(F[x]):F[x];
}

int Union(int x,int y)
{
	int fx = find(x),fy = find(y);
	if(fx == fy) return 0;
	if(rank[fx] < rank[fy]) swap(fx,fy);
	F[fy] = fx,rank[fx] += rank[fy];
	return 1;
}

int head[N],depth[N];

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
	head[x] = cnt;
	edge[++cnt] = graph(head[y],x,z);
	head[y] = cnt;
}

int size[N];
int fa[N];

void DFS1(int x)
{
	size[x] = 1;
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to!=fa[x])
		{
			fa[edge[i].to] = x;depth[edge[i].to] = depth[x] + 1;
			DFS1(edge[i].to),size[x]+=size[edge[i].to];
		}
}

int sz,a[N];
int w[N],top[N];

void DFS2(int x,int chain)
{
	top[x] = chain; w[x] = ++sz;int k = 0;
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to!=fa[x] && size[k] < size[edge[i].to])
			k = edge[i].to;
	if(!k) return ;DFS2(k,chain);
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to!=fa[x]&&edge[i].to!=k)
			DFS2(edge[i].to,edge[i].to);
}

int tr[M];

#define updata(k) tr[k] = max(tr[k<<1],tr[k<<1|1])

int ask(int k,int l,int r,int x,int y)
{
	if(x <=l && r <= y) return tr[k];
	int mid = (l+r)>>1;
	int tmp1 = 0;
	if(x <= mid) tmp1 = max(tmp1,ask(k<<1,l,mid,x,y));
	if(y > mid) tmp1 = max(tmp1,ask(k<<1|1,mid+1,r,x,y));
	return tmp1;
}

inline void change(int k,int l,int r,int pos,int x)
{
	if(l==r){tr[k] = x;return;}
	int mid = (l+r)>>1;
	if(pos <= mid)change(k<<1,l,mid,pos,x);
	else change(k<<1|1,mid+1,r,pos,x);
	updata(k);
}

int n,m,Q;

inline int read()
{
	int x = 0, f = 1; char ch = getchar();
	while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
	return x * f;
}

int solveask(int x,int y)
{
	int MAX = 0;
	while(top[x]!=top[y])
	{
		if(depth[top[x]] < depth[top[y]]) swap(x,y);
		MAX = max(MAX,ask(1,1,n,w[top[x]],w[x]));x = fa[top[x]];
	}
	if(depth[x] > depth[y]) swap(x,y);
	if(w[x]!=w[y]) MAX = max(MAX,ask(1,1,n,w[x]+1,w[y]));
	return MAX;
}

int X[N],Y[N],val[N];

int main(){
	n = read(), m = read(), Q=read();
	for(int i=1;i<=m;++i) tmp[i].from=read(),tmp[i].to = read(),tmp[i].val = read();
	sort(tmp+1,tmp+m+1);for(int i=1;i<=n;++i) rank[F[i] = i] = 1;
	int cnt = 0;
	for(int i=1;cnt<n-1;++i)
		if(Union(tmp[i].from,tmp[i].to))
			++cnt,add(X[cnt] = tmp[i].from,Y[cnt] = tmp[i].to,val[cnt] = tmp[i].val);
	DFS1(1);DFS2(1,1);
	for(int i=1;i<n;++i)
		change(1,1,n,w[depth[X[i]] > depth[Y[i]] ? X[i] : Y[i]],val[i]);
	while(Q--)
	{
		int A = read(),B = read();
		printf("%d\n",solveask(A,B));
	}
}
