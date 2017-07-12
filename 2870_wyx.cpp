
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
const int M = N << 1;

bool vis[N];
int depth[N];

inline int read() {
    int x=0,f=1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
    while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
    return x*f;
}

int n;
int fa[N][20], F[N];

inline int find(int x) {
    return F[x] ^ x ? F[x] = find(F[x]) : F[x];
}

inline void Union(int x,int y) {
    int fx = find(x), fy = find(y);
    if(fx == fy) return;
    if(rand()&1) F[fx] = fy;
    else F[fy] = fx;
}

int head[N];

struct graph {
    int next,to;
    graph () {}
    graph (int _next,int _to)
    :next(_next),to(_to){}
}edge[M];

inline void add(int x,int y) {
    static int cnt = 0;
    edge[++cnt] = graph(head[x],y); head[x] = cnt;
    edge[++cnt] = graph(head[y],x); head[y] = cnt;
}

int q[N];

void BFS() {
    int l = 1, r = 0;
    q[++r] = 1;
    register int i;
    while(l <= r) {
        int tt = q[l++];
        for(i=head[tt];i;i=edge[i].next) 
            if(edge[i].to != fa[tt][0])
                depth[q[++r] = edge[i].to] = depth[tt] + 1, fa[edge[i].to][0] = tt;
    }
    for(int j=1;j<20;++j) for(i=1;i<=n;++i) fa[i][j] = fa[fa[i][j-1]][j-1];
}

inline int lca(int x,int y) {
    if(depth[x] < depth[y]) swap(x,y);
    int tt = depth[x] - depth[y];
    for(int i=19;~i;--i) if((1<<i)&tt) x = fa[x][i];
    for(int i=19;~i;--i) if(fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
    return x == y ? x : fa[x][0];
}

inline int calc(int x,int y) {
    return depth[x] + depth[y] - (depth[lca(x,y)]<<1) + 1;
}

int bst[N][2];

inline void solve(int x){
    int i,j,nx=x,ny=x,tx,ty,d,f=0,fx,fy;
    for(i=head[x];i;i=edge[i].next)
        if(vis[j=edge[i].to]){
            j=find(j);tx=bst[j][0],ty=bst[j][1];F[find(x)]=j;f=0;
            d=calc(nx,tx);f<d?f=d,fx=nx,fy=tx:1;
            d=calc(nx,ty);f<d?f=d,fx=nx,fy=ty:1;
            d=calc(ny,tx);f<d?f=d,fx=ny,fy=tx:1;
            d=calc(ny,ty);f<d?f=d,fx=ny,fy=ty:1;
            d=calc(nx,ny);f<d?f=d,fx=nx,fy=ny:1;
            d=calc(tx,ty);f<d?f=d,fx=tx,fy=ty:1;
            nx=fx,ny=fy;
    }
    x=find(x);
    bst[x][0] = nx, bst[x][1] = ny;
}

struct Lux {
    int x,val;
    bool operator < (const Lux &z)const {
        return val > z.val;
    }
}a[N];

int main() {
    n = read();
    for(int i=1;i<=n;++i) a[i].val = read(), a[i].x = i;
    for(int i=1;i<n;++i) add(read(),read());
    for(int i=1;i<=n;++i) F[i] = i;
    sort(a+1,a+n+1); BFS();
    int ans = 0;
    for(int i=1;i<=n;++i) {
        int tt = a[i].x;
        bst[tt][0] = bst[tt][1] = tt; vis[tt] = 1;
        solve(tt); tt = find(tt);
        ans = max(ans,a[i].val*calc(bst[tt][0],bst[tt][1]));
 //       cout << bst[tt][0] << " " << bst[tt][1] << endl;
    }
    cout << ans << endl;
}
