
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 200000+5;
const int M = N << 1;

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int head[N];

struct graph {
	int next,from,to;
	graph () {}
	graph (int _next,int _to)
	:next(_next),to(_to){}
}edge[M];

inline void add(int x,int y) {
	static int cnt = 0;
	edge[++cnt] = graph(head[x],y); head[x] = cnt;
	edge[++cnt] = graph(head[y],x); head[y] = cnt;
}

int F[N], Max[N], fa[N], val[N], lmt[N];

struct data {
	int val, x;
	bool operator < (const data &z) const {
		return val > z.val;
	}
}a[N];

inline void DFS(int x) {
	int i;
	for(i=head[x];i;i=edge[i].next) {
		if(edge[i].to != fa[x]) {
			fa[edge[i].to] = x;
			DFS(edge[i].to);
		}
	}
	int cnt = 0;
	for(i = head[x]; i; i = edge[i].next) 
		if(edge[i].to != fa[x]) 
			a[++cnt] = (data) {Max[edge[i].to], edge[i].to};
	sort(a+1,a+cnt+1);
	int sum = 1;
	for(i=1;i<=cnt;++i) {
		if(a[i].val < 0 || sum == lmt[x]) break;
		sum ++; Max[x] += a[i].val; F[x] |= F[a[i].x];
		if(a[i].val == 0) F[x] = true;
	}
	if(sum < lmt[x] && i <= cnt && cnt != 0) if(a[i].val == a[i-1].val) F[x] = 1;
	Max[x] += val[x];
}

int main() {
//	freopen("01.in","r",stdin);
	int n = read();
	register int i;
	for(i=2;i<=n;++i) val[i] = read();
	for(i=2;i<=n;++i) lmt[i] = read();
	for(i=1;i<n;++i) add(read(),read());
	DFS(1);
	cout << Max[1] << endl;
	puts(!F[1] ? "solution is unique" : "solution is not unique");
}
