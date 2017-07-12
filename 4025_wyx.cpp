
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 5e5+5;
const int M = N;

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
int ans, n, m;

struct data{
	int from, to, val;
} e[M];

struct graph {
	int next, to;
	graph () {}
	graph (int _next,int _to)
	:next(_next), to(_to) {}
} edge[M];

int head1[N], head2[N], cnt;

inline void add1(int x,int y) {
	edge[++cnt] = graph(head1[x], y);
	head1[x] = cnt;
}

inline void add2(int x,int y) {
	edge[++cnt] = graph(head2[x], y);
	head2[x] = cnt;
}

int fa[N], val[N], pos[N], ch[N][2];
int size[N];
bool rev[N], root[N], in[N], on[N];

inline void updata(int k) {
	size[k] = size[ch[k][0]] + size[ch[k][1]] + (k > n);
	pos[k] = k;
	if(val[pos[ch[k][0]]] < val[pos[k]]) pos[k] = pos[ch[k][0]];
	if(val[pos[ch[k][1]]] < val[pos[k]]) pos[k] = pos[ch[k][1]];
}

inline void solve(int x) {
	swap(ch[x][0], ch[x][1]);
	rev[x] ^= 1;
}

inline void push_down(int x) {
	if(rev[x]) {
		if(ch[x][0]) solve(ch[x][0]);
		if(ch[x][1]) solve(ch[x][1]);
		rev[x] ^= 1;
	}
}

inline void down(int x) {
	if(!root[x]) down(fa[x]);
	push_down(x);
}

inline void rotate(int x) {
	int y = fa[x], z = ch[y][1] == x;
	ch[y][z] = ch[x][!z]; fa[ch[y][z]] = y;
	ch[x][!z] = y; fa[x] = fa[y]; fa[y] = x;
	if(root[y]) swap(root[x], root[y]);
	else ch[fa[x]][ch[fa[x]][1] == y] = x;
	updata(y);
}

inline void splay(int x) {
	down(x);
	while(!root[x]) {
		int y = fa[x], z = fa[y];
		if(root[y]) rotate(x);
		else if((ch[y][1] == x) == (ch[z][1] == y)) rotate(y), rotate(x);
		else rotate(x), rotate(x);
	}
	updata(x);
}

inline void access(int x) {
	int y = 0;
	while(x) {
		splay(x);
		root[ch[x][1]] = true;
		ch[x][1] = y;
		root[ch[x][1]] = false;
		updata(x);
		y = x;
		x = fa[x];
	}
}

inline void move(int x) {
	access(x);
	splay(x);
	solve(x);
}

inline void link(int x,int y) {
	move(x);
	fa[x] = y;
}

inline void cut(int x,int y) {
	move(x);
	access(y);
	splay(y);
	root[x] = 1;
	ch[y][0] = fa[x] = 0;
	updata(y);
}

inline int find(int x) {
	access(x); splay(x);
	while(ch[x][0]) x = ch[x][0]; 
	return x;
}

inline void insert(int x) {
	int u = e[x].from, v = e[x].to, temp = e[x].val;
	if(u == v) {
		in[x] = 1;
		ans ++;
		return;
	}
	if(find(u) != find(v)) {
		on[x] = 1;
		link(u, x + n);
		link(x + n, v);
	}
	else {
		move(v);
		access(u);
		splay(u);
		int y = pos[u] - n;
		if(e[y].val < temp) {
			if((size[u] & 1) == 0) {
				in[y] = 1;
				ans ++;
			}
			cut(e[y].from, y + n);
			cut(e[y].to, y + n);
			link(u, x + n);
			link(v, x + n);
			on[y] = 0;
			on[x] = 1;
		}
		else {
			if((size[u] & 1) == 0) {
				in[x] = 1;
				ans  ++;
			}
		}
	}
}

inline void del(int x) {
	if(on[x]) {
		cut(e[x].from, x + n);
		cut(e[x].to , x + n);
	}
	else if(in[x]) ans --;
}

int main() {
//	freopen("tt.in","r",stdin);
	n = read(), m = read();
	int T = read();
	memset(val, 0x3f, sizeof val);
	for(int i=1;i<=n+m;++i) pos[i] = i;
	for(int i=1;i<=n+m;++i) root[i] = 1;
	for(int i=1;i<=m;++i) size[i+n] = 1;
	for(int i=1;i<=m;++i) {
		e[i].from = read(), e[i].to = read();
		int temp1 = read(), temp2 = read();
		val[n+i] = e[i].val = temp2;
		add1(temp1, i); add2(temp2, i);
	}
	for(int i=0;i<T;++i) {
		for(int j=head1[i];j;j=edge[j].next) insert(edge[j].to);
		for(int j=head2[i];j;j=edge[j].next) del(edge[j].to);
		puts(ans ? "No" : "Yes");
	}
}
