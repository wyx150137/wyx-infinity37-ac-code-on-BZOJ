
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
const LL inf = 2e18;
const int N = 600000 +5;
const int M = N << 1;
inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9') {if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9') {x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int son[N][26],depth[N], fa[N];
LL mn[N], mx[N];
int p, np, q, nq, cnt, last, size[N], root;
bool in[N];
int mp[N], a[N];

inline int newnode(int _depth){
	depth[++cnt] = _depth;
	return cnt;
}

inline void insert(int x,int node) {
	p = last, np = newnode(depth[p]+1);
	last = np; in[np] = 1; mp[np] = node;
	while(p && !son[p][x]) {
		son[p][x] = np;
		p = fa[p];
	}
	if(!p) fa[np] = root;
	else {
		q = son[p][x];
		if(depth[q] == depth[p]+1) fa[np] = q;
		else {
			int nq = newnode(depth[p]+1);
			memcpy(son[nq],son[q],sizeof son[q]);
			fa[nq] = fa[q]; fa[q] = fa[np] = nq;
			while(p && son[p][x] == q) {
				son[p][x] = nq;
				p = fa[p];
			}
		}
	}
}

int head[N];
LL ans[N], ans1[N];

struct graph {
	int next, to;
	graph () {}
	graph (int _next,int _to)
	:next(_next), to(_to) {}
}edge[M];

inline void add(int x,int y) {
	static int cnt = 0;
	edge[++cnt] = graph(head[x],y); head[x] = cnt;
	edge[++cnt] = graph(head[y],x); head[y] = cnt;
}

inline void DFS(int x,int fa) {
	if(in[x]) {
		mx[x] = mn[x] = a[mp[x]];
		size[x] = 1;
	}
	else mx[x] = mn[x] = inf;
	for(int i=head[x];i;i=edge[i].next) {
		if(edge[i].to != fa) {
			DFS(edge[i].to,x);
			ans[depth[x]] += (LL) size[x] * size[edge[i].to];
			if(mx[x] == inf) {
				mx[x] = mx[edge[i].to];
				mn[x] = mn[edge[i].to];
			}
			else {
				ans1[depth[x]] = max(ans1[depth[x]], mx[x]*mx[edge[i].to]);
				ans1[depth[x]] = max(ans1[depth[x]], mn[x]*mn[edge[i].to]);
				mx[x] = max(mx[x], mx[edge[i].to]);
				mn[x] = min(mn[x], mn[edge[i].to]);
			}
			size[x] += size[edge[i].to];
 		}
	}
}

char str[N];

int main() {
//	freopen("tt.in","r",stdin);
	int n = read();
	scanf("%s",str+1);
	last = root = newnode(0);
	reverse(str+1,str+n+1);
	for(int i=1;i<=n;++i) insert(str[i]-'a', i);
	for(int i=2;i<=cnt;++i) add(fa[i],i);
	for(int i=1;i<=n;++i) a[n-i+1] = read();
	for(int i=0;i<=n;++i) ans1[i] = -inf;
	DFS(1, -1);
	for(int i=n;i>=0;--i) ans[i] += ans[i+1];
	for(int i=n-1;i>=0;--i) ans1[i] = max(ans1[i], ans1[i+1]);
	for(int i=0;i<n;++i) 
		printf("%lld %lld\n", ans[i], ans1[i] == -inf ? 0 : ans1[i]);
}
