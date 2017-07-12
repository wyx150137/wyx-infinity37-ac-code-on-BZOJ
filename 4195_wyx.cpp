
#include <map>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1000000+5;
inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

struct data {
	int x, y, opt;
} a[N];

int fa[N], size[N];

inline int find(int x) {
	return fa[x] ^ x ? fa[x] = find(fa[x]) : fa[x];
}

inline void Union(int x,int y) {
	x = find(x), y = find(y);
	if(x == y) return;
	if(size[x] < size[y]) swap(x, y);
	size[x] += size[y];
	fa[y] = x;
}

int cnt, T[N];

inline void init(int n) {
	for(int i=1;i<=n;++i) size[fa[i] = i] = 1;
}

int main() {
//	freopen("prog.in","r",stdin);
//	freopen("prog.out","w",stdout);
//	freopen("tt.in","r",stdin);
	int testcases;
	for(cin >> testcases; testcases; testcases--) {
		int n = read();
		for(int i=1;i<=n;++i) {
			T[++cnt] = a[i].x = read();
			T[++cnt] = a[i].y = read();
			a[i].opt = read();
		}
		sort(T+1,T+cnt+1);
		int top = 0;
		for(int i=1;i<=cnt;++i) if(T[i] != T[i-1]) T[++top] = T[i];
		cnt = top;
		init(cnt);
		for(int i=1;i<=n;++i) {
			a[i].x = lower_bound(T+1,T+cnt+1,a[i].x) - T;
			a[i].y = lower_bound(T+1,T+cnt+1,a[i].y) - T;
			if(a[i].opt == 1) Union(a[i].x, a[i].y);
		}
		bool flag = false;
		for(int i=1;i<=n;++i) {
			if(a[i].opt == 0 && find(a[i].x) == find(a[i].y))
				flag = true;
		}
		if(flag) {
			puts("NO");
		}
		else puts("YES");
	}
}
