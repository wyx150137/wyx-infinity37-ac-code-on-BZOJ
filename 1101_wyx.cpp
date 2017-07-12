
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 5e4+5;
typedef long long LL;
int prime[N], cnt, mu[N];
bool F[N];

inline void init() {
	mu[1] = 1;
	int i, j;
	const int Max = 5e4;
	for(i=2;i<=Max;++i) {
		if(!F[i]) {
			prime[++cnt] = i;
			mu[i] = -1;
		}
		for(j = 1; prime[j] * i <= Max; ++j) {
			F[i*prime[j]] = 1;
			if(i%prime[j]==0) break;
			mu[i*prime[j]] = -mu[i];
		}
	}
	for(int i=1;i<=Max;++i) mu[i] += mu[i-1];
}

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

inline LL calc(int x,int y) {
	LL ans = 0;
	for(int i=1,last=0;i<=min(x,y);i=last+1) {
		last = min(x/(x/i),y/(y/i));
		ans += (LL)(mu[last]-mu[i-1])*(x/i)*(y/i);
	}
	return ans;
}

int main() {
	init();
	int n = read();
	for(int i=1;i<=n;++i) {
		int a = read(), b = read(), d = read();
		a /= d, b /= d;
		printf("%lld\n", calc(a,b));
	}
}
