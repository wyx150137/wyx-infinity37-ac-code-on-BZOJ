
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 100+5;
const int M = N << 1;
inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9') {if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9') {x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int F[N][N][2];

int head[N],fa[N];

struct graph {
	int next,to;
	graph () {}
	graph (int _next,int _to)
	:next(_next),to(_to){}
}edge[M];

inline void add(int x,int y) {
	static int cnt = 0;
	edge[++cnt] = graph(head[x],y); head[x] = cnt;
	edge[++cnt] = graph(head[y],x); head[y] = cnt; 
}

int n, lmt, dis[N];

inline void DFS(int x) {
	F[x][0][0] = F[x][0][1] = 1;
	for(int i=head[x];i;i=edge[i].next) {
		if(edge[i].to != fa[x]) {
			fa[edge[i].to] = x;
			dis[edge[i].to] = dis[x] + 1;
			DFS(edge[i].to);
		}
	}
	for(int i=head[x];i;i=edge[i].next) {
		if(edge[i].to != fa[x]) {
			for(int j=lmt;j>=0;--j) {
				for(int k=0;k<j;++k) {
					if(j-k-1>=0)F[x][j][0] = max(F[x][j][0], F[edge[i].to][k][0]+F[x][j-k-1][1]);
					if(j-k-1>=0)F[x][j][0] = max(F[x][j][0], F[edge[i].to][k][1]+F[x][j-k-1][1]);
					if(j-k-2>=0)F[x][j][1] = max(F[x][j][1], F[edge[i].to][k][1]+F[x][j-k-2][1]);
					if(j-k-2>=0)F[x][j][0] = max(F[x][j][0], F[edge[i].to][k][1]+max(F[x][j-k-2][0],F[x][j-k-2][1]));
				}
			}
		}
	}
}

int main() {
//	freopen("tt.in","r",stdin);
	n = read(), lmt = read();
	for(int i=2;i<=n;++i) {
		int x = read()+1, y = read()+1;
		add(x,y);
	}	
	DFS(1);
	int ans = 0;
	for(int i=0;i<=lmt;++i) ans = max(ans, F[1][i][1]), ans = max(ans, F[1][i][0]);
	cout << ans << endl;
}

