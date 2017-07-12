
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e6+5;
typedef long long LL;
const int mod = 1e9+7;

inline int read() {
    int x=0,f=1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
    while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
    return x*f;
}

int T, v[N];
int depth[N], dfn[N], dis[N];
LL ans;

struct Graph {
    int head[N], cnt, fa[N][22], size[N];

    struct graph {
        int next,to;
        graph () {}
        graph (int _next,int _to)
        :next(_next),to(_to){}
    }edge[N<<1];

    inline void add(int x,int y, bool flag = false) {
        if(x==y) return;
    //  if(flag) cout << x <<  "  " << y << endl;
        edge[++cnt] = graph(head[x],y); head[x] = cnt;
        edge[++cnt] = graph(head[y],x); head[y] = cnt;
    }

    void DFS(int x,int fa) {
        if(v[x] == T) size[x] = 1; else size[x] = 0;
        for(int i=head[x];i;i=edge[i].next) if(edge[i].to != fa) DFS(edge[i].to,x); int last = size[x];
        for(int i=head[x];i;i=edge[i].next) if(edge[i].to != fa) (ans += (LL) last * size[edge[i].to] % mod * dis[x] % mod) %= mod , last += size[edge[i].to];
        size[x] = last; head[x] = 0;
    }

    void DFS1(int x) {
        static int cnt = 0;
        dfn[x] = ++cnt;
        for(int i=head[x];i;i=edge[i].next) if(edge[i].to != fa[x][0])  {
            fa[edge[i].to][0] = x;
            depth[edge[i].to] = depth[x] + 1;
            DFS1(edge[i].to);
        }
    }

    inline int lca(int x,int y) {
        if(depth[x] < depth[y]) swap(x,y);
        int tt = depth[x] - depth[y];
        for(int i=21;~i;--i) if((1<<i)&tt) x = fa[x][i];
        for(int i=21;~i;--i) if(fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
        return x == y ? x : fa[x][0];
    }

}tr,vt;

bool cmp(const int &a,const int &b) { return dfn[a] < dfn[b]; }
int Uni(int *a,int cnt) { int top = 0; for(int i=1;i<=cnt;++i) if(a[i] != a[i-1]) a[++top] = a[i]; return top; }  

char str[N];
int fa[N<<1];
int son[N][26], sz, last, root, tmp[N];

void insert(int x,int *depth = ::dis) {
    int np = ++sz,  p = last;
    last = np; depth[np] = depth[p] + 1;
    while(p && !son[p][x])  son[p][x] = np, p = fa[p];
    if(!p) fa[np] = root;
    else  {
        int q = son[p][x];
        if(depth[q] == depth[p] + 1) fa[np] = q;
        else  {
            int nq = ++sz;
            depth[nq] = depth[p] + 1;
            memcpy(son[nq],son[q],sizeof son[q]);
            fa[nq] = fa[q];
            fa[q] = nq; fa[np] = nq;
            while(p && son[p][x] == q) {
                son[p][x] = nq;
                p = fa[p];
            }
        }
    }
}

int pos[N], stack[N], top;

int main() {// freopen("C.in","r",stdin); freopen("C.out","w",stdout);
    register int i ; int n = read(), m = read();
    scanf("%s",str+1); root = ++sz; last = root;
    for(i=n;i;--i) insert(str[i]-'a'), pos[i] = last;
    for(i=2;i<=sz;++i) tr.add(fa[i],i); tr.DFS1(1); 
    for(int j=1;j<=21;++j) for(int i=1;i<=sz;++i) tr.fa[i][j] = tr.fa[tr.fa[i][j-1]][j-1];
    while(m--) {
        n = read(); T++; vt.cnt = 0;
        for(i=1;i<=n;++i) v[tmp[i] = pos[read()]] = T;
        sort(tmp+1,tmp+n+1,cmp);
        stack[top = 1] = 1;
        for(i=1;i<=n;++i) {
            int L = tr.lca(tmp[i],stack[top]);
        //  cout << tmp[i] << " " << stack[top] << " " << L << endl;
            while(depth[stack[top]] > depth[L])  {
                if(depth[stack[top-1]] >= depth[L]) vt.add(stack[top],stack[top--], 1);
                else vt.add(L,stack[top--]);
            } 
            if(L != stack[top]) stack[++top] = L;
            stack[++top] = tmp[i];
        }
        while(top) vt.add(stack[top],stack[top--]);
        ans = 0;
        vt.DFS(1,-1);
        printf("%lld\n",ans);
    }
}

