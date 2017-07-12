
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e4+5;
#define solve(k) swap(ch[k][0], ch[k][1]); rev[k] ^= 1

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int ch[N][2], root[N], rev[N], fa[N];

inline void push_down(int k) {
	if(rev[k]) {
		if(ch[k][0]) solve(ch[k][0]);
		if(ch[k][1]) solve(ch[k][1]);
		rev[k] ^= 1;
	}
}

inline void down(int k) {
	if(!root[k]) {
		down(fa[k]);
	}
	push_down(k);
}

inline void rotate(int x) {
	int y = fa[x], z = ch[y][1] == x;
	ch[y][z] = ch[x][!z]; fa[ch[x][!z]] = y;
	ch[x][!z] = y;  fa[x] = fa[y]; fa[y] = x;
	if(root[y]) swap(root[x], root[y]);
	else {
		ch[fa[x]][ch[fa[x]][1] == y] = x;
	}
}

inline void Splay(int x) {
	down(x);
	while(!root[x]) {
		int y = fa[x], z = fa[y];
		if(root[y]) rotate(x);
		else if((ch[y][1] == x) == (ch[z][1] == y) ) rotate(y), rotate(x);
		else rotate(x), rotate(x);
	}
}

inline void access(int x) {
	int y = 0;
	while(x) {
		Splay(x);
		root[ch[x][1]] = 1; root[y] = 0; ch[x][1] = y;
		y = x; x = fa[x];
	}
}

inline int find(int x) {
	while(fa[x]) {
		x = fa[x];
	}
	return x;
}

inline void move(int x) {
	access(x);
	Splay(x);
	solve(x);
}

inline void link(int x,int y) {
	move(x);
	access(y);
	Splay(y);
	fa[x] = y;
}

inline void cut(int x,int y) {
	move(x);
	access(y);
	Splay(y);
	ch[y][0] = fa[x] = 0;
	root[x] = 1;
}

int main() {
//	freopen("tt.in", "r", stdin);
	int n = read();
	for(int i=1;i<=n;++i) root[i] = 1;
	int m = read(), x, y;char str[10];
	for(int i=1;i<=m;++i) {
		scanf("%s", str);
		x = read(), y = read();
		if(str[0] == 'Q') printf("%s\n", find(x) == find(y) ? "Yes" : "No");
		else if(str[0] == 'D') cut(x,y);
		else link(x,y);
	}
}
