
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N=200005;
const int M=200005;
const int nQ=500005;
long long ans;
int n, m, K, head[N+M];
int pos[N], g[N], depth[N+M];
int fa[N+M][20], tot;

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

struct graph {
	int next,to;
	graph () {}
	graph (int _next,int _to)
	:next(_next),to(_to){}
}edge[M<<1];

struct Q { 
	int x, y, depth, id; 
	bool operator < (const Q&z) const {
		return depth ^ z.depth ? depth > z.depth : id < z.id;
	}
}q[nQ];

inline void add(int x,int y) {
	static int cnt = 0;
	edge[++cnt] = graph(head[x],y); head[x] = cnt;
	edge[++cnt] = graph(head[y],x); head[y] = cnt;
}

void DFS(int x) {
    for(int i=1;i<=19;++i) fa[x][i] = fa[fa[x][i-1]][i-1];
    for(int i=head[x]; i; i=edge[i].next) if(edge[i].to!=fa[x][0]) { 
    	fa[edge[i].to][0] = x;
    	depth[edge[i].to] = depth[x] + 1;
    	DFS(edge[i].to);
    }
}

inline int lca(int x,int y) {
	if(depth[x] < depth[y]) swap(x,y);
	int tt = depth[x] - depth[y];
	for(int i=19;~i;--i) if((1<<i)&tt) x = fa[x][i];
	for(int i=19;~i;--i) if(fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
	return x == y ? x : fa[x][0];
}

int main() {
    n = read(), m = read(), K = read();
    for(int i=1; i<=n; ++i) pos[i]=i;
    for(int i=1; i<=n; ++i) g[i] = read();
    for(int i=1; i<=m; ++i) { 
    	int a = read(), b = read(), tt=n+i; 
    	add(pos[a], tt); add(pos[b], tt); 
    	pos[b]=tt; 
    }   
    for(int i=n+m; i>=1; --i) if(!fa[i][0]) DFS(i);
    for(int i=1; i<=K; ++i) { 
    	int a = read(), b = read(), ff=lca(a, b); 
    	if(!ff) continue; 
    	q[tot++]=(Q){a, b, depth[ff], tot}; 
   	}
    sort(q, q+tot);
    for(int i=0; i<tot; ++i) {
        int x=q[i].x, y=q[i].y;
        int dec=min(g[x], g[y]);
        g[x]-=dec; g[y]-=dec; ans+=dec;
    }
    printf("%lld\n", ans<<1);
    return 0;
}
