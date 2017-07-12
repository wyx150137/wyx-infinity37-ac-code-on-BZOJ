
#include <queue>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e6+5;
typedef long long LL;
const int inf = 2147483647;
int ch[N][2], fa[N], lazy[N], root, size[N];
int val[N];


inline char getc()
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
 
inline int read()
{
    static char ch;
    static int D;
    while(!isdigit(ch=getc()));
    for(D=ch-'0'; isdigit(ch=getc());)
        D=(D<<3)+(D<<1)+(ch-'0');
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
	__attribute__((optimize("-O2"))) void flush()
	{
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

inline void add(int k,int _val) {
	lazy[k] += _val;
	val[k] += _val;
}

inline void down(int k) {
	if(lazy[k]) {
		if(ch[k][0]) add(ch[k][0], lazy[k]);
		if(ch[k][1]) add(ch[k][1], lazy[k]);
		lazy[k] = 0;
	}
}

inline void updata(int k) {
	size[k] = 1;
	if(ch[k][0]) size[k] += size[ch[k][0]];
	if(ch[k][1]) size[k] += size[ch[k][1]];
}

inline void rotate(int x) {
	int y = fa[x], z = ch[y][1] == x;
	ch[y][z] = ch[x][!z]; fa[ch[y][z]] = y;
	ch[x][!z] = y; fa[x] = fa[y]; fa[y] = x;
	ch[fa[x]][ch[fa[x]][1] == y] = x;
	updata(y); updata(x);
}

inline void splay(int x,int w) {
	while(fa[x] != w) {
		int y = fa[x], z = fa[y];
		down(z); down(y);
		if(z == w) rotate(x);
		else if((ch[y][1] == x) == (ch[z][1] == y)) rotate(y), rotate(x);
		else rotate(x), rotate(x);
	}
	if(!w) root = x;
}

inline int newnode() {
	static int sz = 0;
	return ++sz;
}

inline void insert(int &k,int val,int F) {
	if(!k) {
		k = newnode();
		fa[k] = F;
		::val[k] = val;
		lazy[k] = ch[k][0] = ch[k][1] = 0;
		size[k] = 1;
		return;
	}
	down(k);
	if(val <= ::val[k]) insert(ch[k][0], val, k);
	else insert(ch[k][1], val, k);
	updata(k);
}

int ans;

inline void find_pre(int k,int val) {
	if(!k) return;
	down(k);
	if(::val[k] < val) {
		ans = k;
		find_pre(ch[k][1], val);
	}
	else find_pre(ch[k][0], val);
}

inline void find_aft(int k,int val) {
	if(!k) return;
	down(k);
	if(::val[k] > val) {
		ans = k;
		find_aft(ch[k][0], val);
	}
	else find_aft(ch[k][1], val);
}

inline int find(int k,int temp) {
	int tt = size[ch[k][0]];
	down(k);
	if(temp <= tt) return find(ch[k][0], temp);
	else if(temp == tt + 1) return k;
	else return find(ch[k][1], temp - tt - 1);
}

int stack[N], top;

inline void solve(int &k) {
	if(!k) return;
	down(k);
	stack[++top] = val[k];
	solve(ch[k][0]);
	solve(ch[k][1]);
	k = 0;
}

int n, m;

inline void build(int &k,int l,int r,int F) {
	if(l > r) return;
	k = newnode();
	fa[k] = F;
	int mid = (l+r) >> 1;
	val[k] = stack[mid];
	ch[k][0] = ch[k][1] = 0;
	size[k] = 1;
	lazy[k] = 0;
	build(ch[k][0], l, mid-1, k);
	build(ch[k][1], mid+1, r, k);
	updata(k);
}

inline void rebuild() {
	top = 0;
	solve(root);
	sort(stack+1,stack+top+1);
	build(root, 1, n + 2, 0);
}

int main() {
	n = read(), m = read();
	root = newnode();
	ch[root][1] = newnode();
	fa[ch[root][1]] = root;
	val[root] = -inf;
	val[ch[root][1]] = inf;
	updata(ch[root][1]);
	updata(root);
	bool flag = false;
	for(int i=1;i<=n;++i) {
		int x = read();
		insert(root, x, 0);
		splay(i+2,root);
	}
	for(int i=1;i<=m;++i) {
		int opt = read();
		if(opt == 1) {
			int k = read();
			ans = find(root, k + 1);
			splay(ans, 0);
			print(val[ans]);
		}
		else {
			int k = read();
			find_pre(root,k+1);
			splay(ans, 0);
			find_aft(root,2*k);
			splay(ans, root);
			top = 0;
			solve(ch[ch[root][1]][0]);
			updata(ch[root][1]);
			updata(root);
			for(int j=1;j<=top;++j) insert(root, stack[j] - k, 0);
			find_pre(root, 2*k+1);
			splay(ans, 0);
			splay(2,root);
			if(ch[2][0])add(ch[2][0], -k);
		}
	}
	io::flush();
}
