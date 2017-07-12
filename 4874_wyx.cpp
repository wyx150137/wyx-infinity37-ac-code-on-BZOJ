
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 2e5+5;
int F[N], size[N];

inline int find(int x) {
	return F[x] ^ x ? F[x] = find(F[x]) : F[x];
}

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int main() {
	int n = read(), m = read();
	swap(n,m);
	for(int i=1;i<=n;++i) F[i] = i;
	for(int i=1;i<=m;++i) {
		int x = read(), y = read(), fx = find(x), fy = find(y);
		if(fx == fy) size[fx] ++;
		else  {
			if(size[fx] < size[fy]) swap(fx, fy);
			size[fx] += size[fy] + 1;
			F[fy] = fx;
		}
	}
	int ans = 0;
	for(int i=1;i<=n;++i) 
		if(F[i] == i && (size[i] & 1))
			ans ++;
	cout << ans << endl;
}
