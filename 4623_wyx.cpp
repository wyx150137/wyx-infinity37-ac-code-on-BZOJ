
#include <vector>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int mod = 1e9+7;
const int N = 1e5+5;
const int M = N << 2;
const int inf = 0x3f3f3f3f;
#define pb push_back
typedef long long LL;

inline char getc() {
    static const int LEN = 1<<15;
    static char buf[LEN],*S=buf,*T=buf;
    if(S == T) {
        T = (S=buf)+fread(buf,1,LEN,stdin);
        if(S == T)return EOF;
    }
    return *S++;
}
  
inline int read() {
    static char ch;
    static int D;
    while(!isdigit(ch=getc()));
    for(D=ch-'0'; isdigit(ch=getc());)
        D=(D<<3)+(D<<1)+(ch-'0');
    return D;
}

#define RG register

namespace io {
    const int MaxBuff = 1 << 20;
    const int Output = 1 << 24;
    char B[MaxBuff], *S = B, *T = B;
    //#define getc() getchar()
    #define getc() ((S == T) && (T = (S = B) + fread(B, 1, MaxBuff, stdin), S == T) ? 0 : *S++)
    char Out[Output], *iter = Out;
    inline void flush() {
        fwrite(Out, 1, iter - Out, stdout);
        iter = Out;
    }
}
 
template<class Type> __attribute__((optimize("-O2")))  void print(RG Type x, RG char ch = '\n')
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

inline LL pow(LL a,int b) {
	LL res = 1;
	for(;b;b>>=1,a=(LL)a*a%mod)
		if(b&1) res = res * a % mod;
	return res;
}

inline LL inv(LL a) {
	return pow(a, mod-2);
}

namespace pre_work {
	const int N = 1e6+5, Max = 1e6;
	int prime[N], num, has[N];
	bool F[N];

	inline void init() {
		static int cnt = 0;
		for(int i=2;i<=Max;++i) {
			if(!F[i]) {prime[++cnt] = i; has[i] = cnt;}
			for(int j=1;prime[j]*i<=Max;++j) {
				F[i*prime[j]] = true;
				if(i%prime[j]==0) break;
			}
		}
	}

	LL q[N];
	LL sum = 1;

	inline void Add(int x,int y) {
		(sum *= inv(q[x]+1)) %= mod;
		q[x] += y;
		(sum *= (LL)(q[x]+1)) %= mod;
	}

	inline void add(int x,int type) {
		LL temp = x;
		for(int i=1;prime[i]*prime[i] <= temp; ++i) {
			if(temp % prime[i] == 0) {
				int tt = 0;
				while(temp % prime[i] == 0) {
					temp /= prime[i];
					tt ++;
				}
				Add(i, type * tt);
			}
		}
		if(temp != 1) Add(has[temp], type);
	}
}

int head[N];
int ans[N][3];
int size[N], F[N];

struct graph {
	int from, to, next;
	graph () {}
	graph (int _from,int _to,int _next) 
	:from(_from), to(_to), next(_next){}
}edge[M];

inline void add(int x,int y) {
	static int cnt = 0;
	edge[++cnt] = graph(x, y, head[x]); head[x] = cnt;
	edge[++cnt] = graph(y, x, head[y]); head[y] = cnt;
}

struct Matrix {
	int a[3][3];
	Matrix () {
		memset(a, 0, sizeof a);
	}	
	int *operator [] (int x) {
		return a[x];
	}
	inline void init(int *x) { //  0 -x2  x1
		a[0][0] = 0;           // x2   0 -x0
		a[0][1] = -x[2] + mod; //-x1  x0   0
		a[0][2] = x[1];
		a[1][0] = x[2];
		a[1][1] = 0;
		a[1][2] = -x[0] + mod;
		a[2][0] = -x[1] + mod;
		a[2][1] = x[0];
		a[2][2] = 0;
	}
	void out() {
		for(int i=0;i<3;++i) {
			for(int j=0;j<3;++j)
				cout << a[i][j] << ' ';
			puts("");
		}

	}
}Val[N], A[N], B[N], C;

inline void mul(Matrix &a, Matrix &b, Matrix &c){
	c[0][0]=((LL)a[0][0]*b[0][0]+(LL)a[0][1]*b[1][0]+(LL)a[0][2]*b[2][0])%mod;
	c[0][1]=((LL)a[0][0]*b[0][1]+(LL)a[0][1]*b[1][1]+(LL)a[0][2]*b[2][1])%mod;
	c[0][2]=((LL)a[0][0]*b[0][2]+(LL)a[0][1]*b[1][2]+(LL)a[0][2]*b[2][2])%mod;
	c[1][0]=((LL)a[1][0]*b[0][0]+(LL)a[1][1]*b[1][0]+(LL)a[1][2]*b[2][0])%mod;
	c[1][1]=((LL)a[1][0]*b[0][1]+(LL)a[1][1]*b[1][1]+(LL)a[1][2]*b[2][1])%mod;
	c[1][2]=((LL)a[1][0]*b[0][2]+(LL)a[1][1]*b[1][2]+(LL)a[1][2]*b[2][2])%mod;
	c[2][0]=((LL)a[2][0]*b[0][0]+(LL)a[2][1]*b[1][0]+(LL)a[2][2]*b[2][0])%mod;
	c[2][1]=((LL)a[2][0]*b[0][1]+(LL)a[2][1]*b[1][1]+(LL)a[2][2]*b[2][1])%mod;
	c[2][2]=((LL)a[2][0]*b[0][2]+(LL)a[2][1]*b[1][2]+(LL)a[2][2]*b[2][2])%mod;
}

