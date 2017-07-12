
#include <map>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 2e6+5;
const int Max = 2e6;
typedef long long LL;
int prime[N], cnt, mu[N], sum[N];
bool F[N];
int stack[N], top, f[N], k, n, m, py[N];

inline void init() {
	mu[1] = 1;
	for(int i=2;i<=Max;++i) {
		if(!F[i]) {
			prime[++cnt] = i;
			mu[i] = -1;
		}
		for(int j=1;prime[j]*i<=Max;++j) {
			F[prime[j]*i] = 1;
			if(i%prime[j]==0) break;
			mu[i*prime[j]] = -mu[i];
		}
	}
	for(int i=1;i<=Max;++i) sum[i] = mu[i] + sum[i-1];
	for(int i=2;i<=k;++i) if(k%i==0 && mu[i]) stack[++top] = i;
	for(int i=1;i<=k;++i) {
		f[i] = f[i-1];
		py[i] = py[i-1];
		if(__gcd(i, k) == 1) ++ f[i], py[i] += mu[i];
	} 
}

inline LL calc_f(LL x) {
	return 1ll*(x/k)*f[k] + f[x%k];
}

map <LL,int> mp, mp2;

inline LL calc_mu(LL x) {
	if(x <= Max) return sum[x];
	if(mp.count(x)) return mp[x];
	int t = 1;
	for(LL i=2,last;i<=x;i=last+1) {
		last = x/(x/i);
		t -= (last-i+1) * calc_mu(x/i);
	}
	return mp[x] = t;
}

inline int calc(LL x) {
	if(x <= k) return py[x];
	if(mp2.count(x)) return mp2[x];
	int temp = calc_mu(x);
	for(int i=1;i<=top && stack[i]<=x;++i) {
		temp -= mu[stack[i]] * calc(x/stack[i]);
	}
	return mp2[x] = temp;
}

int main() {
	cin >> n >> m >> k;
	init();
	LL ans = 0;
	for(int i=1,last;i<=min(n,m);i=last+1) {
		last = min(n/(n/i),m/(m/i));
		ans += ((calc(last)) - calc(i-1)) * calc_f(m/i) * (n/i);
	}
	cout << ans << endl;
}
