
#include <vector>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
#define pb push_back
typedef long long LL;
const LL N = 1e5+5;
const LL mod = 100003;
inline LL read() {
	LL x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

inline LL pow(LL a,LL b) {
	LL res = 1;
	for(;b;b>>=1,a=(LL)a*a%mod)
		if(b&1)
			res = (LL)res * a % mod;
	return res;
}

LL a[N],  f[N];
LL g[N];
vector <LL> V[N];

int main() {
//	freopen("trennen.in","r",stdin);
//	freopen("trennen.out","w",stdout);
	LL n = read(), k = read();
	for(LL i=1;i<=n;++i) a[i] = read();
	for(LL i=1;i<=n;++i) for(LL j=i;j<=n;j+=i) V[j].pb(i);
	LL ans = 0;
	for(LL i=n;i>=1;--i)  {
		if(a[i]) {
			ans ++;
			for(LL j=0;j<V[i].size();++j)
				a[V[i][j]] ^= 1;
		}
	}
	LL tmp;
	if(k < ans) {
		tmp = 0;
		g[n] = 1;
		for(LL i=n;i>=1;i--) g[i] = (g[i+1]*(n-i)%mod+n)%mod*pow(i,mod-2) % mod;
		for(LL i=ans;i>k;--i) tmp = tmp + g[i];
		tmp += k;
	}
	else tmp = ans;
	//cout << tmp << endl;
	for(LL i=1;i<=n;++i) tmp = tmp * i % mod;
	cout << tmp << endl;
}
