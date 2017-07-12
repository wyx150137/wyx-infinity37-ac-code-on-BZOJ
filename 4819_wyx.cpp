
#include <queue>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
typedef double f2;
const f2 inf = 1e17;
const int N = 200+5;
const int M = N * N;
int n;
f2 a[N][N], b[N][N];

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1; ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int head[N];

struct graph{
	int next, to; f2 val;  int f, from;
	graph () {}
	graph (int _next,int _to,f2 _val,int _f,int _from)
	:next(_next), to(_to), val(_val), f(_f), from(_from){} 
}edge[M];

int cnt = 1;

inline void add(int x,int y,f2 z,int f) {
	edge[++cnt] = graph(head[x],y,z,f, x); head[x] = cnt;
	edge[++cnt] = graph(head[y],x,-z,0,y); head[y] = cnt;
}

f2 dis[N];
bool in[N], vis[N], app[N];
int pre[N], s, t;

bool spfa() {
	queue <int> q;
	for (int i=s;i<=t;i++) dis[i]=-inf,app[i]=0;
	dis[s]=0;vis[s]=1; q.push(s);
	while (!q.empty()) {
		int tt = q.front(); q.pop(); app[tt] = 1; vis[tt] = false;
		for(int i=head[tt];i;i=edge[i].next) {
			if(edge[i].f && dis[tt] + edge[i].val > dis[edge[i].to]) {
				dis[edge[i].to] = dis[tt] + edge[i].val;
				pre[edge[i].to] = i;
				if(!vis[edge[i].to]) {
					vis[edge[i].to] = 1;
					q.push(edge[i].to);
				}
			}
		}
	}
	return app[t];
}

inline f2 mcmf() {
	int x = t,  Min = (int)1e5;
	f2 ans = 0;
	while(pre[x]) {
		Min = min(Min, edge[pre[x]].f);
		x = edge[pre[x]].from;
	}
	ans += Min * dis[t];
	x = t;
	while(pre[x]) {
		edge[pre[x]].f -= Min, 
		edge[pre[x]^1].f += Min;
		x = edge[pre[x]].from;
	}
	return ans;
}

inline bool check(f2 mid) {
	cnt = 1;
	memset(head, 0, sizeof head);
	for(int i=1;i<=n;++i) add(s,i,0,1);
	for(int i=1;i<=n;++i) add(i+n,t,0,1);
	for(int i=1;i<=n;++i) 
		for(int j=1;j<=n;++j) 
			add(i,j+n,(f2)a[i][j]-mid*b[i][j],1);
	f2 ans = 0;
	while(spfa()) 
		ans += mcmf();
	return ans <= 0;
}

int main() {
//	freopen("tt.in","r",stdin);
	n = read();
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=n;++j) a[i][j] = read();
	}
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=n;++j) b[i][j] = read();
	}
	f2 l = 0, r = 10000;
	int T = 50;
	s = 0, t = n<<1|1;
	while(T--) {
		f2 mid = (l+r)/2;
		if(check(mid)) r = mid;
		else l = mid; 
	}
	printf("%.6lf\n", l);
}
