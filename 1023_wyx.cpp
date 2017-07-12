
#include <vector>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define fir first
#define sec second
#define mp make_pair
#define pb push_back
const int N = 2000000+5;
const int inf = 0x3f3f3f3f;
using namespace std;

vector <int> V1[N], V2[N], val[N];

inline void add(int x,int y) {V1[x].pb(y);}
inline void add2(int x,int y,int z) {V2[x].pb(y), val[x].pb(z);} 

int dfn[N], dis[N], fa[N], n, m, num, from[N], len[N];
bool vis[N];

inline void DFS1(int x) { static int cnt = 0;
	dfn[x] = ++cnt; 
	for(int i=0;i<V1[x].size();++i) {
		if(V1[x][i] != fa[x]) {
			if(!dfn[V1[x][i]]) {
				dis[V1[x][i]] = dis[x] + 1;
				fa[V1[x][i]] = x;
				DFS1(V1[x][i]);
			}
			else if(dis[V1[x][i]] < dis[x]) {
				vis[++n] = 1; ++ num;  from[n] = num; add2(V1[x][i],n,0); 
				len[num] = dis[x] - dis[V1[x][i]] + 1; int tmp = x;
				while(tmp != V1[x][i]) {
					add2(n,tmp,min(dis[tmp]-dis[V1[x][i]],len[num]-(dis[tmp]-dis[V1[x][i]])));
					from[tmp] = num; tmp = fa[tmp];
				}
			}
		}
	}
	if(!from[x]) add2(fa[x],x,1);
}

pair <int,int> F[N];

int ans;

inline void get(pair<int,int> &p,int tt) {
	if(tt > p.fir) {
		p.sec = p.fir;
		p.fir = tt;
	}
	else if(tt > p.sec) p.sec = tt;
}

int q[N], disq[N];

inline void DFS2(int x) {
	for(int i=0;i<V2[x].size();++i)  {
		DFS2(V2[x][i]);
		get(F[x],F[V2[x][i]].fir+val[x][i]);
	}
	if(!vis[x]) ans = max(ans,F[x].fir+F[x].sec);
	else {
		int l = 1, r = 0,anc = from[x], mx = -inf;
		for(int i=V2[x].size()-1;~i;--i) {
			while(l<=r && dis[V2[x][i]] - dis[q[l]] > len[anc]/2) {mx = max(mx,F[q[l]].fir+dis[q[l]]+len[anc]); l ++;}
			ans = max(ans,mx+F[V2[x][i]].fir-dis[V2[x][i]]);
			if(l<=r) ans = max(ans,disq[l]+dis[V2[x][i]]+F[V2[x][i]].fir);
			while(l<=r && disq[r] < F[V2[x][i]].fir-dis[V2[x][i]]) r--;
			q[++r] = V2[x][i]; disq[r] = F[V2[x][i]].fir-dis[V2[x][i]];
		}
	}
}

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int main (){
    n = read(), m = read();
    int u,v,k;  
    for (int i=1;i<=m;i++)  
    {  
        k = read(), u = read();
        for (int i=1;i<k;i++)  
        {  
            v = read();
            add(u,v);add(v,u);u=v;  
        }  
    }  
	dis[1] = 1;
	DFS1(1);
	DFS2(1);
	cout << ans << endl;
}
