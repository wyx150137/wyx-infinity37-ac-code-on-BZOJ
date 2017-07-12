
#include <map>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
const LL N = 1e7+5;
map <LL,LL> mp;

inline LL read() {
	LL x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9') {if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9') {x = (x<<1) + (x<<3) + ch - '0'; ch = getchar();}
	return x*f;
}

LL prime[N], cnt;
LL phi[N];
bool F[N];

inline void init() {
	const LL Max = 1e7;
	register LL j;
	phi[1] = 1;
	for(LL i=2;i<=Max;++i) {
		if(!F[i]) prime[++cnt] = i, phi[i] = i-1;
		for(j=1;prime[j]*i<=Max;++j) {
			F[i*prime[j]] = 1;
			if(i%prime[j]==0) {
				phi[prime[j]*i] = prime[j]*phi[i];
				break;
			}
			phi[prime[j]*i] = (prime[j]-1)*phi[i];
		}
	}
	for(LL i=2;i<=Max;++i) phi[i] += phi[i-1];
}

inline LL calc(LL n) {
	LL last;
	static const LL Max = 1e7;
	if(n <= Max) return phi[n];
	else if(mp.count(n)) return mp[n];
	LL tmp1 = (n)*(n+1)/2;
	for(LL i=2;i<=n;i=last+1) {
		last = n/(n/i);
	//	cout << calc(n/i) << endl;
		tmp1 -= (LL)(last-i+1)*calc(n/i);
	}
	return (mp[n] = tmp1);
}

int main() {
//	freopen("tt.in","r",stdin);
//	freopen("tt.out","w",stdout);
	init();
	LL n = read();
	cout << calc(n);
}