int val[N], _val[N];
int a[N][3];

inline void DFS1(int x,int fa) {
	size[x] = 1;
	pre_work::add(val[x], 1);
	_val[x] = (LL)val[x] *_val[fa] % mod;
	a[x][0] = (pre_work::sum)*_val[x] % mod;
	a[x][1] = 4 * x;
	for(int i=head[x];i;i=edge[i].next) {
		if(edge[i].to != fa) {
			DFS1(edge[i].to, x);
			size[x] += size[edge[i].to];
		}
	}
	a[x][2] = size[x]; 
	pre_work::add(val[x],-1);
	Val[x].init(a[x]);
}

bool vis[N];
int sum, root, depth[N], Fa[N], col[N];

inline void DFS2(int x,int fa) {
	size[x] = 1; F[x] = 0;
	for(int i=head[x];i;i=edge[i].next) {
		if(edge[i].to != fa && !vis[edge[i].to]) {
			DFS2(edge[i].to, x);
			size[x] += size[edge[i].to];
			F[x] = max(F[x], size[edge[i].to]);
		}
	}
	F[x] = max(F[x], sum - size[x]);
	if(F[x] < F[root]) root = x;
}

int cnt;

inline void DFS3(int x,int fa,int z) {
	++ cnt;
	col[x] = z; Fa[x] = fa;
	depth[x] = depth[fa] ^ 1;
	mul(Val[x], A[fa], A[x]);
	mul(B[fa], Val[x], B[x]);
	for(int i=head[x];i;i=edge[i].next) {
		if(edge[i].to != fa && !vis[edge[i].to]) {
			DFS3(edge[i].to, x, z);
		}
	}
}

vector <int> V[N];
int X[N], Y[N], rt[N];

inline void solve(int x) {
	if(V[x].size()==0) return;
	vis[x] = 1; 
	col[x] = x;
	depth[x] = 0;
	Fa[x] = 0;
	memset(A[x].a, 0, sizeof A[x].a);
	memset(B[x].a, 0, sizeof B[x].a);
	for(int i=0;i<3;++i) A[x][i][i] = 1;
	for(int i=0;i<3;++i) 
		for(int j=0;j<3;++j) 
			B[x][i][j] = Val[x][i][j];
	for(int i=head[x];i;i=edge[i].next) {
		if(!vis[edge[i].to]) {
			cnt = 0;
			DFS3(edge[i].to, x, edge[i].to);
			size[edge[i].to] = cnt;
		}
	}
	for(int i=head[x];i;i=edge[i].next) {
		if(!vis[edge[i].to]) {
			sum = size[edge[i].to];
			F[root = 0] = inf;
			DFS2(edge[i].to, x);
			rt[edge[i].to] = root;
		}
	}
	for(int i=0;i<V[x].size();++i) {
		int tt = V[x][i], x = X[tt], y = Y[tt];
		if(col[x] != col[y]) {
			mul(A[y], B[Fa[x]], C);
			ans[tt][0]=((LL)C[0][0]*a[x][0]+(LL)C[0][1]*a[x][1]+(LL)C[0][2]*a[x][2])%mod;
			ans[tt][1]=((LL)C[1][0]*a[x][0]+(LL)C[1][1]*a[x][1]+(LL)C[1][2]*a[x][2])%mod;
			ans[tt][2]=((LL)C[2][0]*a[x][0]+(LL)C[2][1]*a[x][1]+(LL)C[2][2]*a[x][2])%mod;
			if (depth[x]^depth[y])
				ans[tt][0] = (mod - ans[tt][0])%mod, 
				ans[tt][1] = (mod - ans[tt][1])%mod, 
				ans[tt][2] = (mod - ans[tt][2])%mod;
		}
		else {
			V[rt[col[x]]].pb(tt);
		}
	}
	for(int i=head[x];i;i=edge[i].next) {
		if(!vis[edge[i].to]) {
			solve(rt[edge[i].to]);
		}
	}
}

int main() {
//  freopen("tt.in","r",stdin);
	pre_work::init();
	int n = read(), m = read();
	memset(B[0].a, 0, sizeof B[0].a);
	for(int i=0;i<3;++i) B[0][i][i] = 1;
	for(int i=1;i<=n;++i) val[i] = read();
	for(int i=1;i<n;++i) add(read(),read());
	_val[0] = 1;
	DFS1(1,0);
	sum = n;
	F[root = 0] = inf;
	DFS2(1,0);
	for(int i=1;i<=m;++i) {
		X[i] = read(), Y[i] = read();
		if(X[i] == Y[i]) {
			for(int j=0;j<3;++j) ans[i][j] = a[X[i]][j];
		}
		else V[root].pb(i);
	}
	solve(root);
	for(int i=1;i<=m;++i) {
		printf("%d %d %d\n", ans[i][0], ans[i][1], ans[i][2]);
	}
}
