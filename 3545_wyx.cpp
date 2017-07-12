
#include <cstdio>
#include <algorithm>
using namespace std;
#define MAXN 500005
int n, m, q, h[MAXN], ans[MAXN], rt[MAXN], fa[MAXN], cnt;
inline void GET(int&n) {
    char c; n = 0; do c = getchar(); while('0' > c || c > '9');
    while('0' <= c && c <= '9')n = n*10 + c-'0', c = getchar();
}
struct Edge {
    int u, v, w;
    inline void scan() { GET(u); GET(v); GET(w); }
    inline bool operator < (const Edge&r) const { return w < r.w; }
} e[MAXN];
struct Query {
    int v, x, k, id;
    inline void scan(int i) { GET(v); GET(x); GET(k); id = i; }
    inline bool operator < (const Query&r)const { return x < r.x; }
} p[MAXN];
int findroot(int x) { return x == fa[x] ? x : (fa[x] = findroot(fa[x])); }
struct Seg { int l, r, c; } t[100005*32];
#define MID ((l + r) >> 1)
void ins(int&x, int p, int l = 1, int r = 1e9) {
    if(!x) x = ++ cnt; ++ t[x].c;
    if(l == r) return;
    if(p <= MID) ins(t[x].l, p, l, MID);
    else ins(t[x].r, p, MID+1, r);
}
int mer(int x, int y, int l = 1, int r = 1e9) {
    if(!x || !y) return x + y;
    if(l == r) { t[x].c = t[x].c + t[y].c; return x; }
    t[x].l = mer(t[x].l, t[y].l, l, MID);
    t[x].r = mer(t[x].r, t[y].r,MID+1,r);
    t[x].c = t[t[x].l].c + t[t[x].r].c;
    return x;
}
int getkth(int x, int k, int l = 1, int r = 1e9) {
    if(l == r) return l;
    if(t[t[x].r].c >= k) return getkth(t[x].r, k, MID+1, r);
    return getkth(t[x].l, k-t[t[x].r].c, l, MID);
}
void Merge(int u, int v) {
    u = findroot(u); v = findroot(v);
    if(u == v) return;
    rt[u] = mer(rt[u], rt[v]);
    fa[v] = u;
}
int main() {
    GET(n); GET(m); GET(q);
    for(int i = 1; i <= n; ++ i) GET(h[i]);
    for(int i = 1; i <= n; ++ i) fa[i] = i;
    for(int i = 1; i <= n; ++ i) ins(rt[i], h[i]);
    for(int i = 1; i <= m; ++ i) e[i].scan();
    sort(e + 1, e + m + 1);
    for(int i = 1; i <= q; ++ i) p[i].scan(i);
    sort(p + 1, p + q + 1);
    for(int i = 1, j = 1; i <= q; ++ i) {
        while(j <= m && e[j].w <= p[i].x) Merge(e[j].u, e[j].v), j ++;
        int r = rt[findroot(p[i].v)];
        ans[p[i].id] = t[r].c >= p[i].k ? getkth(r, p[i].k) : -1;
    }
    for(int i = 1; i <= q; ++ i) printf("%d\n", ans[i]);
    return 0;
}
