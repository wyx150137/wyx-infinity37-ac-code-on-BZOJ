
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e6+5;
int prime[N], cnt, mu[N];
bool F[N];
typedef long long LL;

inline int pow(int a,int b,int mod) {
	LL res = 1;
	for(;b;b>>=1,a=(LL)a*a%mod)
		if(b&1)
			res = res * a % mod;
	return res;
}

inline void init() {
	const int Max = 1e6;
	mu[1] = 1;
	for(int i=2;i<=Max;++i) {
		if(!F[i]) mu[i] = -1, prime[++cnt] = i;
		for(int j=1;prime[j]*i<=Max;++j) {
			F[i*prime[j]] = 1;
			if(i%prime[j]==0) break;
			mu[i*prime[j]] = -mu[i];
		} 
	}
}

int f[N], h[N], g[N], inv[N];

int main() {
	int T;
	cin >> T;
	init();
	while(T--)  {
		int Max, mod;
		cin >> Max >> mod;
		f[1] = 1, f[2] = 2;
		register int i; int x;
		for(i=3;i<=Max;++i) f[i] = (2ll * f[i-1] + f[i-2]) % mod;
		for(i=1;i<=Max;++i) h[i] = 1;
		for(i=1;i<=Max;++i) inv[i] = pow(f[i], mod-2,mod);
		for(int d=1;d<=Max;++d) {
			for(i=1;i*d<=Max;++i) {
				x = i * d;
				if(mu[i] == 1) 
					h[x] = (LL) h[x] * f[d] % mod;
				else if(mu[i] == -1) 
					h[x] = (LL) h[x] * inv[d] % mod;
			}
		}
		for(i=2;i<=Max;++i) h[i] = (LL) h[i] * h[i-1] % mod;
		for(i=1;i<=Max;++i) g[i] = h[i];
		LL ans = 0;
		for(i=1;i<=Max;++i) ans = (ans + (LL) g[i] * i % mod) % mod;
		cout << ans << endl;
	}
}	
