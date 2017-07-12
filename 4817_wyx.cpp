
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 200000+5;
const int M = N << 2;
#define Max(a,b) ((a)>(b)?(a):(b))
 
__attribute__((optimize("-O2"))) char getc()
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
 
__attribute__((optimize("-O2"))) int read()
{
    static char ch;
    static int D;
    while(!isdigit(ch=getc())) if(ch == EOF) return -1;
    for(D=ch-'0'; isdigit(ch=getc());) D=(D<<3)+(D<<1)+(ch-'0');
    return D;
}
#define RG register
namespace io
{
    const int MaxBuff = 1 << 20;
    const int Output = 1 << 24;
    char B[MaxBuff], *S = B, *T = B;
    //#define getc() getchar()
    #define getc() ((S == T) && (T = (S = B) + fread(B, 1, MaxBuff, stdin), S == T) ? 0 : *S++)
    char Out[Output], *iter = Out;
    __attribute__((optimize("-O2")))  void flush()
    {
        fwrite(Out, 1, iter - Out, stdout);
        iter = Out;
    }
}
 
template<class Type>__attribute__((optimize("-O2")))  void print(RG Type x, RG char ch = '\n')
{
    using namespace io;
    if(!x) *iter++ = '0';
    else
    {
        if(x < 0) *iter++ = '-', x = -x;
        static int S2[100]; RG int t = 0;
        while(x) S2[++t] = x % 10, x /= 10;
        while(t) *iter++ = '0' + S2[t--];
    }
    *iter++ = ch;
}
 
int head[N], n;
 
struct graph {
    int next, to;
    graph () {}
    graph (int _next,int _to)
    :next(_next), to(_to) {}
}edge[M];
 
 void add(int x,int y) {
    static int cnt = 0;
    edge[++cnt] = graph(head[x],y); head[x] = cnt;
    edge[++cnt] = graph(head[y],x); head[y] = cnt;
}
 
 
int tr[M], lazy[M];
 
#define updata(k) (tr[k] = Max(tr[k<<1], tr[k<<1|1]) + lazy[k])
 
void change(int k,int l,int r,int x,int y,int val) {
    if(x <=l && r <= y) {
        tr[k] += val;
        lazy[k] += val;
        return ;
    }
    int mid = (l+r) >> 1;
    if(x <= mid) change(k<<1,l,mid,x,y,val);
    if(y > mid) change(k<<1|1,mid+1,r,x,y,val);
    updata(k);
}  
 
 int ask(int k,int l,int r,int x,int y) {
    if(l==x && r==y) return tr[k];
    int mid = (l+r) >> 1;
    if(y <= mid) return ask(k<<1,l,mid,x,y) + lazy[k];
    else if(x > mid) return ask(k<<1|1,mid+1,r,x,y) + lazy[k];
    else return max(ask(k<<1,l,mid,x,mid),ask(k<<1|1,mid+1,r,mid+1,y)) + lazy[k];
}
 
int F[N][18];
int in[N], out[N],depth[N];
 
 void DFS(int x) {
    static int cnt = 0;
    in[x] = ++cnt; 
    for(int i=head[x];i;i=edge[i].next) {
        if(edge[i].to != F[x][0]) {
            F[edge[i].to][0] = x;
            depth[edge[i].to] = depth[x] + 1;
            DFS(edge[i].to);
        }
    }
    out[x] = cnt;
    if(F[x][0]) change(1,1,n,in[x],out[x],1);
}
 
 int lca(int x,int y) {
    if(depth[x] < depth[y]) swap(x,y);
    int tt = depth[x] - depth[y];
    for(int i=17;~i;--i) if((1<<i)&tt) x = F[x][i];
    for(int i=17;~i;--i) if(F[x][i] != F[y][i]) x = F[x][i], y = F[y][i];
    return x == y ? x : F[x][0];
}
 
int fa[N], ch[N][2], lx[N];
bool root[N], rev[N];
void rotate(int x) {
    int y = fa[x], k = ch[y][1] == x;
    ch[y][k] = ch[x][!k], fa[ch[y][k]] = y;
    ch[x][!k] = y, fa[x] = fa[y], fa[y] = x;
    if(root[y]) swap(root[x],root[y]);
    else ch[fa[x]][ch[fa[x]][1] == y] = x;
    lx[y] = y; if(ch[y][0]) lx[y] = lx[ch[y][0]];
}
 
 
void splay(int x)
{
    if(!x) return;
    while(!root[x]) {
        int y = fa[x], z = fa[y];
        if(root[y]) rotate(x);
        else if((ch[z][1] == y) == (ch[y][1] == x)) rotate(y),rotate(x);
        else rotate(x),rotate(x);
    }
    lx[x] = x;
    if(ch[x][0]) lx[x] = lx[ch[x][0]];
}
 
 
 void access(int x) {
    int y = 0;
    while(x) {
        splay(x);
        root[ch[x][1]] = 1;
        root[y] = 0;
        if(ch[x][1]) {
            int y = lx[ch[x][1]];
            change(1,1,n,in[y],out[y],1);
        }
        ch[x][1] = y;
        if(ch[x][1]) {
            int y = lx[ch[x][1]];
            change(1,1,n,in[y],out[y],-1);
        }
        lx[x] = x; if(ch[x][0]) lx[x] = lx[ch[x][0]];
        y = x;
        x = fa[x];
    }
}
 
int main() {
//  freopen("tt.in", "r", stdin);
    n = read();
    for(int i=1;i<=n;++i) root[i] = 1, lx[i] = i;
    int m = read();
    for(int i=1;i<n;++i) {
        int x = read(), y = read();
        add(x,y);
    }
    DFS(1);
    for(int j=1;j<=17;++j) for(int i=1;i<=n;++i) F[i][j] = F[F[i][j-1]][j-1];
    for(int i=1;i<=n;++i) fa[i] = F[i][0];
    for(int i=1;i<=m;++i) {
    //  if(i%10000 == 0) printf("%d\n", i);
        int opt = read();
        if(opt == 1) {
            int x = read();
            access(x);
        }
        else if (opt == 2) {
            int x = read(), y = read();
            int tmp1 = ask(1,1,n,in[x],in[x]);
            int tmp2 = ask(1,1,n,in[y],in[y]);
            int ll = lca(x,y);
            int tmp3 = ask(1,1,n,in[ll],in[ll]) << 1;
            print(tmp1+tmp2-tmp3+1);
//          printf("%d\n", tmp1 + tmp2 - tmp3 + 1);
        }
        else {
            int x = read();
            print(ask(1,1,n,in[x],out[x])+1);
        }
    }
    io::flush();
}
