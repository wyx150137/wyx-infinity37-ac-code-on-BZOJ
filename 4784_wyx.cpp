
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 5e5+5;
const int M = N << 1;
const int mod = 998244353;
typedef long long LL;
using namespace std;

bool is_cactus, vis[N+5];
LL F[N+5], H[N+5], G[N+5];
int col[N+5];

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int head[N];

struct graph{
	int from, next, to;
	bool ban;
	graph () {}
	graph (int _from,int _next,int _to,bool _ban = true)
	:from(_from),next(_next),to(_to),ban(_ban){}
}edge[M];

int cnt = 1;

inline void add(int x,int y) {
	edge[++cnt] = graph(x,head[x],y,1); head[x] = cnt;
	edge[++cnt] = graph(y,head[y],x,1); head[y] = cnt;
}

int low[N], dfn[N], times;
int stack[N], top;

inline void DFS(int x, int fa) {
	dfn[x] = low[x] = ++times;
	stack[++top] = x;
	bool flag = false;
	for(int i=head[x];i;i=edge[i].next) {
		if(edge[i].to != fa)  {
			if(!dfn[edge[i].to]) {
				DFS(edge[i].to,x);
				low[x] = min(low[x],low[edge[i].to]);
				if(low[edge[i].to] < dfn[x]) {
					if(flag) {
						is_cactus = false;
						return;
					}
					else flag = true;
				}
			}
			else {
				low[x] = min(low[x],dfn[edge[i].to]);
				if(low[edge[i].to] < dfn[x]) {
					if(flag) {
						is_cactus = false;
						return;
					}
					else flag = true;
				}
			}
		}
	}
	if(low[x] == dfn[x])  {
		while(1) {
			col[stack[top--]] = x;
			if(stack[top+1] == x) break;
		}
	}
}

void DFS2(int x,int fa) {
//	cout << x << endl;
	vis[x] = 1, F[x] = 1, G[x] = 0;
	int cnt = 0;
	for(int i=head[x];i;i=edge[i].next) {
		if(edge[i].ban && edge[i].to != fa) {
			DFS2(edge[i].to,x);
			F[x] = F[x] * G[edge[i].to] % mod;
			cnt ++;
		}
	}
//cout << x << endl;
//	cout << x << " " << cnt << endl;
	if(cnt > 0)
		G[x] = (F[x] * H[cnt] + F[x] * H[cnt-1]  % mod * cnt)  % mod;
	else 
		G[x] = (F[x] * H[cnt])  % mod;
	F[x] = F[x] * H[cnt] % mod;
//	cout << F[x] << endl;
//	printf("f[%d] = %d, G[%d] = %d\n", x, F[x], x, G[x]);
}

inline void init(int x) {
	for(int i=1;i<=x;++i) head[i] = 0, col[i] = 0, dfn[i] = 0, low[i] = 0, vis[i] = false;
	cnt = 1; is_cactus = true; times = 0; top = 0;
}

int main() {
	//freopen("03.in","r",stdin);
	H[0] = H[1] = 1;
	for(int i=2;i<N;++i) H[i] = (H[i-1] + (i-1) * H[i-2]) % mod;
	int T; cin >> T;
	while(T--) {
		int n = read(), m = read();
		init(n);
		for(int i=1;i<=m;++i) add(read(),read());
		DFS(1,-1);
		if(!is_cactus) {
			puts("0");
			continue;
		}
		for(int i=2;i<=cnt;++i) if(col[edge[i].from] == col[edge[i].to]) edge[i].ban = false;
		LL ans = 1;
		for(int i=1;i<=n;++i) 
			if(!vis[i]) {
				DFS2(i,-1);
				ans = ans * F[i] % mod;
			}
		printf("%lld\n", ans);
	}
	return 0;
}
