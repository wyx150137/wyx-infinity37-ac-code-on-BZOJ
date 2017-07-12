
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 80010+5;
const int M = N << 2;
#define lowbit(x) ((x)&(-x))
using namespace std;

int head[N],sum[N],ans[N];

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
  

struct graph{
	int next,to;
	graph () {}
	graph (int _next,int _to)
	:next(_next),to(_to){}
}edge[M];

inline void add(int x,int y){
	static int cnt = 0;
	edge[++cnt] = graph(head[x],y); head[x] = cnt;
	edge[++cnt] = graph(head[y],x); head[y] = cnt;
}

int fa[N][18],dfn;
int depth[N],in[N],out[N];

void DFS(int x){
	in[x] = ++dfn;
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to != fa[x][0]){
			fa[edge[i].to][0] = x;
			depth[edge[i].to] = depth[x] + 1;
			DFS(edge[i].to);
		}
	out[x] = dfn;
}

inline int lca(int x,int y){
	if(depth[x] < depth[y]) swap(x,y);
	int tt = depth[x] - depth[y];
	for(int i=17;~i;--i) if((1<<i)&tt) x = fa[x][i];
	for(int i=17;~i;--i) if(fa[x][i] != fa[y][i]) x = fa[x][i], y =fa[y][i];
	return x == y ? x : fa[x][0];
}

inline int up(int x,int y){
	for(int i=17;~i;--i) if(depth[fa[x][i]] > depth[y]) x = fa[x][i];
	return x;
}

struct Plate{
	int x1,x2,y1,y2;
	int val;
	int times;
	bool operator < (const Plate &z)const{
		return val < z.val;
	}
}plate[N];

int cnt;

struct fruit{
	int x,y1,y2;
	int val,id;
	bool operator < (const fruit &z)const{
		return x ^ z.x ? x < z.x : id < z.id;
	}
}ev[N];

struct points{
	int x,y,k,id;
}a[N],tmp1[N],tmp2[N];

int tr[N],n,m,q;

void updata(int x,int val){
	while(x < N){
		tr[x] += val;
		x += lowbit(x);
	}
}

int ask(int x){
	int ans = 0;
	while(x){
		ans += tr[x];
		x -= lowbit(x);
	}
	return ans;
}
void solve(int l,int r,int L,int R){
	if(L > R) return ;
	if(l == r){
		for(int i=L;i<=R;++i)
			ans[a[i].id] = plate[l].val;
		return ;
	}
	int mid = (l+r) >> 1, sz = 0;
	for(int i=l;i<=mid;++i){
		ev[++sz] = (fruit) {plate[i].x1,plate[i].y1,plate[i].y2,1,0};
		ev[++sz] = (fruit) {plate[i].x2,plate[i].y1,plate[i].y2,-1,n+1};
	}
	for(int i=L;i<=R;++i) ev[++sz] = (fruit) {a[i].x,a[i].y,0,0,i};
	sort(ev+1,ev+sz+1);
	for(int i=1;i<=sz;++i){
		if(ev[i].id <= R && ev[i].id >= L) sum[ev[i].id] = ask(ev[i].y1);
		else updata(ev[i].y1,ev[i].val),updata(ev[i].y2+1,-ev[i].val);
	}
	int l1 = 0, l2 = 0;
	for(int i=L;i<=R;++i)
		if(sum[i] >= a[i].k) tmp1[++l1] = a[i];
		else  tmp2[++l2] = (points){a[i].x,a[i].y,a[i].k-sum[i],a[i].id};
	for(int i=L;i<=L+l1-1;++i) a[i] = tmp1[i-L+1];
	for(int i=L+l1;i<=R;++i) a[i] = tmp2[i-L-l1+1];
	solve(l,mid,L,L+l1-1); solve(mid+1,r,L+l1,R);
}

int main(){
	n = read(), m = read(), q = read();
	for(int i=1;i<n;++i) add(read(),read());
	DFS(1); for(int j=1;j<=17;++j) for(int i=1;i<=n;++i) fa[i][j] = fa[fa[i][j-1]][j-1];
	for(int i=1;i<=m;++i){
		int x = read(), y = read(), L = lca(x,y); int c = read();
		if(in[x] > in[y]) swap(x,y);
		if(L !=  x) plate[++cnt] = (Plate){in[x],out[x],in[y],out[y],c};
		else{
			int tt = up(y,L); //cout << tt << endl;
			plate[++cnt] = (Plate) {1,in[tt]-1,in[y],out[y],c};
			if(out[tt] < n) plate[++cnt] = (Plate) {in[y],out[y],out[tt]+1,n,c};
		}
	}
	sort(plate+1,plate+cnt+1);
	for(int i=1;i<=q;++i){
		int a = read(), b = read(), k = read();
		if(in[a] > in[b]) swap(a,b);
		::a[i] = (points){in[a],in[b],k,i};
	}
	solve(1,cnt,1,q);
	for(int i=1;i<=q;++i)
		printf("%d\n",ans[i]);
}
