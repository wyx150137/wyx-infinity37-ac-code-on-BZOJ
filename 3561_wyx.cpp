
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 5e5+5;
const int mod = 1e9+7;
typedef long long LL;
int prime[N], cnt, mu[N];
bool F[N];

inline int pow(int a,int b) {
	LL res = 1;
	for(;b;b>>=1,a=(LL)a*a%mod)
		if(b&1)
			res = (LL) res * a % mod;
	return res;
}

inline void init() {
	const int Max = 5e5;
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
}

int sum[N], a[N];

int main() {
	init();
	int n, m;
	cin >> n >> m;
	if(m > n) swap(n,m);
	register int i, j;
	int ans = 0;
	for(i=1;i<=n;++i) a[i] = 1;
	for(i=1;i<=m;++i) {
		int x = pow(i,i), y = 0;
		for(j=1;j*i<=n;++j) {
			a[j] = (LL) a[j] *j % mod;
			sum[j] = (sum[j-1] + a[j]) % mod;
		}
		for(j=1;j*i<=m;++j) if(mu[j]) 
			(y += (LL)a[j] * a[j] % mod * sum[m/i/j] % mod * sum[n/i/j] % mod * mu[j] % mod) %= mod;
		(ans += (LL) x * y % mod) %= mod;
	}
	cout << ans << endl;
}
