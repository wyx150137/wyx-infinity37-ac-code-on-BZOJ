
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1000+5;
const int Max = 1000;
const int mod = 1e9+7;
typedef long long LL;
int fac[N], ifac[N];

inline int C(int n,int m) {
	return (LL)	fac[n] * ifac[m] % mod * ifac[n-m] % mod;
}

inline int pow(int a,int b) {
	LL res = 1;
	for(;b;b>>=1,a=(LL)a*a%mod)
		if(b&1)
			res = res * a % mod;
	return res;
}

LL F[N];

int main() {
	int n, m;
	cin >> n >> m;
	if(m == 1) {cout << ((LL)n*(n+1)/2)%mod << endl; return 0;}
	fac[0] = 1;
	for(int i=1;i<=Max;++i) fac[i] = (LL) fac[i-1] * i % mod;
	ifac[Max] = pow(fac[Max], mod-2);
	for(int i=Max-1;i>=0;--i) ifac[i] = (LL)ifac[i+1] * (i+1) % mod;
	int inv = pow(m - 1, mod - 2);
	F[0] = (LL)(pow(m, n+1) - m + mod) % mod * inv % mod;
	for(int i=1;i<=Max;++i) {
		int ans = 0;
		ans = (LL)pow(n, i) * pow(m ,n+1) % mod; 
		for(int j=0;j<i;++j) {
			if((i-j)&1) (ans += mod - (LL) C(i, j) * F[j] %mod) %= mod;
			else (ans += (LL) C(i, j) * F[j] % mod) %= mod;
		}
		ans = (LL) ans * inv % mod;
		F[i] = ans;
	}
	cout << F[m] << endl;
} 
