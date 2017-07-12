
#include <vector>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int inf = 0x7fffffff;
const int N = 2e5+5;
const int M = N << 1;
#define pb push_back
int head[N], a[N], last[N];
int n, m, K, P;

#define lowbit(x) ((x)&(-x))
int tt[N];

struct BIT {
	int l;
	vector <int> V;
	inline void push(int x,int val) {
		if(l < x + 1) V.pb(val), l ++;
		else V[x] += val;
	}

	inline void updata(int x,int val) {
		while(x <= l) {
			V[x] += val;
			x += lowbit(x);
		}
	}

	inline int ask(int x) {
		int ans = 0;
		while(x) {
			ans += V[x];
			x -= lowbit(x) ;
		}
		return ans;
	}

	inline void init() {
		for(int i=0;i<l;++i) tt[i+1] = V[i], V[i] = 0;
		V.pb(0);
		for(int i=1;i<=l;++i)  updata(i,tt[i]);
	}
} tmp1[N], tmp2[N];

struct graph {
	int next,to;
	graph () {}
	graph (int _next,int _to)
	:next(_next),to(_to){}
}edge[M];

inline void add(int x,int y)  {
	static int cnt = 0;
	edge[++cnt] = graph(head[x],y); head[x] = cnt;
	edge[++cnt] = graph(head[y],x); head[y] = cnt;
}

namespace Graph {
	int fa[N][21], depth[N];

	inline void pre(int x) {
		for(int i=1;i<=20;++i) fa[x][i] = fa[fa[x][i-1]][i-1];
	}

	inline void DFS1(int x) {
		pre(x);
		for(int i=head[x];i;i=edge[i].next) {
			if(edge[i].to != fa[x][0]) {
				fa[edge[i].to][0] = x;
				depth[edge[i].to] = depth[x] + 1;
				DFS1(edge[i].to);
			}
		}
	}

	inline int lca(int x,int y) {
		if(depth[x] < depth[y]) swap(x,y);
		int tt = depth[x] - depth[y];
		for(int i=0;i<=20;++i) if((1<<i)&tt) x = fa[x][i];
		for(int i=20;i>=0;--i) if(fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
		return x == y ? x: fa[x][0];
	}

	inline int calc(int x,int y){
		return depth[x] + depth[y] - (depth[lca(x,y)] << 1);
	}
}

using namespace Graph;

namespace Sol {
	int F[N], size[N];
	bool vis[N];
	int sum, root;

	inline void DFS2(int x,int fa) {
		F[x] = 0, size[x] = 1;
		for(int i=head[x];i;i=edge[i].next) {
			if(edge[i].to != fa && !vis[edge[i].to]) {
				DFS2(edge[i].to,x);
				F[x] = max(F[x], size[edge[i].to]);
				size[x] += size[edge[i].to];
			}
		}
		F[x] = max(F[x], sum - size[x]);
		if(F[x] < F[root]) root = x;
	}

	inline void calc_dep(int x,int fa,int p,int opt) {
		if(opt == 0) tmp2[p].push(calc(x,last[p]),a[x]);
		else tmp1[p].push(calc(x,p), a[x]);
		for(int i=head[x];i;i=edge[i].next) {
			if(edge[i].to != fa && !vis[edge[i].to])
				calc_dep(edge[i].to,x,p,opt); 
		}
	}

	inline void solve(int x) {
		vis[x] = 1;
		calc_dep(x,-1,x,1);
		for(int i=head[x];i;i=edge[i].next) {
			if(!vis[edge[i].to]) {
				F[root = 0] = inf;
				sum = size[edge[i].to];
				DFS2(edge[i].to,x);
				last[root] = x;
				tmp2[root].push(0,0);
				calc_dep(edge[i].to,x,root,0);
				solve(root);
			}
		}
		tmp1[x].init();
		tmp2[x].init();
	}

	inline void init(){
		F[root = 0] = inf, sum = n;
		DFS2(1,0);
		tmp2[root].push(0,0);
		int tmp = root;
		DFS2(root,0);
		solve(tmp);
	}
}

using namespace Sol;

inline void change(int x,int val) {
	for(int i = x; i; i = last[i]) {
		int dis1 = calc(x,last[i]), dis2 = calc(x,i);
		tmp1[i].updata(dis2+1,-a[x]); tmp1[i].updata(dis2+1,val);
		tmp2[i].updata(dis1+1,-a[x]); tmp2[i].updata(dis1+1,val);
	}
	a[x] = val;
}

inline int get(int x) {
	int t1 = calc(x, P);
	int t2 = calc(last[x], P);
	int res = t1 <= K ? tmp1[x].ask(min(tmp1[x].l, K - t1 + 1)) : 0;
	if(!last[x]) return res;
	if(t2 <= K)  res -= tmp2[x].ask(min(tmp2[x].l, K - t2 + 1));
	return res + get(last[x]);
}

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int main() {
	n = read(), m = read();
	for(int i=1;i<=n;++i) a[i] = read();
	for(int i=1;i<n;++i) add(read(),read());
	DFS1(1);
	init();
	int ans = 0;
	for(int i=1;i<=m;++i) {
		int opt = read(); P = read(), K = read();
		P ^= ans, K ^= ans;
		if(opt == 0) printf("%d\n", ans = get(P));
		else change(P,K);
	}
}
