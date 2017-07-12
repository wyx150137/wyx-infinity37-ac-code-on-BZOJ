
#include <map>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 5e5+5;
const int M = N << 1;
using namespace std;
typedef long long LL;
inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

map <int,int> id;
int val[N], deg[N], sum, mx;
bool vis[N];
LL ans;

int head[N];

struct graph {
	int next, to, val;
	graph () {}
	graph (int _next,int _to)
	:next(_next), to(_to){}
}edge[M];

inline void add(int x,int y) {
	static int cnt = 0;
	edge[++cnt] = graph(head[x], y); head[x] = cnt; deg[x] ++;
	edge[++cnt] = graph(head[y], x); head[y] = cnt; deg[y] ++;
} 

inline void DFS(int x) {
	if(vis[x]) return;
	vis[x]  = 1;
	mx = max(mx, val[x]);
	ans += (LL)val[x] * (deg[x]-1);
	sum += deg[x] - 2;
	for(int i=head[x];i;i=edge[i].next) {
		if(!vis[edge[i].to])
			DFS(edge[i].to);
	}
}

int cnt;

int main() {
	int n = read();
	for(int i=1;i<=n;++i) {
		int x = read(), y = read();
		if(!id.count(x)) {
			id[x] = ++ cnt;
			val[cnt] = x;
		}
		if(!id.count(y)) {
			id[y] = ++ cnt;
			val[cnt] = y;
		}
		add(id[x], id[y]);
	}
	for(int i=1;i<=cnt;++i) {
		if(!vis[i]) {
			sum = 0;
			mx = 0;
			DFS(i);
			if(sum < 0) ans += mx;
		}
	}
	cout << ans << endl;
}
