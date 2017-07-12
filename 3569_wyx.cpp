
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
const int M = 1e6+5;
typedef unsigned long long ull;

inline ull Rand() {
    return ((((ull)rand()) << 32) | ((ull)rand())) & ((1llu << 40) - 1);
}

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
	:next(_next), to(_to){}
}edge[M];

inline void add(int x,int y) {
	static int cnt = 1;
	edge[++cnt] = graph(head[x],y); head[x] = cnt;
	edge[++cnt] = graph(head[y],x); head[y] = cnt;
}

int dfn[N];
ull w[M], val[N];

inline void DFS1(int x,int fa) {
	static int cnt = 0;
	dfn[x] = ++cnt;
	for(int i=head[x];i;i=edge[i].next ) {
		if(edge[i].to != fa) {
			if(!dfn[edge[i].to]) {
				DFS1(edge[i].to, x);
			}
			else if(dfn[edge[i].to] < dfn[x]) {
				w[i>>1] = Rand();
				val[x] ^= w[i>>1];
				val[edge[i].to] ^= w[i>>1];
			}
		}
	}
}

inline void DFS2(int x,int fa) {
	static int cnt = 0;
	dfn[x] = ++cnt;
	for(int i=head[x];i;i=edge[i].next) {
		if(edge[i].to != fa) {
			if(!dfn[edge[i].to]) {
				DFS2(edge[i].to,x);
				w[i>>1] = val[edge[i].to];
				val[x] ^= w[i>>1];
			}
		}
	}
}

struct data {
	ull a[66];

	inline void init() {
		memset(a, 0, sizeof a);
	}

	void insert(int x) {
		for(int j=63;~j;--j) {
			if((x>>j)&1) {
				if(a[j]) x ^= a[j];
				else {
					a[j] = x;
					break;
				}
			}
		}
	}

	inline bool check(int k) {
		int cnt = 0;
		for(int i=0;i<=63;++i) {
			if(a[i]) cnt ++;
		}
		return (cnt == k);
	}
} Ans;

int main() {
//s	freopen("tt.in", "r", stdin);
	srand(150137);

	int n = read(), m = read();
	for(int i=1;i<=m;++i) {
		int x = read(), y = read();
		add(x,y);
	}

	DFS1(1,-1);
//	for(int i=1;i<=n;++i) cout << dfn[i] << " " ;
	memset(dfn, 0, sizeof dfn);
	DFS2(1,-1);

	int lastans = 0;
	int q = read();
	while(q--) {
		int K = read();
		Ans.init();
		for(int i=1;i<=K;++i) {
			int tmp = read() ^ lastans;
			Ans.insert(w[tmp]);
		}
		if(Ans.check(K)) {
			lastans ++;
			puts("Connected");
		}
		else puts("Disconnected");
	}
}

