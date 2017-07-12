
#include <vector>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define pb push_back
#define mp make_pair
#define fir first
#define sec second
const int N = 600010;
using namespace std;
typedef long long LL;
const LL inf = 1e15;

vector <int> V1[N], V2[N], V3[N];
vector <LL>  val1[N],val2[N], val3[N];

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

inline void add1(int x,int y,LL z) {V1[x].pb(y); val1[x].pb(z);V1[y].pb(x);val1[y].pb(z);}
inline void add2(int x,int y,LL z) {V2[x].pb(y); val2[x].pb(z);}
inline void add3(int x,int y,LL z) {V3[x].pb(y); val3[x].pb(z);V3[y].pb(x);val3[y].pb(z);
/*cout << x << " " << y << " " << z << endl;*/}

LL dis[N], len[N], t[N]; 
bool vis[N];
int depth[N], fa[N], Fa[N][21], dfn[N], num, from[N], n, m;

void DFS1(int x) {
	static int cnt = 0; dfn[x] = ++cnt;
	LL l[3] = {0,inf,inf};
	if(fa[x]) {
		for(int i=0;i<V1[x].size();++i) if(V1[x][i] == fa[x]) l[++l[0]] = val1[x][i];
		dis[x] = dis[fa[x]] + min(l[1],l[2]);
	}
	for(int i=0;i<V1[x].size();++i) 
		if(V1[x][i] != fa[x]) {
			if(!dfn[V1[x][i]]){
				fa[V1[x][i]] = x;
		//		dis[V1[x][i]] = dis[x] + val1[x][i];
				DFS1(V1[x][i]);
			}
			else if(dis[V1[x][i]] < dis[x]) {
				vis[++n] = 1; from[n] = ++num; add2(V1[x][i],n,0);
				len[num] = dis[x] - dis[V1[x][i]] + val1[x][i]; int tmp = x;
				while(tmp != V1[x][i]) {
					from[tmp] = num; t[tmp] = dis[tmp] - dis[V1[x][i]];
					add2(n,tmp,min(t[tmp],len[num]-t[tmp])); tmp = fa[tmp];					
				}
			}
		}
	if(!from[x] && fa[x]) add2(fa[x],x,min(l[1],l[2]));
}

inline void DFS2(int x) {
	static int cnt = 0; dfn[x] = ++cnt;
	for(int i=0;i<V2[x].size();++i) {
		if(V2[x][i] != Fa[x][0]) { 
			Fa[V2[x][i]][0] = x;
			depth[V2[x][i]] = depth[x] + 1;
			dis[V2[x][i]] = dis[x] + val2[x][i];
			DFS2(V2[x][i]);
		}
	}
}

inline int lca(int x,int y) {
	if(depth[x] < depth[y]) swap(x,y);
	int tt = depth[x] - depth[y];
	for(int i=20;~i;--i) if((1<<i)&tt) x= Fa[x][i];
	for(int i=20;~i;--i) if(Fa[x][i] != Fa[y][i]) x = Fa[x][i], y = Fa[y][i];
	return x == y ? x : Fa[x][0];
}

inline int up(int x,int y) {
	int tt = depth[x] - depth[y] - 1;
	for(int i=20;~i;--i) if((1<<i)&tt) x = Fa[x][i];
	return x;
}

int times; 

int q[N]; LL disq[N], g[N], tmpcnt; 
int T[N];
LL ans;

bool cmp2(int x,int y){
	return t[x] < t[y];
}

inline LL calc(int x,int y) {
	if(t[x] <= t[y]) return t[y] - t[x];
	else return len[from[x]] - (t[x] - t[y]);
}

