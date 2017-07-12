
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 2500+5;
const int M = N << 1;
typedef double f2;
typedef long double f4;
const f2 eps = 1e-9;

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

f2 F[N][N], a[N];
int K, n, head[N], fa[N], S[N], P[N], size[N];

struct graph {
	int next,to;
	graph () {}
	graph (int _next,int _to)
	:next(_next),to(_to){}
}edge[M];

inline void add(int x,int y) {
	static int cnt = 0; edge[++cnt] = graph(head[x],y); head[x] = cnt;
}

inline void DFS(int x) {
	size[x] = 1;
	int last = 0;
	register int i, j, k;
	if(x) F[x][1] = a[x], last = 1;
	else F[x][0] = 0;
	for(i=head[x];i;i=edge[i].next) DFS(edge[i].to), size[x] += size[edge[i].to];
	for(i=head[x];i;i=edge[i].next) {
		last += size[edge[i].to];
		for(j=last;j>=0;--j) 
			for(k=0;k<=size[edge[i].to]&&k<=j;++k) 
				F[x][j] = max(F[x][j],F[x][j-k] + F[edge[i].to][k]);
	}
}

inline bool check(f2 mid) {
	memset(F,0xc2,sizeof F);
	for(int i=1;i<=n;++i) a[i] = (f2)P[i] - (f2)S[i]*mid;
	DFS(0);
	return F[0][K] > -eps;
}

int main() {
	K = read(), n = read();
	for(int i=1;i<=n;++i) {
		S[i] = read(), P[i] = read();
		fa[i] = read(); add(fa[i],i);
	}
	f2 L = 0, R = 1e4;
	while(R-L>1e-5) {
		f2 mid = (L+R)/2.0;
		if(check(mid)) L = mid;
		else R = mid;
	}
	printf("%.3lf\n",(L+R)/2);
} 
