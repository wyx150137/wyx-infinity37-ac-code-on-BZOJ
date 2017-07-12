
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e6+5;
inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int val[N], ch[N][2], tr[N], fa[N];
bool rev[N], root[N];

void updata(int x)
{tr[x]=max(max(tr[ch[x][0]],tr[ch[x][1]]),val[x]);}

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

int F[N];

inline int find(int x) {
	return F[x] ^ x ? F[x] = find(F[x]) : F[x];
}

int main() {
//	freopen("tt.in","r",stdin);
	int n = read(), m = read(), lastans = 0;
	for(int i=1;i<=n;++i) F[i] = i;
	for(int i=1;i<=n+m;++i) root[i] = 1;
	int cnt = 0;
	for(int i=1;i<=m;++i) {
		int opt = read(); 
		int x = read() ^ lastans, y = read() ^ lastans;
		//int x = read(), y = read();
		if(opt == 0) {
			tr[i+n] = val[i+n] = ++ cnt;
			int fx = find(x), fy = find(y);
			if(fx == fy) continue;
			F[fy] = fx;
			link(x,i+n);
			link(y,i+n);
		}
		else {
			if(find(x)!=find(y)) {
				puts("0");
				lastans = 0;
				continue;
			}
			move(x);
			access(y);
			splay(y);
			printf("%d\n", lastans = tr[y]);
		}
	}
}
