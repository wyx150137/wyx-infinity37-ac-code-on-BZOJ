
#include <vector>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 200000+5;
const int M = N << 1;
int sz, son[N][26], in[N], out[N], val[N], fa[N], depth[N], tr[N], has[N], sum[N], v[N];
vector <int> V[N], G[N];

#define lowbit(x) ((x)&(-x))

inline void change(int x,int val) {
	static const int Max = 2e5;
	while(x <= Max) {
		tr[x] += val;
		x += lowbit(x);
	}
}

int head[N];

inline int ask(int x) {
	int ans = 0;
	while(x) {
		ans += tr[x];
		x -= lowbit(x);
	}
	return ans;
}

struct graph {
	int next, to;
	graph () {}
	graph (int _next,int _to)
	:next(_next), to(_to) {}
}edge[M];

inline void add(int x,int y) {
	static int cnt = 0;
	edge[++cnt] = graph(head[x], y);
	head[x] = cnt;
}

struct data {
	int l, r, id;
	bool operator < (const data &z) const {
		return r < z.r;
	}
} a[N];

char str[N];
int p, np, q, nq, last, root;

inline int newnode(int _) {
	depth[++sz] = _;
	return sz;
}

inline void insert(int x,int id) {
	p = last;
	if(son[p][x]) {
		q = son[p][x];
		if(depth[q] == depth[p] + 1) last = q;
		else {
			nq = newnode(depth[p]+1);
			memcpy(son[nq], son[q], sizeof son[q]);
			fa[nq] = fa[q]; fa[q] = nq;
			while(p && son[p][x] == q) {
				son[p][x] = nq;
				p = fa[p];
			}
			last = nq;
		}
	}
	else {
		np = newnode(depth[p]+1);
		while(p && !son[p][x]) {
			son[p][x] = np;
			p = fa[p];
		}
		if(!p) fa[np] = root;
		else {
			q = son[p][x];
			if(depth[q] == depth[p]+1) fa[np] = q;
			else {
				nq = newnode(depth[p]+1);
				memcpy(son[nq], son[q], sizeof son[q]);
				fa[nq] = fa[q]; fa[np] = fa[q] = nq;
				while(p && son[p][x] == q) {
					son[p][x] = nq;
					p = fa[p];
				}
			}
		}
		last = np;
	}
	V[last].push_back(id);
	G[id].push_back(last);
}

inline void DFS1(int x) {
	static int sz = 0;
	in[x] = ++sz; has[sz] = x;
	for(int i=head[x];i;i=edge[i].next) {
		DFS1(edge[i].to);
	}
	out[x] = sz;
}

inline void DFS2(int x) {
	v[x] += v[fa[x]];
	for(int i=head[x];i;i=edge[i].next) {
		DFS2(edge[i].to);
	}
}

int fin[N];

int main() {
	int n, lmt;
	cin >> n >> lmt;
	root = last = newnode(0);
	for(int i=1;i<=n;++i) {
		scanf("%s", str+1);
		last = root;
		int len = strlen(str+1);
		for(int j=1;j<=len;++j) 
			insert(str[j]-'a', i);
	}
	for(int i=2;i<=sz;++i) add(fa[i], i);
	DFS1(1);
	for(int i=1;i<=sz;++i) a[i] = (data){in[i], out[i],i};
	sort(a+1,a+sz+1);
	int k = 1;
	for(int i=1;i<=sz;++i) {
		for(int j=0;j<V[has[i]].size();++j) {
			if(fin[V[has[i]][j]]) change(fin[V[has[i]][j]], -1);
			change(fin[V[has[i]][j]] = i, 1);
		}
		while(a[k].r == i) {
			sum[a[k].id] = ask(a[k].r) - ask(a[k].l-1);
			k ++;
		}
	}
	for(int i=1;i<=sz;++i) {
		if(sum[i] >= lmt) v[i] = depth[i] - depth[fa[i]];
		else v[i] = 0;
	}
	DFS2(root);
	long long ans = 0;
	for(int i=1;i<=n;++i) {
		if(i > 1) putchar(' ');
		ans = 0;
		for(int j=0;j<G[i].size();++j)  ans += v[G[i][j]];
		printf("%lld", ans);
	}
}
