
#include <stdio.h>
#include <iostream>
using namespace std;
const int mod = 998244353;
int main() {
	int n, all=0;
	long long ans = 1;
	cin >> n ;
	for(int i=1;i<=n;++i) {
		int tmp; cin >> tmp; all += tmp;
	}
	for(int i=1;i<=all;++i) {
		if(i != all - n + 1) ans = ans * i % mod;
	}
	cout << ans << endl;
}
