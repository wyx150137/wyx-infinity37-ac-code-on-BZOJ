
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 1e6+5;
inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

struct data{
	LL l, r;
	bool operator < (const data &z) const {
		return l != z.l ? l < z.l : r > z.r;
	}
} a[N];

inline LL calc(int x,int y) {
	return (a[x].r-a[y].l)*(a[y].r-a[x].l);
}

bool flag[N];

int main() {
	int n = read();
	for(int i=1;i<=n;++i) a[i].l = read(), a[i].r = read();
	sort(a+1,a+n+1);
	register int j;
	int now = 0 , mxp = 0;
	LL ans = 0;
	for(int i=1;i<=n;++i) {
		if(a[i].r<=now) { 
			flag[i] = mxp;
			ans = max(ans, (LL)(a[i].r-a[i].l)*(a[mxp].r-a[mxp].l));
		}
		else flag[i] = 0;
		if(now < a[i].r) {
			now = a[i].r;
			mxp = i;
		}
	}  
	int top = 0;
	for(int i=1;i<=n;++i) if(flag[i] == 0) a[++top] = a[i];
	n = top;
	j = 2;
	for(int i=1;i<n;++i) {
		if(i == j) ++j;
		while(j+1<=n && calc(i,j+1) > calc(i,j)) ++ j;
		ans = max(ans, calc(i,j));
	}
	cout << ans << endl;
}
