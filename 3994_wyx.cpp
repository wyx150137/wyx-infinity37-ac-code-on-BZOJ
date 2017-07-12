
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 50000+5;
const int Max = 50000;
typedef long long LL;

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int prime[N], cnt, mu[N];
LL f[N];
bool F[N];

inline void init() {
	mu[1] = 1;
	for(int i=2;i<=Max;++i) {
		if(!F[i]) {
			prime[++cnt] = i;
			mu[i] = -1;
		}
		for(int j=1;prime[j]*i<=Max;++j) {
			F[i*prime[j]] = 1;
			if(i%prime[j]==0) break;
			mu[i*prime[j]] = -mu[i];
		}
	}
	for(int i=2;i<=Max;++i) mu[i] += mu[i-1];
} 

inline LL get(int x) {
	LL ans = 0;
	for(int i=1,last;i<=x;i=last+1) {
		last = x / (x/i);
		ans += (LL)(last-i+1) * (x/i);
	}
	return ans;
}

int main() {
	init();
	for(int i=1;i<=Max;++i) f[i] = get(i);
	int T; cin >> T; while(T--) {
		int x = read(), y = read();
		LL ans = 0;
		for(int i=1,last;i<=min(x,y);i=last+1) {
			last = min(x/(x/i), y/(y/i));
			ans += f[x/i] * f[y/i] * (mu[last]-mu[i-1]);
		}
		printf("%lld\n", ans);
	}
}
