
#include <queue>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 10010;
const int M = N << 2;
const int inf = 0x3f3f3f3f;

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int head[N];

struct graph {
	int next, to, val, f, from;
	graph () {}
	graph (int _next,int _to,int _val,int _f,int _from)
	:next(_next), to(_to), val(_val), f(_f), from(_from) {}
} edge[M];

inline void add(int x,int y,int z,int f) {
	static int cnt = 1;
	edge[++cnt] = graph(head[x], y, z, f, x); head[x] = cnt;
	edge[++cnt] = graph(head[y], x,-z, 0, y); head[y] = cnt;
}

int from[N], dis[N], s, t;
bool in[N];

inline bool spfa() {
	queue <int> q;
	memset(dis, -1, sizeof dis);
	dis[s] = 0; in[s] = 1; q.push(s);
	while(!q.empty()) {
		int tt = q.front(); q.pop(); in[tt] = false;
		for(int i=head[tt];i;i=edge[i].next) {
			if(dis[edge[i].to] < dis[tt] + edge[i].val && edge[i].f) {
				from[edge[i].to] = i;
				dis[edge[i].to] = dis[tt] + edge[i].val;
				if(!in[edge[i].to]) {
					in[edge[i].to] = 1;
					q.push(edge[i].to);
				}
			}
		}
	}
	return dis[t] != -1;
}

inline int mcmf() {
	int ans = 0;
	int Min = inf, x = from[t];
	while(x) {
		Min = min(Min, edge[x].f);
		x = from[edge[x].from];
	}
	x = from[t];
	while(x) {
		edge[x].f -= Min;
		edge[x^1].f += Min;
		ans += Min * edge[x].val;
		x = from[edge[x].from];
	}
	return ans;
}

int main() {
//	freopen("tt.in","r",stdin);
	int n = read(), m = read(), k = read();
	s = 0, t = n + 1;
	for(int i=1;i<=n;++i) {
		int x = read();
		add(i-1, i, 0, k);
		if(i + m <= n) add(i, i+m, x, 1);
		else add(i, t, x, 1);
	}
	add(n, t, 0, k);
	int ans = 0;
	while(spfa()) {
		ans += mcmf();
	}
	cout << ans << endl;
}
