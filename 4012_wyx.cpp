
#include <vector>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
#define fir first
#define sec second
typedef long long LL;
const int N = 150000+5;
const int M = N << 1;
const int inf = 0x7fffffff;
#define mp(a,b) make_pair(a,b)

int head[N], last[N];
bool vis[N];

struct graph
{
	int next,to,val;
	graph () {}
	graph (int _next,int _to,int _val)
	:next(_next),to(_to),val(_val){}
}edge[M];

inline void add(int x,int y,int z){
	static int cnt = 0;
	edge[++cnt] = graph(head[x],y,z); head[x] = cnt;
	edge[++cnt] = graph(head[y],x,z); head[y] = cnt;
}

int size[N],f[N],sum,root;
int depth[N],fa[N][19];
int tmpdis[N];

void DFS(int x){
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to != fa[x][0]){
			depth[edge[i].to] = depth[x] + 1; tmpdis[edge[i].to] = tmpdis[x] + edge[i].val;
			fa[edge[i].to][0] = x; DFS(edge[i].to);
		}
}

inline int Lca(int x,int y) {
	if(depth[x] < depth[y]) swap(x,y);
	int tt = depth[x] - depth[y];
	for(int i=18;~i;--i) if((1<<i)&tt) x = fa[x][i];
	for(int i=18;~i;--i) if(fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
	return x == y ? x : fa[x][0];
}

int calc(int x,int y) {
	if(!y) return 0;
	return tmpdis[x] + tmpdis[y] - 2*tmpdis[Lca(x,y)];
}

void DFS1(int x,int fa) {
	size[x] = 1, f[x] = 0 ;
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to != fa && !vis[edge[i].to])
			DFS1(edge[i].to,x), size[x] += size[edge[i].to] , f[x] = max(f[x],size[edge[i].to]);
	f[x] = max(f[x],sum - size[x]);
	if(f[x] < f[root]) root = x;	
}

vector <pair<int,LL> > V[N],F[N];

char getc()
{
    static const int LEN = 1<<15;
    static char buf[LEN],*S=buf,*T=buf;
    if(S == T)
    {
        T = (S=buf)+fread(buf,1,LEN,stdin);
        if(S == T)return EOF;
    }
    return *S++;
}
  
int read()
{
    static char ch;
    static int D;
    while(!isdigit(ch=getc()));
    for(D=ch-'0'; isdigit(ch=getc());)
        D=(D<<3)+(D<<1)+(ch-'0');
    return D;
}

int dis[N],val[N];

void DFS2(int x,int fa,int bl){
	V[bl].push_back(mp(val[x],dis[x]));
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to != fa && !vis[edge[i].to]){
			dis[edge[i].to] = dis[x] + edge[i].val; DFS2(edge[i].to,x,bl);
		}
}

void DFS3(int x,int fa,int bl){
	F[bl].push_back(mp(val[x],dis[x]));
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to != fa && !vis[edge[i].to]){
			dis[edge[i].to] = dis[x] + edge[i].val; DFS3(edge[i].to,x,bl);
		}
}

void solve(int x){
	vis[x] = 1;  DFS1(x,0); dis[x] = 0;
	V[x].push_back(mp(val[x],0));
	for(int i=head[x];i;i=edge[i].next){
		if(!vis[edge[i].to]){
			dis[edge[i].to] = dis[x] + edge[i].val;
			DFS2(edge[i].to,x,x);
		}
	}
	for(int i=head[x];i;i=edge[i].next){
		if(!vis[edge[i].to]){
			dis[edge[i].to] = dis[x] + edge[i].val; root = 0; sum = size[edge[i].to];
			DFS1(edge[i].to,x);DFS3(edge[i].to,x,root); last[root] = x; solve(root);
		}
	}
}

LL ans = 0;
LL sz,lmt;
int now,lastL;

inline void ask(int x,int last){
	if(!x) return;
	{
		int l = 0, r = V[x].size();
		if(r != 0){
			while(l < r) {
				int mid = (l + r) >> 1;
				if(V[x][mid].fir <= lmt) l = mid + 1;
				else r =  mid;
			}
			l --;
			if(l >= 0) ans = ans + V[x][l].sec;
		}
		ans += (LL)(l - lastL)*calc(x,now);
	}
	{
		int l = 0, r = F[x].size();
		if(r != 0){
			while(l < r){
				int mid = (l+r) >> 1;
				if(F[x][mid].fir <= lmt) l = mid + 1;
				else r = mid;  
			}
			l --;
			if(l>=0) ans = ans - F[x][l].sec;
		}
		lastL = l;
	}
	ask(::last[x],x);
}

int main()
{
	int n = read(), Q = read(),x,y,z,A =  read();
	for(int i=1;i<=n;++i) val[i] = read();
	for(int i=1;i<n;++i) {
		x = read(), y = read(), z = read(); add(x,y,z);
	}
	root = 0; f[0] = inf;
	DFS(1); 
	for(int j=1;j<=18;++j) for(int i=1;i<=n;++i) fa[i][j] = fa[fa[i][j-1]][j-1];
	sum = n;
	DFS1(1,0); 
	solve(root);
	for(int i=1;i<=n;++i) sort(V[i].begin(),V[i].end());
	for(int i=1;i<=n;++i) sort(F[i].begin(),F[i].end());
	for(int i=1;i<=n;++i) {
		for(int j=1;j<V[i].size();++j) V[i][j].sec += V[i][j-1].sec;
		for(int j=1;j<F[i].size();++j) F[i][j].sec += F[i][j-1].sec;
	}	
	LL lastans = 0;
	for(int i=1;i<=Q;++i){
		int u = read();LL a = read(), b = read();
		(a += lastans) %= A, (b += lastans) %= A;
		int tt = a + b ; a = min(a,b); b = tt - a;
		lmt = a-1;
		now = u; lastL = 0;
		ask(u,0); LL tmp1 = ans; 
		lmt = b; lastL = 0;
		ans = 0;
		ask(u,0); LL tmp2 = ans;
		printf("%lld\n",lastans = tmp2 - tmp1);
		ans = 0;
	}
}
