
#include <cmath>
#include <queue>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 600 +5;
const int M = N*N;
const int inf = 0x7fffffff;

int head[N], x, y, n;

struct graph {
	int next,to,val;
	graph () {}
	graph (int _next,int _to,int _val)
	:next(_next),to(_to),val(_val){}
}edge[M];

inline void add(int x,int y,int z) {
	static int cnt = 1;
	edge[++cnt] = graph(head[x],y,z); head[x] = cnt;
	edge[++cnt] = graph(head[y],x,0); head[y] = cnt;
}

int depth[N], S, T;

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

struct poi {
	int x,y;
	void R() {
		x = read(), y = read();
	}
};

inline double dis(poi x,poi y) {
	return sqrt((x.x-y.x)*(x.x-y.x) + (x.y-y.y)*(x.y-y.y));
}

struct data {
	int opt; poi tmp1,tmp2;
	int r;
	void R() {
		opt = read(); tmp1.R();
		if(opt == 1) r = read();
		else tmp2.R();
	}
}a[N];

inline bool in(poi &x,data &y) {
	if(x.x >= y.tmp1.x && x.x <= y.tmp2.x && x.y >= y.tmp2.y && x.y <= y.tmp1.y) return true;
	return false;
}

bool check(int x,int y) {
	if(a[x].opt == 1 && a[y].opt == 1) return (dis(a[x].tmp1,a[y].tmp1) <= a[x].r + a[y].r);
	else if(a[x].opt == 2  && a[y].opt == 2) {
		poi tmp1 = a[x].tmp1, tmp2 = a[x].tmp2;
		poi tmp3 = (poi){a[x].tmp1.x,a[x].tmp2.y};
		poi tmp4 = (poi){a[x].tmp2.x,a[x].tmp1.y};
		if(in(tmp1,a[y]) || in(tmp2,a[y]) || in(tmp3,a[y]) || in(tmp4,a[y])) return true;
		return false;
	}  
	else {
		if(a[x].opt == 1 && a[y].opt == 2) swap(x,y);
		poi tmp1 = a[x].tmp1, tmp2 = a[x].tmp2;
		poi tmp3 = (poi){a[x].tmp1.x,a[x].tmp2.y};
		poi tmp4 = (poi){a[x].tmp2.x,a[x].tmp1.y};
		if(dis(tmp1,a[y].tmp1) <= a[y].r || dis(tmp2,a[y].tmp1) <= a[y].r || dis(tmp3,a[y].tmp1) <= a[y].r || dis(tmp4,a[y].tmp1) <= a[y].r) return true;
		if(a[y].tmp1.x >= a[x].tmp1.x && a[y].tmp1.x <= a[x].tmp2.x && (abs(a[y].tmp1.y-a[x].tmp1.y) <= a[y].r|| abs(a[y].tmp1.y-a[x].tmp2.y) <= a[y].r) ) return true;
		if(a[y].tmp1.y >= a[x].tmp2.y && a[y].tmp1.y <= a[x].tmp1.y && (abs(a[y].tmp1.x-a[x].tmp1.x) <= a[y].r|| abs(a[y].tmp1.x-a[x].tmp1.x) <= a[y].r) ) return true;
		return false; 
	}
}

bool BFS() { queue <int> q;
	memset(depth,-1,sizeof depth); depth[S] = 0; q.push(S);
	while(!q.empty()) {
		int tt = q.front(); q.pop();
		for(int i=head[tt];i;i=edge[i].next) 
			if(depth[edge[i].to] < 0 && edge[i].val) {
				depth[edge[i].to] = depth[tt] + 1;
				q.push(edge[i].to); 
			}
	}
	return ~depth[T];
}

inline int DFS(int x,int f) {
	if(x == T) return f;
	int w, used = 0;
	for(int i=head[x];i;i=edge[i].next) 
		if(depth[edge[i].to] == depth[x] + 1 && edge[i].val) {
			w = DFS(edge[i].to,min(f-used,edge[i].val));
			edge[i].val -= w, edge[i^1].val += w; used += w;
			if(used == f) return f;
		}
	depth[x] = -1;
	return used;
}

int table[N][2];

int main() {
	int cnt = 0;
	x = read(), y = read(), n = read(), T = 1;
	for(int i=1;i<=n;++i) table[i][0] = ++cnt, table[i][1] = ++cnt; S = ++ cnt, T = ++cnt;
	register int i,j;
	for(i=1;i<=n;++i) {
		a[i].R();
		add(table[i][0],table[i][1],1);
		for(j=1;j<i;++j) if(check(i,j)) add(table[i][1],table[j][0],inf), add(table[j][1],table[i][0],inf);
		if(a[i].opt == 1) {
			if(a[i].tmp1.y - a[i].r <= 0) add(S,table[i][0],inf);
			if(a[i].tmp1.y + a[i].r >= y) add(table[i][1],T,inf);
		}
		else {
			if(a[i].tmp1.y <= 0 ) add(S,table[i][0],inf);
			if(a[i].tmp2.y >= y ) add(table[i][1],T,inf);
		}
	}
	int ans = 0;
	while(BFS()) ans += DFS(S,inf);
	cout << ans << endl;
}
