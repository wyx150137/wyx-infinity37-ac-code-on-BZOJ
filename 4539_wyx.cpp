
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 1e5+5;
const int M = N << 2;
const int Max = 2200000;

int root[N], from[N], idx, dfn[N], out[N];
int n, m, q;

LL cnt[N], nn;

inline LL read() {
	LL x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

struct seg {
	int ls[Max],rs[Max],root[N];
	int tr[Max], sz;
	inline void insert(int x,int &y,int l,int r,int pos,int val) {
		y = ++sz;ls[y] = ls[x], rs[y] = rs[x], tr[y] = tr[x] + val;
		if(l==r) return; int mid = (l+r) >> 1;
		if(pos <= mid) insert(ls[x],ls[y],l,mid,pos,val);
		else insert(rs[x],rs[y],mid+1,r,pos,val);
	}
	void insert(int x,int val) {
		insert(root[x-1],root[x],1,n,val,1);
	}
	int ask(int x,int y,int l,int r,int kth) {
		if(l==r) return l; int mid  = (l+r) >> 1;
		int tmp = tr[ls[y]] - tr[ls[x]];
		if(tmp >= kth) return ask(ls[x],ls[y],l,mid,kth);
		else return ask(rs[x],rs[y],mid+1,r,kth - tmp);
	}
	inline int ask(int x,int y,int kth) {
		return ask(root[x-1],root[y],1,n,kth);
	}
}T;

struct Graph{
	int head[N],fa[N][20], size[N], depth[N];
	LL dis[N];

	struct graph{
		int next,to;
		LL val;
		graph () {}
		graph (int _next,int _to,LL _val)
		:next(_next),to(_to),val(_val){}
	}edge[M];

	inline void add(int x,int y,LL z){
		static int cnt = 0;
		edge[++cnt] = graph(head[x],y,z); head[x] = cnt;
		edge[++cnt] = graph(head[y],x,z); head[y] = cnt;
	}

	void DFS(int x) {
		for(int i=1;i<=19;++i) fa[x][i] = fa[fa[x][i-1]][i-1];
		for(int i=head[x];i;i=edge[i].next) {
			if(edge[i].to != fa[x][0]) {
				fa[edge[i].to][0] = x;
				depth[edge[i].to] = depth[x] + 1;
				dis[edge[i].to] = dis[x] + edge[i].val;
				DFS(edge[i].to);
			}
		}
 	}

 	void DFS2(int x) {
 		static int cnt = 0; size[x] = 1;
 		T.insert(dfn[x] = ++cnt,x);
 		for(int i=head[x];i;i=edge[i].next) {
 			if(edge[i].to != fa[x][0]) {
 				DFS2(edge[i].to);
 				size[x] += size[edge[i].to];
 			}
 		}
 		out[x] = cnt;
 	}

 	inline int lca(int x,int y) {
 		if(depth[x] < depth[y]) swap(x,y);
 		int tt = depth[x] - depth[y];
 		for(int i=19;~i;--i) if((1<<i)&tt) x = fa[x][i];
 		for(int i=19;~i;--i) if(fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
 		return x == y ? x : fa[x][0];
 	}

 	inline LL calc(int x,int y) {
 		return dis[x] + dis[y] - (dis[lca(x,y)]<< 1) ;
 	}

 	inline int up(int x,int y) {
 		int tt = depth[x] - depth[y] - 1;
 		for(int i=19;~i;--i) if((1<<i)&tt) x = fa[x][i];
 		return x;
 	}
}ori,g;

inline int get(LL x) {
	return lower_bound(cnt+1,cnt+idx+1,x) - cnt;
}

LL Query(LL a,LL b) {
	int ida = get(a), rta = root[ida], aa = T.ask(dfn[rta],out[rta],a-cnt[ida-1]);
	int idb = get(b), rtb = root[idb], bb = T.ask(dfn[rtb],out[rtb],b-cnt[idb-1]);
	int lca = g.lca(ida,idb);
	if(ida == idb) return ori.calc(aa,bb);
	LL res = g.calc(ida,idb) + ori.dis[aa] - ori.dis[rta] + ori.dis[bb] - ori.dis[rtb];
	if(ida == lca) {
		int tmpb = from[g.up(idb,lca)];
		res -= ori.dis[aa] + ori.dis[tmpb] - ori.calc(aa,tmpb) - 2 * ori.dis[rta];
	}
	else if(idb == lca) {
		int tmpa = from[g.up(ida,lca)];
		res -= ori.dis[bb] + ori.dis[tmpa] - ori.calc(bb,tmpa) - 2 * ori.dis[rtb];
	}
	else {
		int tmpa = from[g.up(ida,lca)], 
			tmpb = from[g.up(idb,lca)];
		res -= ori.dis[tmpa] + ori.dis[tmpb] - ori.calc(tmpa,tmpb) - 2*ori.dis[root[lca]];
	}
	return res;
}

int Q;

int main() {
//	freopen("4539.in","r",stdin);
	n = read(), m = read(), Q = read();
	LL x,y;
	for(int i=1;i<n;++i) { x = read(), y = read(); ori.add(x,y,1); }
	ori.DFS(1);
	ori.DFS2(1);
	nn = n, cnt[1] = nn, root[1] = idx = 1;
	for(int i=2;i<=m+1;++i) {
		x = read(), y = read();
		int id = get(y), rt = root[id];
		root[i] = x, idx = i, from[i] = T.ask(dfn[rt],out[rt],y-cnt[id-1]);
		g.add(i,id,ori.dis[from[i]] - ori.dis[rt] + 1);
//		cout << from[i] << endl;
//		cout << i <<" " << id << " " << ori.dis[from[i]] - ori.dis[rt] + 1 << endl;
		nn += ori.size[x], cnt[i] = nn;
	}
	g.DFS(1);
	for(int i=1;i<=Q;++i) {
		x = read(), y = read();
		printf("%lld\n",Query(x,y));
	}
}