LL F[N];
inline void DFS3(int x,int fa){
	F[x] = 0;
	for(int i=0;i<V3[x].size();++i) {
		if(V3[x][i] != fa) {
			DFS3(V3[x][i],x);
			if(!vis[x] && (F[x] || T[x] == times)) ans = max(ans,F[x]+F[V3[x][i]]+val3[x][i]);
			F[x] = max(F[x],F[V3[x][i]] + val3[x][i]);
		}
	}
	if(vis[x]==1) {
		int tmpcnt = 0;
		for(int i=0;i<V3[x].size();++i) if(V3[x][i] != fa)  g[++tmpcnt] = V3[x][i];
		sort(g+1,g+tmpcnt+1,cmp2);for(int i=1;i<=tmpcnt;++i) g[i+tmpcnt] = g[i];
		if(tmpcnt == 1) return;
		int l = 1, r = 0;
		for(int i=1,now=1;i<=tmpcnt;++i) {
			while(1) {
				LL t = calc(g[i],g[now]);
				if(now >= i + tmpcnt || t > len[from[x]] - t) break;
				while(l<=r && F[g[q[r]]] + calc(g[i],g[q[r]]) <= F[g[now]] + t) r --;
				q[++r] = now ++;
			}
			while(l<=r && q[l] <= i) l++;
			if(l<=r) ans = max(ans,F[g[i]]+F[g[q[l]]]+calc(g[i],g[q[l]]));
		}
	}
}

bool cmp(int a,int b){return dfn[a] < dfn[b];} 

int stack[N], top, a[N];
vector <int> clr;

int main() {//freopen("C.in","r",stdin);freopen("C.out","w",stdout);
	n = read(), m = read();
	for(int i=1;i<=m;++i) {
		int x = read(), y = read(),z = read();
		add1(x,y,z);
	}
	DFS1(1);
	depth[1] = 1;
	DFS2(1);
	for(int j=1;j<=20;++j) for(int i=1;i<=n;++i) Fa[i][j] = Fa[Fa[i][j-1]][j-1];
	int q = read();
	while(q--) {
		int k = read(); times ++;
		for(int i=1;i<=k;i++) a[i] = read(), T[a[i]] = times; a[++k] = 1;
		sort(a+1,a+k+1,cmp); k = unique(a+1,a+k+1)-a-1;
		stack[top=1] = 1;
		for(int i=2;i<=k;++i) {
			while(1) {
				int tt = lca(stack[top],a[i]);
				if(tt == stack[top]) {
					if(vis[stack[top]]) {
						stack[top+1] = up(a[i],stack[top]);
						top++;
					}
					break;
				}
				if(depth[tt] > depth[stack[top-1]]) {
					if(!vis[tt]) {
						clr.pb(tt);clr.pb(stack[top]);
						add3(tt,stack[top],dis[stack[top]]-dis[tt]); stack[top] = tt;
					}
					else {
						int tmp1 = up(stack[top],tt);
						if(tmp1 != stack[top]) {
							clr.pb(tmp1);clr.pb(stack[top]);
							add3(tmp1,stack[top],dis[stack[top]]-dis[tmp1]);
							clr.pb(tt); clr.pb(tmp1);
							add3(tt,tmp1,dis[tmp1]-dis[tt]);
						}
						else {
							clr.pb(tmp1);clr.pb(tt); 
							add3(tmp1,tt,dis[tmp1]-dis[tt]);
						}
						top --;
						if(Fa[tt][0] != stack[top]) stack[++top] = Fa[tt][0];
						stack[++top] = tt;
					}
				}
				else {
					clr.pb(stack[top]);clr.pb(stack[top-1]);
					add3(stack[top],stack[top-1],dis[stack[top]]-dis[stack[top-1]]); top--;
				}
			}
			if(stack[top] != a[i]) stack[++top] = a[i];
		}
		for(int i=top;i>1;--i) {
			clr.pb(stack[i-1]); clr.pb(stack[i]);
			add3(stack[i-1],stack[i],dis[stack[i]]-dis[stack[i-1]]);
		}
		ans = 0;
		DFS3(1,-1);
		printf("%lld\n", ans);
		for(int i=0;i<clr.size();++i) {
			V3[clr[i]].clear(); val3[clr[i]].clear();
		}
		clr.clear();
	}
}
