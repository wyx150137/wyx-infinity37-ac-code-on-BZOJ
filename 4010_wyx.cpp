
#include <queue>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 1e5+5;
const int M = N;

int n, m, deg[N], ans[N], head[N];

struct graph {
	int next,to;
	graph () {}
	graph (int _next,int _to)
	:next(_next),to(_to){}
}edge[M];

int cnt;

inline void add(int x,int y) {
	deg[y] ++; edge[++cnt] = graph(head[x],y); head[x] = cnt;
}

priority_queue <int> q;

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int main() {
	int T = read();
	while(T -- ) {
		memset(head,0,sizeof head);
		memset(deg,0,sizeof deg);
		n = read(), m = read(); cnt = 0;
		for(int i=1;i<=m;++i) {
			int x = read(), y = read(); add(y,x);
		}
		for(int i=1;i<=n;++i) if(!deg[i]) q.push(i);
		int tot = 0;
		while(!q.empty()) {
			int tt = q.top(); q.pop(); ans[++tot] = tt;
			for(int i=head[tt];i;i=edge[i].next) if(!--deg[edge[i].to]) q.push(edge[i].to);
		}
		if(tot == n) {for(int i=n;i;--i) printf("%d ", ans[i]);puts("");}
		else puts("Impossible!");
	}
}
