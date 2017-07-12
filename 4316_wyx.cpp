
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 5e4+5;
const int M = 120000+5;
const int inf = 1000000000;

int head[N];
struct graph {
	int next,to;
	graph () {}
	graph (int _next,int _to)
	:next(_next),to(_to){}
}edge[M];

inline void add(int x,int y) {
	static int cnt = 0 ;
	edge[++cnt] = graph(head[x],y); head[x] = cnt;
	edge[++cnt] = graph(head[y],x); head[y] = cnt;
}

int dfn[N], low[N], fa[N], depth[N], F[N][2], a[N][4], n, m;

void DFS(int be,int ed) {
	register int i,k;
	a[1][0] = F[ed][0], a[1][1] = -inf;
	a[1][2] = -inf, a[1][3] = F[ed][1];
	for(k=fa[ed],i=2;k!=fa[be];k=fa[k],++i) {
		a[i][0] = F[k][0] + max(a[i-1][0],a[i-1][1]);
		a[i][1] = F[k][1] + a[i-1][0];
		a[i][2] = F[k][0] + max(a[i-1][2],a[i-1][3]);
		a[i][3] = F[k][1] + a[i-1][2];
	}
	F[be][0] = max(F[be][0],max(a[i-1][0],a[i-1][2]));
	F[be][1] = max(F[be][1],a[i-1][1]);
}

void DFS2(int x) {
	static int cnt = 0;
	dfn[x] = low[x] = ++cnt;
	F[x][1] = 1;
	for(int i=head[x];i;i=edge[i].next) {
		if(edge[i].to != fa[x]) {
			if(!dfn[edge[i].to]) {
				fa[edge[i].to] = x;
				depth[edge[i].to] = depth[x] + 1;
				DFS2(edge[i].to);
			}
			low[x] = min(low[x],low[edge[i].to]);
			if(low[edge[i].to] > dfn[x]) {
				F[x][1] += F[edge[i].to][0];
				F[x][0] += max(F[edge[i].to][0],F[edge[i].to][1]);
			}
		}
	} 
	for(int i=head[x];i;i=edge[i].next) 
		if(fa[edge[i].to] != x && dfn[edge[i].to] > dfn[x]) DFS(x,edge[i].to);
}

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int main() {
	n = read(), m = read();
	for(int i=1;i<=m;++i) add(read(),read());
	DFS2(1); cout << max(F[1][0],F[1][1]) << endl;
}
