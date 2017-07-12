
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 400000+5;
const int M = N << 1;
int root, sz,deg[N];
int son[N*11][15], fa[N*11], depth[N*11], v[N];

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

inline int newnode(int _) {
	depth[++sz] = _; return sz;
}

inline int insert(int last,int x) {
	int np = newnode(depth[last]+1), p = last;
	while(p && !son[p][x]) {
		son[p][x] = np;
		p = fa[p];
	}
	if(!p) fa[np] = root;
	else {
		int q = son[p][x];
		if(depth[q] == depth[p] + 1) fa[np] = q;
		else {
			int nq = newnode(depth[p]+1);
			memcpy(son[nq],son[q],sizeof son[q]);
			fa[nq] = fa[q]; fa[q] = fa[np] = nq;
			while(p && son[p][x] == q) {
				son[p][x] = nq;
				p = fa[p];
			}
		} 
	}
	return np;
}

int head[N];

struct graph {
	int next,to;
	graph () {}
	graph (int _next,int _to)
	:next(_next),to(_to){}
}edge[M];

inline void add(int x,int y) {
	static int cnt = 0;
	edge[++cnt] = graph(head[x],y); head[x] = cnt;
	edge[++cnt] = graph(head[y],x); head[y] = cnt;
}

inline void DFS(int x,int fa,int last) {
	int newlast = insert(last,v[x]);
	for(int i=head[x];i;i=edge[i].next) {
		if(edge[i].to != fa) {
			DFS(edge[i].to,x,newlast);
		}
	}
}

int main () {
	int n = read(), m = read();
	for(int i=1;i<=n;++i) v[i] = read();
	for(int i=1;i<n;++i) {
		int x = read(), y = read();
		add(x,y); deg[x] ++ ,deg[y] ++;
	}
	sz = root = 1;
	for(int i=1;i<=n;++i) {
		if(deg[i] == 1) {
			DFS(i,0,root);
		}
	}
	long long ans = 0;
	for(int i=1;i<=sz;++i) ans += depth[i] - depth[fa[i]];
	cout << ans << endl;
}
