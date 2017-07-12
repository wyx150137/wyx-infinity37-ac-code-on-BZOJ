
#include <bitset>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 3e4+5;
const int M = 1e5+5;

int head[N];

struct graph {
	int next,to;
	graph () {}
	graph (int _next,int _to)
	:next(_next),to(_to){}
}edge[M];

inline void add(int x,int y) {
	static int cnt = 0;
	edge[++cnt] = graph(head[x],y);
	head[x] = cnt;
}

int deg[N], q[N], len[N];
int ans;

struct data {
	int x,val;
	bool operator < (const data &z) const {
		return val > z.val;
	}
}a[N];

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

bitset <N> F[N];


int main() {
	int n = read(), m = read();
	for(int i=1;i<=m;++i) {
		int x = read(), y = read();
		add(x,y); deg[y] ++;
	}
	int l = 1,r = 0;
	for(int i=1;i<=n;++i) if(!deg[i]) q[++r] = i;
	while(l<=r) {
		int tt = q[l++];
		for(int i=head[tt];i;i=edge[i].next) 
			if(!--deg[edge[i] .to]) q[++r] = edge[i].to;
	}
	for(int i=r;i>=1;--i) {
		int tt = q[i], tot = 0;
		F[tt][tt] = 1, len[tt] = 1;
		for(int j=head[tt];j;j=edge[j].next) {
			a[++tot] = (data){edge[j].to,len[edge[j].to]};
			len[tt] = max(len[tt],len[edge[j].to]+1);
		}
		sort(a+1,a+tot+1);
		for(int j=1;j<=tot;++j) {
			if(F[tt][a[j].x]) ans ++;
			F[tt] |= F[a[j].x];
		}
	}
	cout << ans << endl;
}
