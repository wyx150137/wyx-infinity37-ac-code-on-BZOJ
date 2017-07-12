
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL mod, n, m;

LL mul(LL a,LL b) {
	LL res = 0;
	for(;b;b>>=1,a=(a+a)%mod)
		if(b&1) res = (res + a) % mod;
	return res;
}

LL pow(LL a,LL b) {
	LL res = 1;
	for(;b;b>>=1,a=mul(a,a))
		if(b&1) res = mul(res, a);
	return res;
}

int main() {
	cin >> n >> m >> mod;
	cout << mul(pow(n,m-1),pow(m,n-1)) << endl;
}
