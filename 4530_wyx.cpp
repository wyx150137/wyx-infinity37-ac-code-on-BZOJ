
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 100000+5;
typedef long long LL;
inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch  > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <= '9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int size[N], ch[N][2], tr[N], fa[N];
bool rev[N], root[N];

inline void updata(int x) {
	size[x] = size[ch[x][0]] + size[ch[x][1]] + 1 + tr[x];
}

inline void solve(int x) {
	if(!x) return;
	rev[x] ^= 1;
	swap(ch[x][0], ch[x][1]);
}

inline void push_down(int x) {
	if(rev[x]) {
		rev[x] ^= 1;
		solve(ch[x][0]);
		solve(ch[x][1]);
	}
}

inline void down(int x) {
	if(!root[x]) down(fa[x]);
	push_down(x);
}

inline void rotate(int x) {
	int y = fa[x], z = ch[y][1] == x;
	ch[y][z] = ch[x][!z];fa[ch[y][z]] = y;
	ch[x][!z] = y; fa[x] = fa[y]; fa[y] = x;
	if(root[y]) swap(root[x], root[y]);
	else ch[fa[x]][ch[fa[x]][1] == y] = x;
	updata(y);
	updata(x);
}

inline void splay(int x) {
	down(x);
	while(!root[x]) {
		int y = fa[x], z = fa[y];
		if(root[y]) rotate(x);
		else if((ch[y][1] == x) == (ch[z][1] == y)) rotate(y), rotate(x);
		else rotate(x), rotate(x);
	}
}

inline void access(int x) {
	int y = 0;
	while(x) {
		splay(x);
		tr[x] += size[ch[x][1]];
		root[ch[x][1]] = 1;
		ch[x][1] = y;
		root[ch[x][1]] = 0;
		tr[x] -= size[ch[x][1]];
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
	move(y);
	fa[x] = y;
	tr[y] += size[x];
	updata(y);
}

int main() {
	int i, x, y;
	char str[10];
	int n = read(), m = read();
	for(i=1;i<=n;++i) size[i] = 1, root[i] = 1;
	for(i=1;i<=m;++i) {
		scanf("%s", str);
		x = read(), y = read();
		if(str[0] == 'A') {
			link(x,y);
		}
		else {
			move(x);
			access(y);
			splay(x);
			printf("%lld\n", (LL) (tr[y]+1)*(size[x]-tr[y]-1));
		}
	}
}
