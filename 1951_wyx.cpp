
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int Mod = 999911659;
const int phi = Mod - 1;
const int N = 4e5+5;
using namespace std;
typedef long long LL;
LL prime[4] = {2,3,4679,35617};
LL n, g, ans[4];
LL fac[4][N], inv[4][N];

void init(LL mod,LL* fac,LL* inv) {
	register int i;
	fac[0] = 1; for(i=1;i<mod;++i) fac[i] = fac[i-1]*i%mod;
	inv[1] = 1; for(i=2;i<mod;++i) inv[i] = (mod-mod/i)*inv[mod%i]%mod;
	inv[0] = 1; for(i=1;i<mod;++i) inv[i] = inv[i] * inv[i-1] % mod;
}

inline LL Lucas(LL n,LL m,LL mod,LL *fac,LL *inv) {
	if(n < m) return 0;
	if(n < mod && m < mod) return fac[n] * inv[m] % mod * inv[n-m] % mod;
	return Lucas(n%mod,m%mod,mod,fac,inv)*Lucas(n/mod,m/mod,mod,fac,inv)%mod;
}

inline void calc(LL x) {
	for(int i=0;i<4;++i)  (ans[i] += Lucas(n,x,prime[i],fac[i],inv[i]))%=prime[i];
}

void ex_gcd(LL a,LL b,LL &x,LL &y) {
	if(b == 0) { x = 1, y = 0; return; }
	ex_gcd(b,a%b,x,y); LL tmp = x; x = y; y = tmp-a/b*y;
}

LL crt () {
	LL ans = 0, x,y;
	for(int i=0;i<4;++i) {
		ex_gcd(phi/prime[i],prime[i],x,y);
		x = (x % phi *(phi/prime[i]) % phi + phi)% phi;
		(ans += x * ::ans[i] % phi) %= phi;

	}
	return ans;
}

LL pow(LL a,LL b) { LL res = 1; for(;b;b>>=1,a=a*a%Mod) if(b&1) res = res * a % Mod; return res; }

int main() { cin >> n >> g; int i;
	for(i=0;i<4;++i) init(prime[i],fac[i],inv[i]);
	for(i=1;(LL)i*i<n;++i) if(n%i==0) calc(i),calc(n/i);
	if((LL)i*i==n) calc(i);
	LL f = crt();
	if(g%Mod == 0) return puts("0"),0;
	f = pow(g%Mod,f);
	cout << f << endl;
}
