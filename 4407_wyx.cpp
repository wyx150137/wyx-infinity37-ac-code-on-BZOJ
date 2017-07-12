
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 5000000+5;
const int mod = 1e9+7;

inline int pow(int a,int b) {
	LL res = 1;
	for(;b;b>>=1,a=(LL)a*a%mod)
		if(b&1)
			res = res * a % mod;
	return res;
}

int prime[N], cnt, s[N], pwn[N], k, n;
bool F[N];

inline void init() {
	s[1] = 1;
	const int Max =  5000000;
	for(int i=1;i<=Max;++i) pwn[i] = pow(i, k);
	for(int i=2;i<=Max;++i) {
		if(!F[i]) {
			prime[++cnt] = i;
			s[i] = pwn[i] - 1;
		} 
		for(int j=1;prime[j]*i<=Max;++j) {
			F[prime[j]*i] = 1;
			if(i%prime[j] == 0) {
				s[i*prime[j]] = (LL)s[i] * pwn[prime[j]] % mod;
				break;
			}
			s[i*prime[j]] = (LL)s[i] * s[prime[j]] % mod;
		}
	}
	for(int i=2;i<=Max;++i) (s[i] += s[i-1]) %= mod; 
}

inline int calc(int n,int m) {
	LL ans = 0;
	for(int i=1,last;i<=min(n,m);i=last+1) {
		last = min(n/(n/i),m/(m/i));
		LL temp1 = n / i, temp2 = m / i;
		temp1 = (LL) temp1 * temp2 % mod;
		temp1 = temp1 * (s[last] - s[i-1] + mod) % mod;
		ans = (ans + temp1) % mod;
	}
	return  ans;
}

int main() {
	int T;
	cin >> T >> k;
	init();
	for(int i=1;i<=T;++i) {
		int n, m;
		cin >> n >> m;
		printf("%d\n", calc(n,m));
	}
}
