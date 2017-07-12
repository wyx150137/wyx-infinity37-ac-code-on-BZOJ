
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 300+5;
const int M = N*N*2;

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
	:next(_next), to(_to), val(_val){}
}edge[M];

inline void add(int x,int y,int z) {
	static int cnt = 0;
	edge[++cnt] = graph(head[x], y, z); head[x] = cnt;
}

int f[N][N], g[N][N];

int main() {
//	freopen("tt.in","r",stdin);
	int n = read(), m = read();
	for(int i=1;i<=m;++i) {
		int x = read(), y = read(), z = read();
		add(x ,y, z);
	}
	memset(f, 0x3f, sizeof f);
	for(int i=1;i<=n;++i) f[i][i] = 0;
	for(int i=1;i<=n;++i) {
		memcpy(g, f, sizeof g);
		for(int j=1;j<=n;++j) {
			for(int k=1;k<=n;++k) {
				for(int l=head[k];l;l=edge[l].next) {
					int y = edge[l].to;
					g[j][y] = min(g[j][y], f[j][k] + edge[l].val);
				}
			}
		}
		memcpy(f, g, sizeof f);
		for(int j=1;j<=n;++j) {
			if(f[j][j] < 0) {
				cout << i << endl;
				return 0;
			}
		}
	}
	puts("0");
}
