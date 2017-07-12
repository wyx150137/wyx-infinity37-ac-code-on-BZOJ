
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 200000+5;
const int M = N << 1;
const int Maxn = N << 2;
typedef long long LL;
using namespace std;

int head[N];
int top[N],w[N],depth[N],size[N],fa[N];
LL dis[N];

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
}

void DFS1(int x)
{
	size[x] = 1;
	for(int i=head[x];i;i=edge[i].next)
	{
		fa[edge[i].to] = x;
		depth[edge[i].to] = depth[x] + 1;
		dis[edge[i].to] += dis[x] ;
		DFS1(edge[i].to);
		size[x] += size[edge[i].to];
	}
}

int T[N];
int sz;
int end[N];

void DFS2(int x,int chain)
{
	int k = 0;end[x] = w[x] = ++sz;top[x] = chain;T[sz] = x;
	for(int i=head[x];i;i=edge[i].next)
		if(size[edge[i].to] > size[k])
			k = edge[i].to;
	if(!k) return; DFS2(k,chain); end[x] = end[k];
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to!=k)
			DFS2(edge[i].to,edge[i].to),end[x] = end[edge[i].to];
}

LL tr[Maxn],pos[Maxn];
LL lazy[Maxn];

inline void updata(int k)
{
	tr[k] = tr[k<<1] > tr[k<<1|1] ? tr[k<<1] : tr[k<<1|1];
	pos[k] = tr[k<<1] > tr[k<<1|1] ? pos[k<<1] : pos[k<<1|1];
} 

inline void down(int k,int L,int R)
{
	if(L == R || !lazy[k]) return;
	lazy[k<<1] += lazy[k],lazy[k<<1|1] += lazy[k];
	tr[k<<1] += lazy[k] , tr[k<<1|1] += lazy[k];
	lazy[k] = 0;
}

inline void change(int k,int L,int R,int x,int y,LL val)
{
	if(L == x && R == y)
	{
		lazy[k] += val;
		tr[k] += val;
		return;
	}
	down(k,L,R);
	int mid = (L+R) >> 1;
	if(y <= mid) change(k<<1,L,mid,x,y,val);
	else if(x > mid) change(k<<1|1,mid+1,R,x,y,val);
	else change(k<<1,L,mid,x,mid,val),change(k<<1|1,mid+1,R,mid+1,y,val);
	updata(k);
}

void Pchange(int k,int l,int r)
{
	if(l==r)
	{
		pos[k] = T[l];
		return;
	}
	int mid = (l+r) >> 1;
	Pchange(k<<1,l,mid);
	Pchange(k<<1|1,mid+1,r);
	updata(k);
}

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

bool vis[N];
LL a[N];

int main()
{
	int n = read(), K = read();
	for(int i=1;i<=n;++i) a[i] = dis[i] = read();
	for(int i=1;i<n;++i)
	{
		int x = read(), y = read();
		fa[y] = x; add(x,y);
	}
	
	for(int i=1;i<=n;++i)
		if(!fa[i])
		{
			DFS1(i);
			DFS2(i,i);
			break;
		}
	
	for(int i=1;i<=n;++i) change(1,1,n,w[i],w[i],dis[i]);
	Pchange(1,1,n);
	LL ans = 0;
	while(K--)
	{
		if(tr[1] <= 0) break;
		int tt = pos[1];
		ans += tr[1];
		while(tt)
		{
			if(vis[tt]) break;
			vis[tt] = 1;
			change(1,1,n,w[tt],end[tt],-a[tt]);
			tt = fa[tt];
		}
	}
	cout << ans << endl;
}
