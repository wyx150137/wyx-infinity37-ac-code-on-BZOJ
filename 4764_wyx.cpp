
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 2e5+5;
const int M = 1e3+5;
typedef long long LL;
int fa[N], son[N][2], size[N];
int cir[N], ch[N], n, m;
bool rev[N];
int a[N];

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

inline void updata(int k) {
	size[k] = size[son[k][0]] + size[son[k][1]] + 1;
}

inline void solve(int k) {
	if(!k) return;
	rev[k] ^= 1;
	swap(son[k][0], son[k][1]);
}

inline bool isroot(int x) {
	return !(son[fa[x]][0] == x || son[fa[x]][1] == x);
}

inline void cover(int x,int y) {
	if(!x) return;
	cir[x] = ch[x] = y;
}

inline void push_down(int k) {
	if(rev[k]) {
		solve(son[k][0]);
		solve(son[k][1]);
		rev[k] ^= 1;
	}
	if(ch[k] != -1) {
		cover(son[k][0], ch[k]);
		cover(son[k][1], ch[k]);
		ch[k] = -1;
	}
}

inline void rotate(int x) {
	int y = fa[x] , z = son[y][1] == x;
	bool tmp = isroot(y);
	son[y][z] = son[x][!z], fa[son[y][z]] =  y;
	son[x][!z] = y; fa[x] = fa[y]; fa[y] = x;
	if(!tmp) son[fa[x]][son[fa[x]][1] == y] = x;
	updata(y);
}

inline void down(int x) {
	if(!isroot(x)) down(fa[x]);
	push_down(x);
}

inline void splay(int x) {
	down(x);
	while(!isroot(x)) {
		int y = fa[x], z = fa[y];
		if(isroot(y)) rotate(x);
		else if((son[y][1]==x) == (son[z][1] == y)) rotate(y), rotate(x);
		else rotate(x), rotate(x);
	}
	updata(x);
}

void access(int x) {
	int y = 0;
	while(x) {
		splay(x);
		son[x][1] = y;
		updata(x);
		y = x; x = fa[x];
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
	son[y][0] = fa[x] = 0;
	updata(x);
}

inline int find(int x) {
	access(x);
	splay(x);
	push_down(x);
	while(son[x][0]) {
		x = son[x][0];
		push_down(x);
	}
	return x;
}

inline void solve_link(int x,int y) {
	if(find(x) == find(y)) {
		move(x);
		access(y);
		splay(y);
		cover(y, x);
	}
	else link(x, y);
}

inline void solve_cut(int x,int y) {
	access(x); splay(x);
	access(y); splay(y);
	int tmp3 = find(x);
	if(cir[x] && cir[x] == cir[y]) {
		int tmp = tmp3 + a[tmp3];
		access(tmp);
		splay(tmp);
		cover(tmp, 0);
		if(x != tmp3 || y != tmp) {
			cut(x,y);
			link(tmp3, tmp);
		}
	}
	else {
		cut(x,y);
		move(tmp3);
	}
}

int main() {
//	freopen("tt.in","r",stdin);
	memset(ch, -1, sizeof ch);
	int n = read(), m = read();
	for(int i=1;i<=n;++i) size[i] = 1;
	for(int i=1;i<=n;++i) {
		a[i] = read();
		if(i + a[i] >= 1 && i + a[i] <= n &&  a[i]) 
			solve_link(i, i + a[i]);
	}
	for(int i=1;i<=m;++i) {
		int opt = read();
		if(opt == 1) {
			int x = read();
			int y = find(x);
			if(cir[y]) puts("-1");
			else {
				if(!a[y]) puts("-1");
				else printf("%d\n", size[x]);
			}
		}
		else {
			int x = read(), y = read();
			int tmp = x + a[x];
			if(tmp < 1 || tmp > n || !a[x]) {
				a[x] = y;
				if(x + a[x] >= 1 && x + a[x] <= n) solve_link(x, x + a[x]);
			}
			else {
				solve_cut(x, tmp);
				a[x] = y;
				if(x + a[x] >= 1 && x + a[x] <= n) {
					solve_link(x, x + a[x]);
				}
			}
		}
	}
}
