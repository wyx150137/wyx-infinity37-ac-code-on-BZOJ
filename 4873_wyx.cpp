
#include <queue>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
const int inf = 1000000000;
const int N = 1e4+5;
const int M = 1e6+5;

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int head[N];

struct graph {
	int next, to, val;
	graph () {}
	graph (int _next,int _to,int _val)
	:next(_next), to(_to), val(_val) {}
}edge[M];

inline void add(int x,int y,int z) {
	static int cnt = 1;
	edge[++cnt] = graph(head[x],y,z); head[x] = cnt;
	edge[++cnt] = graph(head[y],x,0); head[y] = cnt;
}

int num[100+5][100+5], val[100+5][100+5], n, m, a[100+5], s, t;
int depth[N];

bool BFS() {
	queue <int> q;
	memset(depth, -1, sizeof depth);
	depth[s] = 0; q.push(s);
	while(!q.empty()) {
		int tt = q.front(); q.pop();
		for(int i=head[tt];i;i=edge[i].next) {
			if(depth[edge[i].to] < 0 && edge[i].val) {
				depth[edge[i].to] = depth[tt] + 1;
				q.push(edge[i].to);	
			}
		}
	}
	return ~depth[t];
}

inline int DFS(int x,int f) {
	if(x == t) return f;
	int used = 0, w;
	for(int i=head[x];i;i=edge[i].next) {
		if(depth[edge[i].to] == depth[x] + 1 && edge[i].val) {
			w = DFS(edge[i].to, min(edge[i].val, f-used));
			edge[i].val -= w, edge[i^1].val += w; used += w;
			if(used == f) return used;
		}
	}
	depth[x] = -1;
	return used;
}

int main() {
//	freopen("sushi.in","r",stdin);
//	freopen("sushi.out","w",stdout);
	int ans = 0;
	n = read(), m = read();
	for(int i=1;i<=n;++i) a[i] = read();
	s = 1001, t = 1002;
	int cnt = t;
	for(int i=1;i<=1000;++i) add(i, t, m*i*i);
	for(int i=1;i<=n;++i) {
		for(int j=i;j<=n;++j) num[i][j] = ++cnt, val[i][j] = read();
	}
	int x;
	for(int i=1;i<=n;++i) {
		for(int j=i;j<=n;++j) {
			x = val[i][j];
			if(i==j) {
				x -= a[i];
				add(num[i][j], a[i], inf);
			} 
			if(x > 0)  {
				add(s, num[i][j], x);
				ans += x;
			}
			else add(num[i][j], t, -x);
			if(i!=j) {
				add(num[i][j], num[i+1][j], inf);
				add(num[i][j], num[i][j-1], inf);
			}
		}
	}
	while(BFS())
		ans -= DFS(s, inf);
	cout << ans << endl;
}
