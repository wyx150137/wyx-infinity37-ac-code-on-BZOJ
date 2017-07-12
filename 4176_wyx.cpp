
#include <map>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
typedef long long LL;
using namespace std;
map <int,int> mp;
const int N = 15000000+5;
const int Max = 15000000;
const int mod = 1e9+7;
int prime[N], cnt, mu[N];
bool F[N];

inline void init() {
	mu[1] = 1;
	for(int i=2;i<=Max;++i) {
		if(!F[i]) {
			mu[i] = -1;
			prime[++cnt] = i;
		} 
		for(int j=1;prime[j]*i<=Max;++j) {
			F[i*prime[j]] = 1;
			if(i%prime[j]==0) break;
			mu[i*prime[j]] = -mu[i];
		}
	}
	for(int i=2;i<=Max;++i) mu[i] += mu[i-1];
}

inline int calc_mu(int x) {
	if(x <= Max) return mu[x];
	if(mp.count(x)) return mp[x];
	int ans = 1;
	for(int i=2,last;i<=x;i=last+1) {
		last = x / (x/i);
		ans -= calc_mu(x/i)*(last-i+1);
	}
	return mp[x] = ans;
}

inline int calc(int x) {
	LL ans = 0;
	for(int i=1,last;i<=x;i=last+1) {
		last = x/(x/i);
		ans = (ans + (LL)x/i*(last-i+1)%mod) % mod;
	}
	return ans;
}

int main() {
	init();
	int n; cin >> n;
	LL ans = 0;
	for(int i=1,last;i<=n;i=last+1) {
		last = n / (n/i);
		int tt = calc(n/i);
		ans = (ans + (LL) (calc_mu(last)-calc_mu(i-1)) * tt % mod * tt % mod) % mod;
	}
	cout << (ans % mod + mod) % mod << endl;
}
