
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 200000+5;
const int M = N;
int F[N], stack[N];
bool v[N];

inline int find(int x) {
	while(F[x] != x && F[x]) {
		stack[++stack[0]] = x;
		x = F[x];
	}
	F[x] = x;
	while(stack[0]) 
		F[stack[stack[0]--]] = x;
	return x;
}

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

struct data {
	int x, y, val;
	data () {}
	data (int _x,int _y,int _val):x(_x),y(_y),val(_val) {}
	bool operator < (const data &z) const {
		return val < z.val;
	}
} edge[M];


int main() {
	int n = read(), m = read(), z;
	int top = 0;
	register int i, j;
	for(int i=1;i<=n+m;++i) F[i] = i;
	for(i=1;i<=n;++i) {
		for(j=1;j<=m;++j) {
			z = read();
			edge[++top] = data(i, j+n, z);
		}
	}
	sort(edge+1,edge+top+1);
	long long ans = 0;
	for(i=1;i<=top;++i) {
		int x = find(edge[i].x), y =find(edge[i].y);
		if(v[x] && v[y]) continue;
		if(x != y) {
			v[y] |= v[x];
			F[F[x]] = F[y];
		}
		else v[x] = 1;
		ans += edge[i].val;
	}
	cout << ans << endl;
}
