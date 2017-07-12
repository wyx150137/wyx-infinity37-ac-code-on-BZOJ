
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 1e6+5;
const int M = N;

char str[N];
int head[N], q[N];

struct graph {
	int next,to;
	graph () {}
	graph (int _next,int _to)
	:next(_next),to(_to){}
}edge[M];

inline void add(int x,int y) { 
	static int cnt = 0; edge[++cnt] = graph(head[x],y); head[x] = cnt;
}

LL size[N];
bool vis[N];

int cnt, n, t, k, sz, last, depth[N], fa[N], son[N][26], root;

inline int newnode(int _) {
	depth[++sz] = _;return sz;
}

void insert(int x) {
    int np = ++sz,  p = last; last = np; 
    depth[np] = depth[p] + 1; size[np] = 1;
    while(p && !son[p][x])  son[p][x] = np, p = fa[p];
    if(!p) fa[np] = root;
    else  {
        int q = son[p][x];
        if(depth[q] == depth[p] + 1) fa[np] = q;
        else  {
            int nq = ++sz;
            depth[nq] = depth[p] + 1;
            memcpy(son[nq],son[q],sizeof son[q]);
            size[nq] = t ? 0 : 1;
            fa[nq] = fa[q];fa[q] = nq; fa[np] = nq;
            while(p && son[p][x] == q) {
                son[p][x] = nq;
                p = fa[p];
            }
        }
    }
}

void BFS() {
	int l = 0, r = 1; q[++r] = root;
	while(l <= r) {
		int tt = q[l++];
		for(int i=head[tt];i;i=edge[i].next) q[++r] = edge[i].to;
	}
	for(int i=r;i;--i) if(fa[q[i]] && fa[q[i]] != root)  size[fa[q[i]]] += size[q[i]];
}

void DFS(int x) {
	if(vis[x]) return;
	vis[x] = 1;
	for(int i=0;i<26;++i) 
		if(son[x][i]) {
			DFS(son[x][i]);
			size[x] += size[son[x][i]];
		}
}

void solve(int x,int k) {
	LL sum = 0;
	for(int i=0;i<26;++i) if(son[x][i]) sum += size[son[x][i]];
	if(size[x] - sum >= k) return;
	k -= size[x] - sum; sum = 0;
	for(int i=0;i<26;++i) {
		if(son[x][i]) {
			if(sum < k && k <= sum + size[son[x][i]]) {
				putchar('a'+i);
				solve(son[x][i],k-sum);
				break;
			}
			else sum += size[son[x][i]];
		}
	}
}

int main() {
//	freopen("string.in","r",stdin);freopen("string.out","w",stdout);
	scanf("%s",str);
	cin >> t >> k; last = root = sz = 1;
	for(int i=0;str[i];++i) insert(str[i]-'a');
	if(t) {
		for(int i=2;i<=sz;++i) add(fa[i],i);
		BFS();
	}
	DFS(root);
	if(size[root] < k) puts("-1");
	else solve(root,k);
	puts("");
}
