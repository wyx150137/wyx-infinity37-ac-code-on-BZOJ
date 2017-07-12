
#include <map>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
map <int,int> mp;

inline LL pow(LL a,LL b,LL mod) {
	LL res = 1;
	for(;b;b>>=1,a=a*a%mod)
		if(b&1)
			res  = res * a % mod;
	return res;
}

inline LL calc(LL n) {
	LL ans = n;
	register int i;
	for(i=2;i*i<=n;++i) {
		if(n%i==0) {
			while(n%i==0) n/=i;
			ans /= i; ans *= (i-1);
		}
	}
	if(n>1) ans /= n, ans *= (n-1);
	return ans;
}

LL get(LL n) {
	if(mp.count(n)) return mp[n];
	LL tt = calc(n);
	return (mp[n] = pow(2,get(tt)+tt,n));
}

int main() {
	int T; cin >> T; mp[1] = 0;
	while(T -- ){
		LL n; scanf("%lld",&n);
		printf("%lld\n",get(n));
	}
}
