
#include <set>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
const int M = N << 2;
const int Maxm = 100*N;

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int head[N];

struct graph {
	int next, to;
	graph () {}
	graph (int _next,int _to)
	:next(_next), to(_to) {}
}edge[M];

int cnt;

inline void add(int x,int y) {
	edge[++cnt] = graph(head[x], y); head[x] = cnt;
}

int fa[N][18], times, in[N], out[N], has[N];

inline void DFS(int x) {
	in[x] = ++times; has[times] = x;
	for(int i=head[x];i;i=edge[i].next) 
		DFS(edge[i].to);
	out[x] = times;
}

int tr[Maxm], ls[Maxm], rs[Maxm], sz;

inline void change(int x,int &y,int l,int r,int pos,int val) {
	y = ++sz; ls[y] = ls[x], rs[y] = rs[x], tr[y] = tr[x] + val;
	if(l==r) return;
	int mid = (l+r) >> 1;
	if(pos <= mid) change(ls[x], ls[y], l, mid, pos,val);
	else change(rs[x], rs[y], mid+1, r, pos, val); 
} 

inline int ask(int k,int l,int r,int x,int y) {
	if(!k) return 0;
	if(l==x && r==y) return tr[k];
	int mid = (l+r) >> 1;
	if(y <= mid) return ask(ls[k] , l, mid, x, y);
	else if(x > mid) return ask(rs[k], mid+1, r, x,y);
	else return ask(ls[k], l, mid, x, mid) + ask(rs[k], mid+1, r, mid+1, y);
}

set <int> s[N];
int depth[N];

inline int lca(int x,int y) {
	if(depth[x] < depth[y]) swap(x,y);
	int tt = depth[x] - depth[y];
	for(int i=17;~i;--i) if((1<<i)&tt) x = fa[x][i];
	for(int i=17;~i;--i) if(fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
	return x == y ? x : fa[x][0];
}

int root[N], col[N], a[N];

bool cmp(int a,int b) {
	return depth[a] != depth[b] ? depth[a] < depth[b] : in[a] < in[b];
}


int main() {
//	freopen("tt.in","r",stdin);
	int T = read();
	while(T--) {
		int n = read() ,m = read();
		cnt = times = sz = 0;
		for(int i=1;i<=n;++i) has[i] = head[i] = root[i] = 0;
		for(int i=1;i<=n;++i) s[i].clear();
		for(int i=1;i<=n;++i) col[i] = read(), a[i] = i;
		depth[1] = 1;
		for(int i=2;i<=n;++i) {
			int tmp = read();
			fa[i][0] = tmp;
			depth[i] = depth[tmp]+1;
			add(tmp, i);
		}
		for(int j=1;j<=17;++j)for(int i=1;i<=n;++i) fa[i][j] = fa[fa[i][j-1]][j-1];
		DFS(1);
		sort(a+1,a+n+1,cmp);
		set <int> :: iterator it1;
		int tmp1, tmp2;
		for(int i=1;i<=n;++i) {
			if(depth[a[i]] != depth[a[i-1]]) change(root[depth[a[i]]-1], root[depth[a[i]]], 1, n, in[a[i]], 1);
			else change(root[depth[a[i]]], root[depth[a[i]]], 1, n, in[a[i]], 1);
			tmp1 = tmp2 = 0;
			it1 = s[col[a[i]]].upper_bound(in[a[i]]);
			if(it1 != s[col[a[i]]].end()) {
				tmp1 = (*it1);
				tmp1 = has[tmp1];
				change(root[depth[a[i]]], root[depth[a[i]]], 1, n, in[lca(a[i], tmp1)], -1);
			}
			if(it1 != s[col[a[i]]].begin()) {
				it1 -- ;
				tmp2 = (*it1);
				tmp2 = has[tmp2];
				change(root[depth[a[i]]], root[depth[a[i]]], 1, n, in[lca(a[i],tmp2)], -1);
			}
			if(tmp1 && tmp2) {	
				change(root[depth[a[i]]], root[depth[a[i]]], 1, n, in[lca(tmp1,tmp2)], 1);
			}
			s[col[a[i]]].insert(in[a[i]]);
		}
		int lastans = 0;
		for(int i=1;i<=m;++i) {
			int x = read() ^ lastans, d = read() ^ lastans;
			int tmp = depth[x] + d;
			printf("%d\n", (lastans = ask(root[tmp], 1, n, in[x], out[x])));
		}
	}
}
