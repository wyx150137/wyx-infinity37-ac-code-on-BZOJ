
#include <map>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e6+5;
const int mod = 1e9+7;
const int phi = mod - 1;
int prime[N], cnt, mu[N];
typedef long long LL;
#define IL __inline__ __attribute__((always_inline))
bool f[N];

map <int,int> mp[N];

IL int modmul(const int &a, const int &b,const int &M) {
    int ret;
    __asm__ __volatile__("\tmull %%ebx\n\tdivl %%ecx\n" : "=d"(ret) : "a"(a), "b"(b), "c"(M));
    return ret;
}

IL int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9') {if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9') {x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int F[N], inv[N];

IL int pow(int a,int b,int M=mod) {int res = 1;for(;b;b>>=1,a=modmul(a,a,mod))if(b&1)res=modmul(res,a,mod);return  res;}

inline void init() {
	int Max = 1e6;
	mu[1] = 1;
	register int j,i;
	for(i=2;i<=Max;++i) {
		if(!f[i]) {
			prime[++cnt] = i;
			mu[i] = -1; 
		} 
		for(j=1;prime[j]*i<=Max;++j) {
			f[prime[j]*i] = 1;
			if(i%prime[j] == 0) break;
			mu[prime[j]*i] = -mu[i];
		}
	}
	for(j=1;j<=Max;++j) mu[j] += mu[j-1];
	F[0] = 0, F[1] = 1;
	for(i=2;i<=Max;++i)  {
		F[i] = F[i-1] + F[i-2];
		if(F[i] >= mod) F[i] -= mod; 
	}
	F[0] = 1;
	for(i=2;i<=Max;++i) F[i] = modmul(F[i-1],F[i],mod);
	for(i=0;i<=Max;++i) inv[i] = pow(F[i],mod-2);
}

IL int calc(int n,int m) {
	if(n > m) swap(n,m);
	if(mp[n].count(m)) return mp[n][m];
	LL ans = 0;
	for(int i=1,last=0;i<=n;i=last+1) {
		last = min(n/(n/i),m/(m/i));
		ans += modmul(modmul((n/i), (m/i),phi) , ((LL)(mu[last] - mu[i-1] + phi)%phi) , phi);
		ans %= phi;
	}
	mp[n][m] = ans;
	return ans;
}

int main() {
	init();
	int T; cin >> T;
	int ans = 1;
	register int last, i;
	while(T--) {
		int n = read(), m = read();
		if(n > m) swap(n,m);
		ans = 1;
		for(i=1,last=0;i<=n;i=last+1) {
			last = min(n/(n/i),m/(m/i));
			LL tmp = calc(n/i,m/i);
			ans = (LL)modmul(ans , pow((LL)F[last]*inv[i-1]%mod,tmp),mod);
		}
		printf("%d\n", ans);
	}
}
