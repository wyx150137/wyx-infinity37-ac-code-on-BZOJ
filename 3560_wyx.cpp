
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int mod = 1e9+7;
const int N = 5000+5;
const int M = 8e5+5;
const int Max = 5000;
typedef long long LL;

int n, cnt, prime[N], sum[N];
bool F[N];

struct data {
	int x,y;
	inline bool operator < (const data &z) const {
		return x ^ z.x ? x < z.x : y < z.y;
	}
}a[M];

int tot;

void init() {
	register int j; int i;
	for(i=2;i<=Max;++i) {
		if(!F[i]) prime[++tot] = i;
		for(j=1;prime[j]*i<=Max;++j) {
			F[i*prime[j]] = 1;
			if(i%prime[j] == 0) break;
		}
	}
}

void solve(int x) {
	for(int i=1;prime[i]*prime[i]<=x;++i) {
		if(x%prime[i] == 0) {
			a[++cnt].x = prime[i];
			while(x%prime[i] ==0) {
				a[cnt].y ++;
				x /= prime[i];
			}
		}
	}
	if(x != 1) a[++cnt].x = x, a[cnt].y = 1;
}

inline int pow(int a,int b) {
	int res = 1;
	for(;b;b>>=1,a=(LL)a*a%mod)
		if(b&1)
			res = (LL)res * a % mod;
	return res;
}

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int main() {
	n = read();
	register int i;
	init();
	for(i=1;i<=n;++i) solve(read());
	sort(a+1,a+cnt+1);
	int ans = 1, j, k, p;
	for(i=1;i<=cnt;i=j+1) {
		for(j=i;a[j+1].x == a[j].x && j < cnt; ++j) ;
		p = a[i].x, sum[0] = 1;
		for(k=1;k<=a[j].y;++k) sum[k] = (LL)sum[k-1]*p%mod;
		for(k=1;k<=a[j].y;++k) sum[k] = (sum[k-1] + sum[k])%mod;
		int tmp = 1;
		for(k=i;k<=j;++k) tmp = (LL)tmp * sum[a[k].y] % mod;
		tmp = (LL)(tmp-1)*(p-1)%mod*pow(p,mod-2)%mod+1;
		ans = (LL)ans*tmp%mod;
	}
	cout << ans << endl;
	return 0;
}
