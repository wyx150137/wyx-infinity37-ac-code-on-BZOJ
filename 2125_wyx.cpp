
#include <vector>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 30000+5;
#define pb push_back
using namespace std;
vector <int> V1[N], V2[N], val1[N], val2[N];

int fa[N], dis[N], depth[N], dfn[N], from[N], t[N], n, len[N], Fa[N][19], num, m;
bool vis[N];

inline void add1(int x,int y,int z) {V1[x].pb(y); val1[x].pb(z);}
inline void add2(int x,int y,int z) {V2[x].pb(y); val2[x].pb(z);}

inline void DFS1(int x) {
	static int cnt = 0; dfn[x] = ++cnt;
	for(int i=0;i<V1[x].size();++i) 
		if(V1[x][i] != fa[x]){
			if(!dfn[V1[x][i]]) {
				fa[V1[x][i]] = x;
				dis[V1[x][i]] = dis[x] + val1[x][i];
				DFS1(V1[x][i]);
			}
			else if(dis[V1[x][i]] < dis[x]) {
				vis[++n] = 1; num ++; from[n] = num;
				add2(V1[x][i],n,0); len[num] = dis[x] - dis[V1[x][i]] + val1[x][i];
				int tmp = x;
				while(tmp != V1[x][i]) {
					add2(n,tmp,min(dis[tmp]-dis[V1[x][i]],len[num]-(dis[tmp]-dis[V1[x][i]])));
					from[tmp] = num;  t[tmp] = dis[tmp] - dis[V1[x][i]];  tmp = fa[tmp];
				}
			}
	}
	if(!from[x]) 
		for(int i=0;i<V1[x].size();++i) 
			if(V1[x][i] == fa[x]) add2(fa[x],x,val1[x][i]);
}

inline void DFS2(int x) {
	for(int i=0;i<V2[x].size();++i) {
		Fa[V2[x][i]][0] = x;
		dis[V2[x][i]] = dis[x] + val2[x][i];
		depth[V2[x][i]] = depth[x] + 1;
		DFS2(V2[x][i]);
	}
}

inline int lca(int x,int y) {
	if(depth[x] < depth[y]) swap(x,y);
	int tt = depth[x] - depth[y];
	for(int i=18;~i;--i) if((1<<i)&tt) x = Fa[x][i];
	for(int i=18;~i;--i) if(Fa[x][i] != Fa[y][i]) x = Fa[x][i], y = Fa[y][i];
	return x == y ? x : Fa[x][0];
}

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

inline int up(int x,int F) {
	int tt = depth[x] - depth[F] - 1;
	for(int i=18;~i;--i) if((1<<i)&tt) x = Fa[x][i];
	return x;
}

int main() {//freopen("path15.in","r",stdin);
	n = read(), m = read();
	int q = read();
	for(int i=1;i<=m;++i) {
		int x = read(), y = read(), z = read();
		add1(x,y,z); add1(y,x,z);
	}
	DFS1(1);
	DFS2(1);
	for(int j=1;j<=18;++j) for(int i=1;i<=n;++i) Fa[i][j] = Fa[Fa[i][j-1]][j-1];
	while(q--) {
		int x = read(), y = read();
		int tt = lca(x,y);
		int ans = dis[x] + dis[y] - 2*dis[tt];
		if(vis[tt]) {
			int tmp1 = up(x,tt);
			int tmp2 = up(y,tt);
			ans -= min(t[tmp1],len[from[tmp1]]-t[tmp1]);
			ans -= min(t[tmp2],len[from[tmp2]]-t[tmp2]);
			ans += min(abs(t[tmp2]-t[tmp1]),len[from[tmp1]]-abs(t[tmp2]-t[tmp1]));
		}
		printf("%d\n", ans);
	}
}
