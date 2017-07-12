
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 1e5+5;
const int M = N << 2;
const LL inf = 1e18;
int w[N], fa[N], has[N];

int head[N], size[N], top[N], a[N];

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

struct graph {
	int next, to;
	graph () {}
	graph (int _next,int _to)
	:next(_next), to(_to) {}
}edge[M];

inline void add(int x,int y) {
	static int cnt = 0;
	edge[++cnt] = graph(head[x], y); head[x] = cnt;
	edge[++cnt] = graph(head[y], x); head[y] = cnt;
}

int depth[N];

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

inline void DFS2(int x,int chain) {
	static int cnt = 0;
	w[x] = ++ cnt; top[x] = chain; int k = 0 ; has[w[x]] = x;
	for(int i=head[x];i;i=edge[i].next) if(edge[i].to != fa[x] && size[k] < size[edge[i].to]) k = edge[i].to;
	if(!k) return; DFS2(k,chain);
	for(int i=head[x];i;i=edge[i].next) if(edge[i].to != fa[x] && edge[i].to != k) DFS2(edge[i].to,edge[i].to);
}

int n;
LL tr1[M], tr2[M], lazy[M], Max[M], cnt[M];

inline void updata(int k) {
	tr1[k] = tr1[k<<1] + tr1[k<<1|1];
	tr2[k] = tr2[k<<1] + tr2[k<<1|1];
	cnt[k] = cnt[k<<1] + cnt[k<<1|1];
	Max[k] = max(Max[k<<1], Max[k<<1|1]);
}

inline void down(int k,int l,int r) {
	if(l==r || !lazy[k]) return;
	int mid = (l+r) >> 1;
	LL temp = lazy[k]; lazy[k] = 0;
	lazy[k<<1] += temp; lazy[k<<1|1] += temp;
	tr1[k<<1] += (LL)(mid-l+1-cnt[k<<1])*temp;
	tr2[k<<1] -= (LL)(cnt[k<<1])*temp;
	tr1[k<<1|1] += (LL)(r-mid-cnt[k<<1|1])*temp;
	tr2[k<<1|1] -= (LL)(cnt[k<<1|1]) * temp;
	Max[k<<1] += temp; Max[k<<1|1] += temp;
}

inline void build(int k,int l,int r) {
	if(l==r) {
		int tt = has[l];
		if(a[tt] < 0) {
			tr2[k] = -a[tt];
			Max[k] = a[tt];
			cnt[k] = 1;
		}
		else {
			tr1[k] = a[tt];
			Max[k] = -inf;
		}
		return;
	}
	int mid = (l+r) >> 1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	updata(k);
}

inline void change(int k,int l,int r,int x,int y,int val) {
	if(x <= l && r <= y) {
		if(Max[k] + val > 0) {
			if(l==r) {
				Max[k] += val;
				if(Max[k] > 0) {
					tr1[k] = Max[k];
					tr2[k] = 0;
					Max[k] = -inf;
					cnt[k] = 0;
				}
				else 
					tr2[k] = abs(Max[k]);
				return;
			}
			down(k,l,r);
			int mid = (l+r) >> 1;
			change(k<<1,l,mid,x,y,val);
			change(k<<1|1,mid+1,r,x,y,val);
			updata(k);
		}
		else {
			Max[k] += val; 
			lazy[k] += val;
			tr2[k] -= (LL)cnt[k] * val;
			tr1[k] += (LL)(r-l+1-cnt[k]) * val;
		}
		return;
	}
	else {
		int mid = (l+r) >> 1;
		down(k,l,r);
		if(x <= mid) change(k<<1,l,mid,x,y,val);
		if(y > mid) change(k<<1|1,mid+1,r,x,y,val);
		updata(k);
	}
}

inline LL ask(int k,int l,int r,int x,int y) {
	if(x <= l && r <= y) return tr1[k]+tr2[k];
	down(k,l,r);
	int mid = (l+r) >> 1;
	LL ans = 0;
	if(x <= mid) ans += ask(k<<1,l,mid,x,y);
	if(y > mid) ans += ask(k<<1|1,mid+1,r,x,y);
	return ans;
}

inline LL ask(int x,int y) {
	LL ans = 0;
	while(top[x] != top[y]) {
		if(depth[top[x]] < depth[top[y]]) swap(x,y);
		ans += ask(1,1,n,w[top[x]], w[x]); x = fa[top[x]];
	}
	if(depth[x] > depth[y]) swap(x,y);
	ans += ask(1,1,n,w[x],w[y]);
	return ans;
}

inline void change(int x,int y,int val) {
	while(top[x] != top[y]) {
		if(depth[top[x]] < depth[top[y]]) swap(x,y);
		change(1,1,n,w[top[x]],w[x],val); x = fa[top[x]];
	}
	if(depth[x] > depth[y]) swap(x,y);
	change(1,1,n,w[x],w[y],val);
}

int main() {
//	freopen("tt.in","r",stdin);
	int n = read(), m = read();
	::n = n;
	for(int i=1;i<=n;++i) a[i] = read();
	for(int i=2;i<=n;++i) add(read(),read());
	DFS1(1); DFS2(1,1); build(1,1,n);
	for(int i=1;i<=m;++i) {
		int opt = read();
		if(opt == 1) {
			int x = read(), y = read(), val = read();
			change(x,y,val);
		}
		else {
			int x = read(), y = read();
			printf("%lld\n", ask(x,y));
		}
	}
}
