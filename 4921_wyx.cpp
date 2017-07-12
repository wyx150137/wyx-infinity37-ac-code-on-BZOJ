
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
const int mod = 998244353;
const int N = 1e5+5;
int a[N], pre[N], last[N];

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int L[N];

int main() {
	int n = read();
	for(int i=1;i<=n;++i) a[i] = read();	
	pre[1] = a[1];
	for(int i=2;i<=n;++i) pre[i] = __gcd(pre[i-1], a[i]);
	for(int i=2;i<=n;++i) {
		if(pre[i] == pre[i-1]) L[i] = L[i-1];
		else L[i] = i - 1;
	}
	L[0] = -1;
	int ans = 0, now = 0;
	for(int i=n;i>=2;--i) {
		now = __gcd(now, a[i]);
		for(int j=i-2;~j;j=L[j]) {
			ans = (ans + (LL)(j-L[j])*(__gcd(now, pre[j]) %mod)) % mod;
		}
		if(i == n) ans = (ans - now + mod) % mod;
	}
	for(int i=2;i<n;++i) ans = (ans + pre[i]) % mod;
	cout << ans << endl;
}
