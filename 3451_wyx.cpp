
#include <cmath>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
typedef double f2;
const int inf = 0x3f3f3f3f;
const f2 PI = acos(-1);
const int N = 30000+5;
const int M = N << 1;

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9') {if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9') {x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f; 
}

struct cp{
	double a,b;
	cp (double _=0,double __=0) :a(_), b(__){}
	cp operator + (const cp &z)const {return cp(a+z.a,b+z.b);}
	cp operator - (const cp &z)const {return cp(a-z.a,b-z.b);}
	cp operator * (const cp &z)const {return cp(a*z.a-b*z.b,a*z.b+b*z.a);}
}a[N],b[N],A[N],x,y,c[N];

int rev[N], dig[50];

void FFT(cp *a,int n,int type) {
	register int i,j,k;
	for(i=0;i<n;++i) A[i] = a[rev[i]];
	for(i=0;i<n;++i) a[i] = A[i];
	for(i=2;i<=n;i<<=1) {
		cp wn (cos(2*PI/i),type*sin(2*PI/i));
		for(j=0;j<n;j+=i) {
			cp w(1,0);
			for(k=j;k<j+i/2;++k,w=w*wn) {
				x = a[k] , y = a[k+i/2]*w;
				a[k] = x + y, a[k+i/2] = x - y;
			}
		}
	}
	if(type == -1) for(i=0;i<n;++i) a[i].a /= n;	
}

int head[N];

struct graph {
	int next, to;
	graph () {}
	graph (int _next,int _to)
	:next(_next), to(_to) {}
}edge[M];

inline void add(int x,int y) {
	static int cnt = 0;
	edge[++cnt] = graph(head[x], y); head[x] = cnt;
	edge[++cnt] = graph(head[y], x); head[y] = cnt;
}

bool vis[N];
int size[N], F[N], root, sz;

inline void DFS1(int x, int fa) {
	size[x] = 1, F[x] = 0;
	for(int i=head[x];i;i=edge[i].next) {
		if(!vis[edge[i].to] && edge[i].to != fa) {
			DFS1(edge[i].to, x);
			size[x] += size[edge[i].to];
			F[x] = max(F[x], size[edge[i].to]);
		}
	}
	F[x] = max(F[x], sz - size[x]);
	if(F[x] < F[root]) root = x;
}

int T[N], tim[N], cls, Max;
int ans[N];

inline void DFS2(int x,int fa,int depth) {
	if(tim[depth] != cls) T[depth] = 0; 
	tim[depth] = cls; T[depth] ++; Max = max(Max,depth);
	for(int i=head[x];i;i=edge[i].next) if(edge[i].to != fa && !vis[edge[i].to]) DFS2(edge[i].to,x,depth+1);
}

inline void calc(int type) {
	for(int i=0;i<=Max;++i) {
		if(tim[i] != cls) a[i] = 0;
		else a[i].a = T[i];
	}
	int len = 0, j, L;
	for(L=1;L<=Max<<1;len++,L<<=1);
	for(int i=1,l=0;i<L;++i,l=0) {
		rev[i] = 0;
		for(j=i;j;j>>=1)  dig[l++] = j&1;
		for(j=0;j<len;++j)rev[i] = (rev[i]<<1)|dig[j];
		l = 0; for(j=i;j;j>>=1)  dig[l++] = 0;
	}
	FFT(a,L,1);
	for(int i=0;i<L;++i) a[i] = a[i] * a[i];
	FFT(a,L,-1);
	for(int i=0;i<L;++i) ans[i] += type * (int)(a[i].a+0.1);
	for(int i=0;i<L;++i) a[i].a = a[i].b = 0;
}

inline void solve(int x) {
	vis[x] = 1;
	tim[0] = ++cls; T[0] = 1;
	Max = 0;
	for(int i=head[x];i;i=edge[i].next) if(!vis[edge[i].to]) DFS2(edge[i].to, x, 1);
	calc(1);
	for(int i=head[x];i;i=edge[i].next) if(!vis[edge[i].to]) {
		cls++; Max = 0;
		DFS2(edge[i].to,x,1);
		calc(-1);
	}
	for(int i=head[x];i;i=edge[i].next) if(!vis[edge[i].to]) {
		sz = size[edge[i].to];
		F[root = 0] = inf;
		DFS1(edge[i].to,x);
		solve(root);
	}
}

int main() {
//	freopen("tt.in", "r", stdin);
	int n = read();
	for(int i=2;i<=n;++i) {
		int x = read() + 1, y = read() + 1;
		add(x,y);
	}
	F[root = 0] = inf;
	sz = n;
	DFS1(1,-1);
	int tmp = root;
	DFS1(root,-1);
	solve(tmp);
	f2 Ans = 0;
	for(int i=1;i<=n;++i)  Ans += (f2)ans[i] / (i+1);
	printf("%.4lf\n", n+Ans);
}
