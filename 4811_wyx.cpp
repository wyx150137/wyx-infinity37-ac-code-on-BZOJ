
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
typedef unsigned long long uLL;
const uLL Max = 0-1;
const int N = 2e5+5;
const int M = N<< 2;

inline uLL read() {
	uLL x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int head[N], opt[N], depth[N], n, m, k;
uLL val[N];

struct graph {
	int next, to;
	graph () {}
	graph (int _next,int _to)
	:next(_next), to(_to) {}
}edge[M];

inline void add(int x,int y) {
	static int cnt = 0;
	edge[++cnt] = graph(head[x],y); head[x] = cnt;
	edge[++cnt] = graph(head[y],x); head[y] = cnt;
}

int size[N], fa[N], top[N], w[N];

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

int has[N];

inline void DFS2(int x,int chain) {
	static int sz = 0;
	w[x] = ++sz; top[x] = chain;int k = 0; has[sz] = x;
	for(int i=head[x];i;i=edge[i].next) {
		if(edge[i].to != fa[x] && size[k] < size[edge[i].to]) k = edge[i].to;
	}
	if(!k) return; DFS2(k,chain);
	for(int i=head[x];i;i=edge[i].next) {
		if(edge[i].to != fa[x] && edge[i].to != k) DFS2(edge[i].to, edge[i].to);
	}
}

uLL calc(uLL a,int x) {
	if(opt[x] == 1) return a & val[x];
	if(opt[x] == 2) return a | val[x];
	if(opt[x] == 3) return a ^ val[x];
}

struct data {
	uLL w0, w1, v0, v1;
	data () {
		w0 = w1 = v0 = v1 = 0;
	}
} ans[N], ans1[N], tr[M];

data merge(data tmp1, data tmp2) {
	data tmp;
	tmp.v0 = (tmp1.v0 & tmp2.v1)|((~tmp1.v0)&tmp2.v0);
	tmp.v1 = (tmp1.v1 & tmp2.v1)|((~tmp1.v1)&tmp2.v0);
	tmp.w0 = (tmp2.w0 & tmp1.w1)|((~tmp2.w0)&tmp1.w0);
	tmp.w1 = (tmp2.w1 & tmp1.w1)|((~tmp2.w1)&tmp1.w0);
	return  tmp;
}

void build(int k,int l,int r) {
	if(l==r) {
		int tmp = has[l];
		tr[k].v0 = calc(0, tmp);
		tr[k].v1 = calc(Max, tmp);
		tr[k].w0 = calc(0, tmp);
		tr[k].w1 = calc(Max, tmp);
		return;
	}
	int mid = (l+r) >> 1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	tr[k] = merge(tr[k<<1], tr[k<<1|1]);
}

inline void change(int k,int l,int r, int pos) {
	if(l==r) {
		int tmp = has[l];
		tr[k].v0 = calc(0, tmp);
		tr[k].v1 = calc(Max, tmp);
		tr[k].w0 = calc(0, tmp);
		tr[k].w1 = calc(Max, tmp);
		return;
	}
	int mid = (l+r) >> 1;
	if(pos <= mid) change(k<<1,l,mid,pos);
	else change(k<<1|1,mid+1,r,pos);
	tr[k] = merge(tr[k<<1], tr[k<<1|1]);
}

inline data ask(int k,int l,int r,int x,int y) {
	if(x <= l && r <= y) return tr[k];
	int mid = (l+r) >> 1;
	if(y <= mid) return ask(k<<1,l,mid,x,y);
	else if(x > mid) return ask(k<<1|1,mid+1,r,x,y);
	else return merge(ask(k<<1,l,mid,x,mid),ask(k<<1|1,mid+1,r,mid+1,y));
}

inline data ask(int x,int y) {
	int top1 = 0, top2 = 0;	
	while(top[x] != top[y]) {
		if(depth[top[x]] > depth[top[y]]) {
			ans[++top1] = ask(1,1,n,w[top[x]],w[x]);
			x = fa[top[x]];
		}
		else {
			ans1[++top2] = ask(1,1,n,w[top[y]],w[y]);
			y = fa[top[y]];
		}
	} 
	if(depth[x] < depth[y]) ans1[++top2] = ask(1,1,n,w[x], w[y]);
	else ans[++top1] = ask(1,1,n,w[y], w[x]);
	for(int i=1;i<=top1;++i) swap(ans[i].v0, ans[i].w0), swap(ans[i].v1,ans[i].w1);
	data sum;
	if(top1) {
		sum = ans[1];
		for(int i=2;i<=top1;++i) sum = merge(sum, ans[i]);
		if(top2) sum = merge(sum, ans1[top2]);
	}
	else sum = ans1[top2];
	for(int i=top2-1;i>=1;--i) sum = merge(sum, ans1[i]);
	return sum;
}

uLL P[N];

int main() {
//	freopen("tt.in","r",stdin);	
	P[0] = 1;
	for(int i=1;i<=63;++i) P[i] = P[i-1]*2;
	n = read(), m = read(), k = read();
	for(int i=1;i<=n;++i) opt[i] = read(), val[i] = read();
	for(int i=1;i<n;++i) {
		int x = read(), y = read();
		add(x, y);
	}
	DFS1(1);
	DFS2(1,1);
	build(1,1,n);
	for(int i=1;i<=m;++i) {
		int opt = read(), x = read(), y = read();
		uLL val = read();
		if(opt == 2) {
			::opt[x] = y;
			::val[x] = val;
			change(1,1,n,w[x]);
		}
		else {
			data t = ask(x, y);
			uLL ans = 0;
			for(int i=63;i>=0;--i) {
				uLL tmp0 = (t.v0>>i)&1;
				uLL tmp1 = (t.v1>>i)&1;
				if(tmp0 >= tmp1 || P[i] > val) ans |= (tmp0 ? P[i] : 0);
				else ans |= (tmp1 ? P[i] : 0), val -= P[i];
			}
			printf("%llu\n", ans);
		}
	}
}
