
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
const int mod = 998244353;

LL calc(LL x) {
	LL ans = x;
	for(LL i = 2; i * i <= x; ++ i) {
		if(x % i == 0) {
			ans = ans / i * (i-1);
			while(x % i == 0) 
				x /= i;
		}
	}
	if(x != 1) ans = ans / x * (x-1) % mod;
	return ans % mod;
}

int main() {
	LL n, m;
	cin >> n >> m;
	cout << (n % mod) * (m % mod) % mod * calc(n) % mod * calc(m) % mod << endl;
}
