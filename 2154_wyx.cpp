
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
const int mod = 20101009;
const int N = 10000000+5;
int g[N], prime[N], cnt;
bool F[N];

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

inline void init() {
	const int Max = 10000000;
	g[1] = 1;
	register int j = 1;
	for(int i=2;i<=Max;++i) {
		if(!F[i]) {
			prime[++cnt] = i;
			g[i] = 1 - i;
		}
		for(j=1;prime[j]*i<=Max;++j) {
			F[prime[j]*i] = 1;
			if(i%prime[j]==0) {
				g[i*prime[j]] = g[i];
				break;
			}
			g[i*prime[j]] = (LL)g[i]*(1-prime[j])%mod; 
		}
	}
	for(int i=1;i<=Max;++i) g[i] = (g[i-1] + (LL)i * g[i] % mod) % mod; 
}

inline int calc(LL n,LL m) {
	LL ans = 0;
	for(int i=1,last=0;i<=min(n,m);i=last+1) {
		last = min(n/(n/i),m/(m/i));
		LL temp1 = n / i;
		LL temp2 = m / i;
		temp1 = (temp1 + 1) * temp1 / 2;
		temp2 = (temp2 + 1) * temp2 / 2;
		temp1 = (temp1%mod) * (temp2%mod) % mod;
		ans = (ans + (LL)((g[last]-g[i-1]+mod)%mod+mod)%mod * temp1 % mod) % mod;
		if(ans < 0) cout << i << endl;
	}
	return ans % mod;
}

int main() {
	init();
	LL T = 1;
	while(T--) {
		LL x = read(), y = read();
		printf("%d\n", calc(x,y));
	}
}
