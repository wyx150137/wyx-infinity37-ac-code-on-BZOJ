
#include <queue>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e4+5;
const int M = N<<2;
const int inf = 0x3f3f3f3f;

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
	static int cnt= 0 ;
	edge[++cnt] = graph(head[x],y,z); head[x] = cnt;
	edge[++cnt] = graph(head[y],x,z); head[y] = cnt;
}

int F[N][(1<<8)+10];
int n, d, m, all;

inline void init() {
	memset(F,0x3f,sizeof F);
	int cnt = 0;
	for(int i=1;i<=d;++i) F[i][1<<cnt] = 0, cnt ++;
	for(int i=n-d+1;i<=n;++i) F[i][1<<cnt] = 0, cnt ++;
	all = (1 << cnt) -1;
}

queue <int> q;
bool in[N];

inline void spfa(int sta) {
	while(!q.empty()) {
		int tt = q.front(); q.pop(); in[tt] = false;
		for(int i=head[tt];i;i=edge[i].next) {
			if(F[edge[i].to][sta] > F[tt][sta] + edge[i].val) {
				F[edge[i].to][sta] = F[tt][sta] + edge[i].val;
				if(!in[edge[i].to]) {
					in[edge[i].to] = 1;
					q.push(edge[i].to);
				}
			}
		}
	}
}

inline void solve() {
	for(int s=0;s<=all;++s) {
		for(int i=1;i<=n;++i) {
			for(int t=s;t;t=(t-1)&s) {
				F[i][s] = min(F[i][s], F[i][t]+F[i][s-t]);
				if(F[i][s] != inf) {
					q.push(i);
					in[i] = 1;
				}
			}
		}
		spfa(s);
	}
}

int ans[N];

bool check(int sta) {
	for(int i=0,j=(d<<1)-1; i<d; i++,j--)
		if(((sta & (1<<i))== 0) != ((sta & (1<<j))==0) ) 
			return false;
	return 1;
}

int main() {
//	freopen("tt.in","r",stdin);
	n = read(), m = read(), d = read();
	for(int i=1;i<=m;++i) {
		int x = read(), y = read(), z = read();
		add(x, y, z);
	}
	init();
	solve();
	memset(ans, 0x3f, sizeof ans);
	for(int i=0;i<=all;++i) if(check(i))
		for(int j=1;j<=n;++j) ans[i] = min(ans[i], F[j][i]);
	for(int s=0;s<=all;++s) {
		for(int t=s;t;t=(t-1)&s) ans[s] = min(ans[s], ans[t]+ans[s-t]);
	}
	if(ans[all] == inf) puts("-1");
	else cout << ans[all] << endl;
}
