
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e7+5;
const int Max = 1e7;
typedef long long LL;

int mu[N], prime[N], cnt;
bool F[N];

void init() {
	mu[1] = 1;
	register int j = 1;
	for(int i=2;i<=Max;++i) {
		if(!F[i]) {
			prime[++cnt] = i;
			mu[i] = -1;
		}
		for(j=1;prime[j]*i<=Max;++j) {
			F[i*prime[j]] = 1;
			if(i%prime[j]==0) break;
			mu[i*prime[j]] = - mu[i];
		}
	}
}

LL calc(LL x) {
	LL ans = x;
	for(int i=1;(LL)i*i<=x;++i) {
		ans -= (LL)mu[i]*x/((LL)i*i);
	}
	return ans;
}

int main() {
	init();
	LL n; cin >> n;
	LL L = 0, R = 210000000000ll, ans = 0;
	while(L <= R) {
		LL mid = (L+R) >> 1;
		if(calc(mid) >= n) {
			ans = mid;
			R = mid - 1;
		}
		else L = mid + 1;
	}
	cout << ans << endl;
}
