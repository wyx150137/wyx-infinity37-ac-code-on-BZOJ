
#include <cmath>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
const long long N = 4e6+5;
const long long mod = 1e9+7;
const long long M = 3e3+5;

inline LL read() {
	LL x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

bool F[N];
long long prime[N], cnt, phi[N];
LL sum[N];

inline void init() {
	phi[1] = 1;
	const long long Max = 4e6;
	for(long long i=2;i<=Max;++i) {
		if(!F[i]) {
			prime[++cnt] = i;
			phi[i] = i - 1;
		}
		for(long long j=1;prime[j]*i<=Max;++j) {
			F[i*prime[j]] = 1;
			if(i%prime[j]==0) {
				phi[i*prime[j]] = phi[i] * prime[j];
				break;
			}
			phi[i*prime[j]] = phi[i] * (prime[j]-1);
		}
	}
	for(long long i=1;i<=Max;++i) sum[i] = (sum[i-1] + (LL) i * i % mod * phi[i]%mod) % mod;
}

inline LL pow(LL a,long long b) {
	LL res = 1;
	for(;b;b>>=1,a=(LL)a*a%mod)
		if(b&1) res = res * a % mod;
	return res;
}

long long Q, n, a, b, k;
LL x;

struct Block {
	long long F[N], add[N], a[N];
	long long bl[N], sz, m;
	long long L[N], R[N];

	inline void init() {
		sz = (long long) sqrt(n);
		m = (n-1)/sz + 1;
		for(long long i=1;i<=n;++i) bl[i] = (i-1) / sz + 1, a[i] = (LL)i*i%mod, F[i] = a[i] + F[i-1] % mod;
		for(long long i=1;i<=m;++i) L[i] = (i-1)*sz + 1, R[i] = i * sz;
	}

	inline long long ask(long long x) {
		return (F[x] + add[bl[x]])  % mod;
	}

	inline void change(long long x,long long val) {
		long long tt = (val - a[x] + mod) % mod;
		long long r = R[bl[x]];
		a[x] = val;
		if(tt == 0) return;
		for(long long i=x;i<=r;++i) F[i] = (F[i] + tt) % mod;
		for(long long i=bl[x]+1;i<=m;++i) add[i] = (add[i] + tt)  % mod;
	}
} block;

inline void solve(long long n) {
	long long ans = 0,r , last = 0, now;
	for(long long i=1;i<=n;i=r+1,last=now) {
		r = n/(n/i);
		now = block.ask(r);
		ans = (ans + (LL) (now - last + mod)*sum[n/i] % mod) % mod;
	}
	printf("%d\n", (ans+mod)%mod);
}

int main() {
	Q = read() , n = read();
	init();
	block.init();
	for(long long i=1;i<=Q;++i) {
		a = read(), b = read();
		x = read(), k = read();
		x %= mod;
		long long d = __gcd(a, b);
		block.change(d, (LL)d*d%mod*x%mod*pow((LL)a*b%mod, mod-2)%mod);
		solve(k);
	}
}
