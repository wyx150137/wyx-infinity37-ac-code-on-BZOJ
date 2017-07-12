
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 524288+5;
const int mod = 1004535809;
const int T_max = 262144;
typedef long long LL;
inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1; ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int fac[N], ifac[N], h[N], t[N], F[N];

inline int pow(int a,int b) {
	int res = 1;
	for(;b;b>>=1,a=(LL)a*a%mod)
		if(b&1)
			res = (LL) res * a % mod;
	return res;
}

inline int C(int n,int m) {
	if(n < m) return 0;
	return (LL)fac[n]*ifac[m]%mod*ifac[n-m]%mod;
}

inline int calc(int x) {
	LL temp = (LL)x * (x-1) / 2;
	temp %= mod - 1;
	return temp;
}

int T[N];

inline void init() {
	fac[0] = 1;
	static const int Max = 130000;
	for(int i=1;i<=Max;++i) fac[i] = (LL)fac[i-1] * i % mod;
	ifac[Max] = pow(fac[Max], mod-2);
	for(int i=Max-1;~i;--i) ifac[i] = (LL)ifac[i+1] * (i+1) % mod;
	for(int i=0;i<=Max;++i) t[i] = calc(i);	
	for(int i=0;i<=Max;++i) h[i] = pow(2,t[i]);
	for(int i=0;i<=Max;++i) T[i] = (LL) h[i] * ifac[i] % mod;
}

inline void NTT(int *a, int len, int type) {
	register int i,k,j; 
	
	for(i=j=0; i<len; ++i) {
		if(i > j) swap(a[i], a[j]);
		for(k = len >> 1; (j^=k) < k; k >>= 1);
	}
	for(i=2;i<=len;i<<=1) {
		int wn = pow(3,(mod-1)/i);
		for(j=0;j<len;j+=i) {
			int w = 1, x, y;
			for(k=0;k<(i>>1);++k,w=(LL)w*wn%mod) {
				x = a[j+k], y = (LL)a[j+k+i/2]*w % mod;
				a[j+k] = (x + y) % mod;
				a[j+k+(i>>1)] = (x + mod - y) % mod;
			}
		}
	}
	
	if(type == -1) {
		for(i=1;i<len>>1;++i) swap(a[i],a[len-i]);
		int tt = pow(len,mod-2);
		for(i=0;i<len;++i) a[i] = (LL) a[i] * tt % mod;		
	}
}

int a[N], b[N], c[N];
int S[N];

inline void solve(int L,int R) {
	if(L == R) {
		(F[L] += h[L]) %= mod;
		S[L] = (LL)F[L]*ifac[L-1]%mod;
		return;
	}

	if(L > R) return;
	int i;
	int mid = (L+R) >> 1;
	solve(L, mid);
	for(i=L;i<=mid;++i) a[i-L+1] = S[i];
	for(i=1;i+L<=R;++i) b[i] = T[i];
	int n = 1, len = R - L + 1;
	for(n=1;n<=len<<1;n<<=1);
	NTT(a, n, 1);
	NTT(b, n, 1);
	for(i=0;i<=n;++i) c[i] = (LL)a[i] * b[i] % mod;
	NTT(c, n,-1);
	for(i=mid+1;i<=R;++i) (F[i] += mod - (LL)fac[i-1] * c[i-L+1] % mod) %= mod;
	for(i=0;i<=n;++i) a[i] = b[i] = c[i] = 0;
	solve(mid+1,R);
}

int main() {
	int n;
	init();
	cin >> n;
	solve(1,n);
	cout << F[n] << endl;
}
