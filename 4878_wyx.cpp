
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 1000+5;
const int M = 20 * N;
using namespace std;

int head[N], cnt;

struct graph {
	int next, to;
	graph () {}
	graph (int _next,int _to)
	:next(_next), to(_to) {}
}edge[M];

inline void add(int x,int y) {
	edge[++cnt] = graph(head[x], y); head[x] = cnt;
	edge[++cnt] = graph(head[y], x); head[y] = cnt;
}

int n, m, pos;
int vis[N];
int col[N];

inline void DFS(int x) {
	pos ++;
	int i;
	for(i = head[x]; i; i = edge[i].next) if(col[edge[i].to]) vis[col[edge[i].to]] = pos;
	for(i = 1; ; ++ i) if(vis[i] < pos) { col[x] = i; break; }
	for(i = head[x]; i; i = edge[i].next) if(!col[edge[i].to]) DFS(edge[i].to);
}

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int stack[N];

int main() {
	int T = read();
	while(T--) {
		cnt = pos = 0;
		int n = read() , m = read(), K = read();
		for(int i=1;i<=n;++i) head[i] = 0, col[i] = 0, vis[i] = 0;
		for(int i=1;i<=m;++i) {
			int x = read(), y = read();
			add(x, y);
		}
		for(int i=1;i<=n;++i) if(!col[i]) DFS(i);
		int Max = 0;
		for(int i=1;i<=n;++i) Max = max(Max, col[i]);
		if(Max <= K) {
			printf("color");
			for(int i=1;i<=n;++i) printf(" %d", col[i]);
			puts("");
		}
		else {
			int x;
			for(int i=1;i<=n;++i) if(col[i] == K + 1) x = i;
			stack[1] = x;
			for(int top = 1; top <= K; ++ top) {
				int tt = stack[top];
				for(int i = head[tt]; i; i = edge[i].next) {
					if(col[edge[i].to] == col[tt] - 1) {
						stack[top+1] = edge[i].to;
						break;
					}
				}
			}
			printf("path");
			for(int i=1;i<=K+1;++i) printf(" %d", stack[i]);
			puts("");
		}
	}
}
