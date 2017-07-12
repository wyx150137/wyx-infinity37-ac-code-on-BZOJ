
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 1e5+5;
LL a[N], b[N];

inline void calc(LL x) {
	register int  i = 1;
	int cnt = 0;
	for(;(LL)i*i<x;++i) {
		if(x%i==0) {
			a[++cnt] = i;
			a[++cnt] = x / i;
		}
	}
	if(i*i==x) a[++cnt] = i;
}

inline LL phi(LL x) {
	register int i = 2;
	LL ans = x;
	int cnt = 0;
	for(;(LL)i*i<=x;++i) {
		if(x%i==0) {
			b[++cnt] = i;
			while(x%i==0) 
				x /= i;
		}
	}
	if(x != 1) b[++cnt] = x;
	for(i=1;i<=cnt;++i) ans = ans / b[i] * (b[i]-1);
	return ans;
}

int main() {
	LL n;
	cin >> n;
	calc(n);
	LL ans = 0;
	for(int i=1;a[i];++i) 
		ans += (LL)a[i] * phi(n/a[i]);
	cout << ans << endl;
}
