
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

const int N = 50+5;
const int M = N << 1;
int n, m, tot;

int head[N];

struct graph {
	int next,to;
	graph () {}
	graph (int _next,int _to)
	:next(_next),to(_to){}
}edge[M];

inline void add(int x,int y)  {
	static int cnt = 0;
	edge[++cnt] = graph(head[x],y); head[x] = cnt;
	edge[++cnt] = graph(head[y],x); head[y] = cnt;
}

LL F[N][N];
int a[N];

bool mp[N][N];

inline void DFS(int x,int fa) {
	for(int i=head[x];i;i=edge[i].next) {
		if(edge[i].to != fa) {
			DFS(edge[i].to,x);
		}
	}
	for(int i=1;i<=tot;++i) F[x][i] = 1;
	for(int i=head[x];i;i=edge[i].next)if(edge[i].to != fa) {
		for(int j=1;j<=tot;++j) {
			LL tmp = 1;
			for(int k=1;k<=tot;++k) 
				if(mp[a[j]][a[k]]) tmp += F[edge[i].to][k];
			F[x][j] *= tmp;
		}
	}
}

int main() {
	n = read(), m = read(); int x, y;
	for(int i=1;i<=m;++i) x = read(), y = read(), mp[x][y] = mp[y][x] = 1;
	for(int i=1;i<n;++i) x = read(), y = read(), add(x,y);
	int Max = (1<<n) - 1;  
	LL ans = 0;
	for(int i=1;i<=Max;++i) {
		LL now = 0; tot = 0;
		for(int j=1;j<=n;++j) if((1<<(j-1))&i) a[++tot] = j;
		DFS(1,-1); for(int j=1;j<=tot;++j) now += F[1][j];
		if((tot&1)== (n&1)) ans += now;
		else ans -= now;
	}
	cout << ans << endl;
}
