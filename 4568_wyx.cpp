
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 2e4+5;
const int M = N << 2;
typedef long long LL;

int n, q;

inline LL read() {
	LL x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int head[N];

struct graph {
	int next, to;
	graph () {}
	graph (int _next,int _to)
	:next(_next), to(_to){}
}edge[M];

inline void add(int x,int y) {
	static int cnt = 0;
	edge[++cnt] = graph(head[x],y); head[x] = cnt;
	edge[++cnt] = graph(head[y],x); head[y] = cnt;
}

int size[N], fa[N], depth[N], Pos[N];

inline void DFS1(int x) {
	size[x] = 1;
	for(int i=head[x];i;i=edge[i].next) {
		if(edge[i].to != fa[x]) {
			fa[edge[i].to] = x;
			depth[edge[i].to] = depth[x] + 1;
			DFS1(edge[i].to);
			size[x] += size[edge[i].to];
		}
	}
}

int w[N], top[N];

inline void DFS2(int x, int chain) {
	static int sz = 0;
	w[x] = ++sz, top[x] = chain; int z = 0; Pos[sz] = x;
	for(int i=head[x];i;i=edge[i].next) {
		if(edge[i].to != fa[x] && size[edge[i].to] > size[z]) z = edge[i].to;
	} 
	if(!z) return;
	DFS2(z,chain);
	for(int i=head[x];i;i=edge[i].next ) {
		if(edge[i].to != fa[x] && edge[i].to != z) {
			DFS2(edge[i].to, edge[i].to);
		}
	}
}

struct data{
	LL a[61];
}Ans, tr[M];

void Merge(data &a,data &b,data &c) {
	data tmp;
	for(int i=0;i<61;++i) tmp.a[i] = b.a[i];
	for(int i=60;~i; --i) {
		if(c.a[i]) {
			LL now = c.a[i];
			for(int j=60; ~j; --j)
				if((1ll<<j) & now) {
					if(!tmp.a[j]) {tmp.a[j] = now; break;}
					else now ^= tmp.a[j];
				}
		}
	}
	for(int i=60;~i;--i) a.a[i] = tmp.a[i];
}

LL val[N];

inline void build(int k,int l,int r) {
	if(l==r) {
		memset(tr[k].a, 0, sizeof tr[k].a);
		LL tmp = val[Pos[l]];
		for(int j=60;~j;--j) {
			if((1ll<<j)&tmp) {
				tr[k].a[j] = tmp;
				break;
			}
		}
		return;
	}
	int mid = (l+r) >> 1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	Merge(tr[k], tr[k<<1], tr[k<<1|1]);
}

inline void ask(int k,int l,int r,int x,int y) {
	if(l==x && r==y) {Merge(Ans, Ans, tr[k]); return;}
	int mid = (l+r) >> 1;
	if(y <= mid) ask(k<<1,l,mid,x,y);
	else if(x > mid) ask(k<<1|1,mid+1,r,x,y);
	else ask(k<<1,l,mid,x,mid), ask(k<<1|1,mid+1,r,mid+1,y);
}

inline void solve_ask(int x,int y) {
	memset(Ans.a, 0, sizeof Ans.a);
	while(top[x] != top[y]) {
		if(depth[top[x]] < depth[top[y]]) swap(x, y);
		ask(1,1,n, w[top[x]], w[x]); x = fa[top[x]];
	}
	if(depth[x] > depth[y]) swap(x,y);
	ask(1,1,n, w[x], w[y]);
}

int main() {
//	freopen("tt.in","r",stdin);
	n = read(), q = read();
	for(int i = 1; i <= n; ++i) val[i] = read();
	for(int i = 1; i < n ; ++i) add(read(),read());
	DFS1(1); DFS2(1,1);
	build(1,1,n);
	for(int i = 1; i <= q; ++i)  {
		int x = read(), y = read();
		solve_ask(x, y);
		LL now = 0;
		for(int j = 60; ~j; --j) {
			if((1ll<<j)&Ans.a[j] && !((1ll<<j)&now)) now ^= Ans.a[j];
		}
		printf("%lld\n", now);
	}
}
