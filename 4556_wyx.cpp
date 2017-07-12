
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 2e5+5;
const int M = 20 * N;
int depth[N], fa[N], sz, temp[N], son[N][26];
int p, np, q, nq, root, last;

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

inline int newnode(int _) {
	depth[++sz] = _;
	return sz;
}

inline void insert(int x,int id) {
	p = last; last = np = newnode(depth[p]+1);
	temp[np] = id;

	while(p && !son[p][x]) {
		son[p][x] = np;
		p = fa[p];
	}

	if(!p) fa[np] = root;
	else {
		q = son[p][x];
		if(depth[q] == depth[p] + 1) fa[np] = q;
		else  {
			nq = newnode(depth[p]+1);
			memcpy(son[nq], son[q], sizeof son[q]);
			fa[nq] = fa[q]; fa[np] = fa[q] = nq;
			while(p && son[p][x] == q) {
				son[p][x] = nq;
				p = fa[p];
			}
		}
	}
}

int tr[M], ls[M], rs[M], Root[N], tot;

inline void change(int &k,int l,int r,int pos) {
	if(!k) k = ++tot;
	tr[k] ++;
	if(l==r) return;
	int mid = (l+r) >> 1;
	if(pos <= mid) change(ls[k], l, mid, pos);
	else change(rs[k], mid+1, r, pos);
}

inline int merge(int x,int y) {
	if(!x || !y) return x + y;
	int z = ++ tot;
	ls[z] = merge(ls[x], ls[y]);
	rs[z] = merge(rs[x], rs[y]);
	tr[z] = tr[ls[z]] + tr[rs[z]];
	return z;
}

inline bool ask(int k,int l,int r,int x,int y) {
	if(!k) return false;
	if(l==x && r==y) return 1;
	int mid = (l+r) >> 1;
	if(y <= mid) return ask(ls[k], l, mid, x, y); 
	else if(x > mid) return ask(rs[k], mid+1, r, x, y);
	else return ask(ls[k], l, mid, x, mid) | ask(rs[k], mid+1, r, mid+1, y);
}

int F[N][20];
int head[N], in[N], out[N];

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

inline void DFS(int x) {
	static int cnt = 0;
	in[x] = ++ cnt;
	for(int i=head[x];i;i=edge[i].next) {
		F[edge[i].to][0] = x;
		DFS(edge[i].to);
		Root[x] = merge(Root[x], Root[edge[i].to]);
	}
	out[x] = cnt;
}

int n, m;

inline bool check(int mid, int x,int l, int r) {
	for(int i=18;~i;--i) {
		if(depth[F[x][i]] >= mid) x = F[x][i];
	} 
	return ask(Root[x], 1, n, l, r);
}

char str[N];
int pos[N];

int main() {  
	root = last = newnode(0);
	n = read(), m = read();
	scanf("%s", str+1);
	reverse(str+1,str+n+1);
	for(int i=1;i<=n;++i) insert(str[i]-'a', i), pos[i] = last;
	for(int i=2;i<=sz;++i) add(fa[i], i);  
	for(int i=1;i<=sz;++i) if(temp[i]) change(Root[i], 1, n, temp[i]);
	DFS(1);
	for(int j=1;j<=18;++j) 
		for(int i=1;i<=sz;++i) F[i][j] = F[F[i][j-1]][j-1];
	for(int i=1;i<=m;++i) {
		int a = n - read() + 1, b = n - read() + 1, c = n - read() + 1, d = n - read() + 1;
		swap(a, b), swap(c, d);
		int l = 1, r = min(b - a + 1, d - c + 1), ans = 0;
		while(l <= r) {
			int mid = (l+r) >> 1;
			if(check(mid, pos[d], a + mid - 1, b)) ans = mid, l = mid + 1;
			else r = mid - 1;
		}
		printf("%d\n", ans);
	}
}
