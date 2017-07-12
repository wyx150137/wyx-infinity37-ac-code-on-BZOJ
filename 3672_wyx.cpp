
#include <vector>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
#define pb push_back
typedef double f2;
typedef long long LL;
const int N = 2e5+5;
const int M = N << 2;
const LL inf = 1e18;
inline LL read() {
	LL x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int head[N] , n, T;

struct graph {
	int next, to, val;
	graph () {}
	graph (int _next,int _to,int _val)
	:next(_next), to(_to), val(_val) {}
}edge[M];

inline void add(int x,int y,int z) {
	static int cnt = 0;
	edge[++cnt] = graph(head[x], y, z); head[x] = cnt;
	edge[++cnt] = graph(head[y], x, z); head[y] = cnt;
}

int size[N], top[N], fa[N][23], depth[N], w[N];
LL dis[N];

inline void DFS1(int x) {
	size[x] = 1;
	for(int i=head[x];i;i=edge[i].next) 
		if(edge[i].to != fa[x][0]) {
			fa[edge[i].to][0] = x;
			depth[edge[i].to] = depth[x] + 1;
			dis[edge[i].to] = dis[x] + edge[i].val;
			DFS1(edge[i].to);
			size[x] += size[edge[i].to];
		}
}

inline void DFS2(int x,int chain) {
	static int cnt = 0;
	w[x] = ++cnt, top[x] = chain; int k = 0;
	for(int i=head[x];i;i=edge[i].next) {
		if(edge[i].to != fa[x][0] && size[k] < size[edge[i].to]) k = edge[i].to;
	}
	if(!k) return;
	DFS2(k,chain);
	for(int i=head[x];i;i=edge[i].next) {
		if(edge[i].to != fa[x][0] && edge[i].to != k) {
			DFS2(edge[i].to, edge[i].to);
		}
	}
}

struct poi {
	LL x, y;
	poi (LL _x=0, LL _y=0):x(_x),y(_y){}
	poi operator + (const poi &z) const{return poi(x+z.x,y+z.y);}
	poi operator - (const poi &z) const{return poi(x-z.x,y-z.y);}
	f2  operator ^ (const poi &z) const{return (f2)x*z.y-(f2)y*z.x;}
	bool operator < (const poi &z) const {
		return x != z.x ? x < z.x : y < z.y;
	}
} p[N], temp[N]; 

LL P[N], Q[N],L[N];

struct seg {
	vector <poi> V;
	int size;
	bool flag;
} tr[N<<2];

inline LL calc(int k,int j,int id) {

	return tr[k].V[j].y + P[id] * (dis[id] - tr[k].V[j].x) + Q[id];
}

inline void build(int k,int l,int r) {
	int top = 0;
	for(int i=l;i<=r+1;++i) tr[k].V.pb(poi(0,0));
	for(int i=l;i<=r;++i) temp[++top] = p[i];
	sort(temp+1,temp+top+1);
	tr[k].size = 0;
	for(int i=1;i<=top;++i) {
		while(tr[k].size > 1 && ((temp[i]-tr[k].V[tr[k].size])^(tr[k].V[tr[k].size]-tr[k].V[tr[k].size-1])) >= 0 )
			--tr[k].size;
		tr[k].V[++tr[k].size] = temp[i];
	} 
}

LL ask(int k,int id) {
	LL ans = inf;
	int l = 1, r = tr[k].size;
	while(r - l >= 3) {
		int mid1 = l+(r-l)/3, mid2 = r-(r-l)/3;
		if(calc(k,mid1,id) < calc(k,mid2,id)) r = mid2;
		else l = mid1;
	}
	for(int j=l;j<=r;++j) ans = min(ans, calc(k,j,id));
	return ans;
}

LL ask(int k,int l,int r,int x,int y,int id) {
	if(x <= l && r <= y) {
		if(!tr[k].flag) {
			tr[k].flag = 1;
			build(k,l,r);
		}
		return ask(k ,id);
	}
	int mid = (l+r) >> 1;
	LL ans = inf;
	if(x <= mid) ans = min(ans, ask(k<<1,l,mid,x,y,id));
	if(mid < y) ans = min(ans, ask(k<<1|1,mid+1,r,x,y,id));
	return ans;
}

LL ask(int x,int y,int id) {
	LL ans = inf;
	while(depth[top[x]] > depth[y]) {
		ans = min(ans, ask(1,1,n,w[top[x]], w[x], id));
		x = fa[top[x]][0];
	}
	ans = min(ans, ask(1,1,n,w[y],w[x], id));
	return ans;
}

int pre[N];
LL F[N];

inline int up(int x) {
	int ans = x;
	for(int i=22;~i;--i) {
		if(fa[ans][i] && dis[x] - dis[fa[ans][i]] <= L[x]) ans = fa[ans][i];
	}	
	return ans;
}

int main() {
//	freopen("tt.in","r",stdin);
//	freopen("ticket.in","r",stdin);
//	freopen("ticket.out","w",stdout);
	n = read(), T = read();
	for(int i=2;i<=n;++i) {
		fa[i][0] = read();
		int val = read();
		P[i] = read(), Q[i] = read(), L[i] = read();
		add(fa[i][0], i, val);
	}
	DFS1(1);
	DFS2(1,1);
	for(int j=1;j<=22;++j) for(int i=1;i<=n;++i) fa[i][j] = fa[fa[i][j-1]][j-1];
	for(int i=1;i<=n;++i) 
		pre[i] = up(i);
	F[1] = 0; p[w[1]] = poi(0,0);
	for(int i=2;i<=n;++i) {
		F[i] = ask(fa[i][0], pre[i], i);
		p[w[i]] = poi(dis[i], F[i]);
		printf("%lld\n",F[i]);
	}
}
