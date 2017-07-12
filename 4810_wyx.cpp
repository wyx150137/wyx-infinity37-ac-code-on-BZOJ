
#include <cmath>
#include <vector>
#include <bitset>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
#define pb push_back
const int Max = 100000;
const int N = 100000+5;
bitset <Max+5> f, g;
int a[N], T[N], ans[N];

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

struct data{
	int opt,x, y, bl, id, val;
	bool operator < (const data &z) const {
		return bl ^ z.bl ? bl < z.bl : y > z.y;
	}
} b[N];

inline void add(int x) {
	T[x] ++;
	f[x] = 1;
	g[Max-x] = 1;
}

inline void del(int x) {
	T[x] --;
	if(T[x] == 0) {
		f[x] = 0;
		g[Max-x] = 0;
	}
}

vector <int> V[Max+5];

int main() {
//	freopen("tt.in","r",stdin);
	int n = read() , m = read();
	for(int i=1;i<=n;++i) a[i] = read();
	int sz = (int)sqrt(n)+1;
	for(int i=1;i<=m;++i) {
		b[i].opt = read();
		b[i].x = read(), b[i].y = read(), b[i].bl = (b[i].x -1)/ sz + 1, b[i].id = i;
		b[i].val = read();
	}
	for(int i=1;i<=Max;++i) {
		for(int j=i;j<=Max;j+=i) {
			V[j].pb(i);
		}
	}
	sort(b+1,b+m+1);
	add(0);
	int l = 0, r = 0;
	for(int i=1;i<=m;++i) {
		while(l > b[i].x) add(a[--l]);
		while(r < b[i].y) add(a[++r]);
		while(l < b[i].x) del(a[l++]);
		while(r > b[i].y) del(a[r--]);
		if(b[i].opt == 1) ans[b[i].id] = ((f>>(b[i].val))&f).count();
		else if(b[i].opt == 2) ans[b[i].id] = ((g>>(Max-b[i].val))&f).count();
		else if(b[i].opt == 3) {
			for(int j=0;j<V[b[i].val].size();++j) {
				if(f[V[b[i].val][j]] && f[b[i].val/V[b[i].val][j]]) ans[b[i].id] = 1;
			}
			if(b[i].val == 0 && f[0]) ans[b[i].id] = 1;
		}
	}
	for(int i=1;i<=m;++i) 
		if(ans[i]) puts("yuno");
		else puts("yumi");
}
