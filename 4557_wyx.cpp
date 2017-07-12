
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 5e5+5;
const int M = N << 1;
const int inf = 0x3f3f3f3f;

int fa[N];
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

inline void add(int x,int y) {
	static int cnt = 1;
	edge[++cnt] = graph(head[x], y); head[x] = cnt;
	edge[++cnt] = graph(head[y], x); head[y] = cnt;
}

int F[N][22], G[N][22], w[N], n, d;
bool vis[N];

inline void DFS(int x) {
	G[x][0] = F[x][0] = vis[x] ? w[x] : 0;
	for(int i=1;i<=d;++i) G[x][i] = w[x];
	G[x][d+1] = inf;
	for(int i=head[x];i;i=edge[i].next) {
		if(edge[i].to != fa[x]) {
			fa[edge[i].to] = x;
			DFS(edge[i].to);
			for(int j=0;j<=d;++j) G[x][j] = min(G[x][j]+F[edge[i].to][j], F[x][j+1] + G[edge[i].to][j+1]);
			for(int j=d;~j;--j) G[x][j] = min(G[x][j], G[x][j+1]);
			F[x][0] = G[x][0];
			for(int j=1;j<=d;++j) F[x][j] += F[edge[i].to][j-1];
			for(int j=1;j<=d;++j) F[x][j] = min(F[x][j-1], F[x][j]);
		}
	}
}

int main() {
	n = read(), d = read();
	for(int i=1;i<=n;++i) w[i] = read();
	int m = read();
	for(int i=1;i<=m;++i) vis[read()] = 1;
	for(int i=2;i<=n;++i) add(read(),read());
	DFS(1);
	cout << F[1][0] << endl;
}
